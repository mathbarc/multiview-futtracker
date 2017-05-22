#include "capture_pool.hpp"
#include <iostream>


CapturePool::CapturePool(const cv::FileNode& config)
    :QObject(0)
{
    cv::FileNode captures = config["captures"];
    for(cv::FileNodeIterator it = captures.begin(); it!=captures.end(); ++it)
    {
        QSharedPointer<View> grabber(View::createView(*it));
        QSharedPointer<FrameWidget> widget(new FrameWidget(QString::fromStdString((std::string)(*it)["path"])));

        QObject::connect(grabber.data(),SIGNAL(showFrame(cv::Mat3b,cv::Mat1b)),widget.data(),SLOT(showFrame(cv::Mat3b,cv::Mat1b)), Qt::QueuedConnection);
        QObject::connect(this,SIGNAL(setFlag(bool)),widget.data(),SLOT(setFlag(bool)));

        this->grabberPool.push_back(grabber);
        this->widgets.push_back(widget);
    }
    tracker.reset(new DataProcessor(config["tracker"],this->grabberPool.size()));

    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        connect(this->grabberPool[i].data(), SIGNAL(sendDetections(DetectionResult,int)),this->tracker.data(), SLOT(receiveResults(DetectionResult,int)));
    }
}

void CapturePool::start()
{
    this->tracker->start();
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->start();
    }
}

QList< QSharedPointer<FrameWidget> > CapturePool::getWidgets() const
{
    return this->widgets;
}

void CapturePool::showColorBGS(bool flag)
{
    emit setFlag(flag);
}

void CapturePool::interrupt()
{
    this->tracker->requestInterruption();
    this->tracker->wait();

    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        QObject::disconnect(this->grabberPool[i].data(),SIGNAL(showFrame(cv::Mat3b,cv::Mat1b)),
                            this->widgets[i].data(), SLOT(showFrame(cv::Mat3b,cv::Mat1b)));
        QObject::disconnect(this,SIGNAL(setFlag(bool)),
                            this->widgets[i].data(),SLOT(setFlag(bool)));

        this->grabberPool[i]->requestInterruption();
    }
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->wait();
    }
}

CapturePool::~CapturePool()
{
    std::cout<<"~CapturePool"<<std::endl;
    this->interrupt();
    std::cout<<"~CapturePool done"<<std::endl;
}
