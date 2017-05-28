#include "file_view.hpp"
#include <chrono>
#include <exception>
#include <iostream>

FileView::FileView(const cv::FileNode &config)
    : View(config)
{

    std::string path =(std::string)config["path"];
    if(!capture.open(path))
    {
        throw std::logic_error("Arquivo de vídeo "+path+" não pode ser aberto");
    }

    int fps;
    if(config["fps"].empty())
    {
        fps = this->capture.get(CV_CAP_PROP_FPS);
    }
    else
    {
        fps = (int)config["fps"];
    }
    int period = 1000/fps;

    this->captureTimer.setInterval(period);
    connect(&this->captureTimer, SIGNAL(timeout()), this, SLOT(requestCapture()));

    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"File View"<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"ID: "<<this->getId()<<std::endl;
    std::cout<<"path: "<<path<<std::endl;
    std::cout<<"fps: "<<fps<<std::endl;
    std::cout<<"period: "<<period<<" ms"<<std::endl;
    std::cout<<"homography: "<<std::endl<<this->homography<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl<<std::endl;


    this->captureTimer.start();

}

void FileView::requestCapture()
{
    cv::Mat3b frame;
    this->capture>>frame;
    this->captureMutex.lock();
    this->frameQueue.enqueue(frame);
    this->captureMutex.unlock();
}

FileView::~FileView()
{
    std::cout<<"~FileView"<<std::endl;
    this->captureTimer.stop();
    if(this->capture.isOpened())
        capture.release();
    std::cout<<"~FileView done"<<std::endl;
}
