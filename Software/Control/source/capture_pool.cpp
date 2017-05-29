#include "capture_pool.hpp"
#include "util.hpp"
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
    cv::Size floorSize = getSize(config["floor"]);


    detector.reset(new GaussianMixtureDetector(config["mixture_of_gaussians_detector"],this->grabberPool.size(),
                   floorSize));
    this->resultWidget.reset(new MapWidget("Detector"));
    connect(this->detector.data(), SIGNAL(sendResult(cv::Mat1d)),this->resultWidget.data(),SLOT(showFrame(cv::Mat1d)));
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        connect(this->grabberPool[i].data(), SIGNAL(sendDetections(DetectionResult,int)),this->detector.data(), SLOT(receiveResults(DetectionResult,int)));
    }

}

void CapturePool::start()
{
    this->detector->start();
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->start();
    }
}

QList< QSharedPointer<QWidget> > CapturePool::getWidgets() const
{
    QList< QSharedPointer<QWidget> > widgets;
    for(int i = 0; i<this->widgets.size(); i++)
    {
        widgets.push_back(static_cast< QSharedPointer<QWidget> >(this->widgets[i]));
    }
    widgets.push_back(static_cast< QSharedPointer<QWidget> >(this->resultWidget));

    return widgets;
}

void CapturePool::showColorBGS(bool flag)
{
    emit setFlag(flag);
}

void CapturePool::interrupt()
{
    this->detector->requestInterruption();
    this->detector->wait();

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

void CapturePool::pause()
{
    for(int i = 0; i<this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->pause();
    }
}

CapturePool::~CapturePool()
{
    std::cout<<"~CapturePool"<<std::endl;
    this->interrupt();
    std::cout<<"~CapturePool done"<<std::endl;
}
