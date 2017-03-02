#include "capture_pool.hpp"
#include <iostream>

CapturePool::CapturePool(const cv::FileNode& config)
    :QObject(0)
{

    for(cv::FileNodeIterator it = config.begin(); it!=config.end(); ++it)
    {
        QSharedPointer<VideoGrabber> grabber(new VideoGrabber((std::string)(*it)["path"]));
        QSharedPointer<VideoProcessor> processor(VideoProcessor::getInstance((*it)["video_processor"]));
        QSharedPointer<FrameWidget> widget(new FrameWidget(QString::fromStdString((std::string)(*it)["path"])));

        QObject::connect(grabber.data(),SIGNAL(nextFrame(cv::Mat3b)),processor.data(),SLOT(queueFrame(cv::Mat3b)));
        QObject::connect(processor.data(),SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),widget.data(),SLOT(showFrame(cv::Mat3b,cv::Mat1b)));
        QObject::connect(this,SIGNAL(setFlag(bool)),widget.data(),SLOT(setFlag(bool)));

        this->grabberPool.push_back(grabber);
        this->videoProcessorPool.push_back(processor);
        this->widgets.push_back(widget);
    }
}

void CapturePool::start()
{
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->start();
        this->videoProcessorPool[i]->start();
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

void CapturePool::interrupt()
{
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        QObject::disconnect(this->grabberPool[i].data(),SIGNAL(nextFrame(cv::Mat3b)),
                            this->videoProcessorPool[i].data(),SLOT(queueFrame(cv::Mat3b)));
        QObject::disconnect(this->videoProcessorPool[i].data(),SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),
                            this->widgets[i].data(), SLOT(showFrame(cv::Mat3b,cv::Mat1b)));
        QObject::disconnect(this,SIGNAL(setFlag(bool)),
                            this->widgets[i].data(),SLOT(setFlag(bool)));

        this->grabberPool[i]->requestInterruption();
        this->videoProcessorPool[i]->requestInterruption();
    }
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->wait();
        this->videoProcessorPool[i]->wait();
    }
}

CapturePool::~CapturePool()
{
    std::cout<<"~CapturePool"<<std::endl;
    this->interrupt();
    std::cout<<"~CapturePool done"<<std::endl;
}
