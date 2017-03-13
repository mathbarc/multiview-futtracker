#include "capture_pool.hpp"
#include <iostream>
#include <chrono>

CapturePool::CapturePool(const cv::FileNode& config)
    :QThread(0)
{

    for(cv::FileNodeIterator it = config.begin(); it!=config.end(); ++it)
    {
        QSharedPointer<VideoGrabber> grabber(new VideoGrabber((std::string)(*it)["path"]));
        QSharedPointer<VideoProcessor> processor(VideoProcessor::getInstance((*it)["video_processor"]));
        QSharedPointer<FrameWidget> widget(new FrameWidget(QString::fromStdString((std::string)(*it)["path"])));
        QSharedPointer<SyncQueue> queue(new SyncQueue());

        QObject::connect(grabber.data(),SIGNAL(nextFrame(cv::Mat3b)),processor.data(),SLOT(queueFrame(cv::Mat3b)));
        QObject::connect(processor.data(),SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),queue.data(),SLOT(enqueue(cv::Mat3b,cv::Mat1b)));
        QObject::connect(this,SIGNAL(setFlag(bool)),widget.data(),SLOT(setFlag(bool)));

        this->grabberPool.push_back(grabber);
        this->videoProcessorPool.push_back(processor);
        this->widgets.push_back(widget);
        this->queues.push_back(queue);
    }
}

void CapturePool::run()
{
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->start();
        this->videoProcessorPool[i]->start();
    }

    bool getImages;
    cv::Mat3b im;
    cv::Mat1b fore;

    while(!this->isInterruptionRequested())
    {
        getImages = true;
        for(int i = 0; i<this->queues.size(); i++)
        {
            getImages &= this->queues[i]->hasImage();
        }
        if(getImages)
        {

            for(int i = 0; i<this->queues.size(); i++)
            {
                this->queues[i]->dequeue(im, fore);
                this->widgets[i]->showFrame(im, fore);
            }
        }
    }

    for(int i = 0; i<this->grabberPool.size(); i++)
    {
//        QObject::disconnect(this->grabberPool[i].data(),SIGNAL(nextFrame(cv::Mat3b)),
//                            this->videoProcessorPool[i].data(),SLOT(queueFrame(cv::Mat3b)));
//        QObject::disconnect(this->videoProcessorPool[i].data(),SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),
//                            this->widgets[i].data(), SLOT(showFrame(cv::Mat3b,cv::Mat1b)));
//        QObject::disconnect(this,SIGNAL(setFlag(bool)),
//                            this->widgets[i].data(),SLOT(setFlag(bool)));

        this->grabberPool[i]->requestInterruption();
        this->videoProcessorPool[i]->requestInterruption();
    }
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->wait();
        this->videoProcessorPool[i]->wait();
    }
}

QList<QSharedPointer<FrameWidget> > CapturePool::getWidgets() const
{
    return this->widgets;
}

void CapturePool::showColorBGS(bool flag)
{
    emit setFlag(flag);
}

CapturePool::~CapturePool()
{
    std::cout<<"~CapturePool"<<std::endl;
    if(this->isRunning())
    {
        this->requestInterruption();
        this->wait();
    }
    std::cout<<"~CapturePool done"<<std::endl;
}
