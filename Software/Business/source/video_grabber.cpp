#include "video_grabber.hpp"
#include <iostream>

VideoGrabber::VideoGrabber(std::string path)
    : QThread()
{
    this->cap.open(path);
    if(!this->cap.isOpened()){
        throw std::string("Erro ao abrir o arquivo");
    }
}


VideoGrabber::VideoGrabber(int id)
{
    this->cap.open(id);
    if(!this->cap.isOpened()){
        throw std::string("Erro ao abrir a câmera");
    }
}

VideoGrabber::~VideoGrabber()
{
    if(this->cap.isOpened()){
        this->cap.release();
    }
}

void VideoGrabber::run()
{
    cv::Mat3b frame;
    this->cap >> frame;
    std::cout<<frame.cols<<", "<<frame.rows<<std::endl;
    while(!this->isInterruptionRequested() && !frame.empty())
    {
        std::cout<<frame.cols<<", "<<frame.rows<<std::endl;
        emit nextFrame(frame);
        QThread::msleep(30);
        this->cap >> frame;
    }
}
