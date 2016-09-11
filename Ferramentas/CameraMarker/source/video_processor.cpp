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
    this->waitPeriod = 1e6/(this->cap.get(CV_CAP_PROP_FPS));
    this->pauseStream = true;
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
    QImage to_show(img.cols, img.rows, QImage::Format_ARGB32);
    cv::Vec3b* v;
    QRgb* v_show;
    for(int i = 0; i<img.rows; i++){
        v = img.ptr<cv::Vec3b>(i);
        v_show = (QRgb*)to_show.scanLine(i);
        for(int j = 0; j<img.cols; j++){
            v_show[j] = qRgba(v[j][2],v[j][1],v[j][0],255);
        }
    }
    return to_show;
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
        emit showImage(cvToQImage(frame));
        QThread::usleep(this->waitPeriod);
        this->cap >> this->frame;
        while(this->pauseStream)
        {
            if(this->isInterruptionRequested()){
                return;
            }
        }
        if(this->isInterruptionRequested()){
            return;
        }
    }

    return;

}

VideoProcessor::~VideoProcessor(){
    this->cap.release();
}
