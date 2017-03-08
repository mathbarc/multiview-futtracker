#include "video_grabber.hpp"
#include <iostream>

VideoGrabber::VideoGrabber(std::string path)
    : QThread()
{
    this->cap.open(path);
    if(!this->cap.isOpened()){
        throw std::string("Erro ao abrir o arquivo "+path);
    }
    this->period = 1000.0/this->cap.get(CV_CAP_PROP_FPS);
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Video Grabber"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<path<<std::endl;
    std::cout<<"fps: "<<(int)this->cap.get(CV_CAP_PROP_FPS)<<std::endl;
    std::cout<<"-----------------------------"<<std::endl<<std::endl;
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

    while(!this->isInterruptionRequested() && !frame.empty())
    {
//        std::cout<<frame.size()<<std::endl;
        emit nextFrame(frame);
//        cv::imshow("i",frame);
        this->msleep(this->period);
        this->cap >> frame;
    }
    return;
}

cv::Size VideoGrabber::getFrameSize()
{
    cv::Size fs;

    fs.width = this->cap.get(CV_CAP_PROP_FRAME_WIDTH);
    fs.height = this->cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    return fs;
}
