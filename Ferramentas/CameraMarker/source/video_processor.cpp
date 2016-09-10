#include "video_processor.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QImage>
#include <iostream>

VideoProcessor::VideoProcessor(std::string path_to_video)
{
    this->cap.open(path_to_video);
    if(!this->cap.isOpened()){
        throw std::string("Não foi possível abrir o vídeo.");
    }
    this->waitPeriod = 1.0/(this->cap.get(CV_CAP_PROP_FPS));
    this->pauseStream = true;
    std::cout<<"Video Processor criado"<<std::endl;
    std::cout<<this->waitPeriod<<std::endl;
    std::cout<<this->pauseStream<<std::endl;
}

void VideoProcessor::pause()
{
    this->pauseStream = true;
}
void VideoProcessor::play()
{
    this->pauseStream = false;
}

QImage cvToQImage(cv::Mat img){

    return QImage();
}

void VideoProcessor::next()
{
    this->cap >> this->frame;

    emit showImage(cvToQImage(this->frame));

}

void VideoProcessor::previous()
{
    double fcount = this->cap.get(CV_CAP_PROP_FRAME_COUNT);
    fcount-=2;
    this->cap.get(CV_CAP_PROP_FRAME_COUNT);
    this->cap.set(CV_CAP_PROP_FRAME_COUNT,fcount);

    this->cap >> this->frame;

    emit showImage(cvToQImage(this->frame));

}

void VideoProcessor::run()
{
    this->cap >> this->frame;
    while(!this->frame.empty()){
        cv::imshow("Video", this->frame);
        emit showImage(cvToQImage(frame));
        QThread::sleep(this->waitPeriod);
        while(this->pauseStream);
    }
}

VideoProcessor::~VideoProcessor(){
    this->cap.release();
}
