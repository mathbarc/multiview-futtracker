#include "video_processor_optical_flow.hpp"
#include <iostream>

VideoProcessorOpticalFlow::VideoProcessorOpticalFlow()
    : VideoProcessor()
    , before()
{}

void VideoProcessorOpticalFlow::run()
{
    cv::Mat3b img;
    cv::Mat1b result;
    cv::Mat1b interResult;
    cv::Mat1b tmp;

    while(!this->isInterruptionRequested())
    {
        mutex.lock();
        if(!this->queue.empty())
            img = this->queue.dequeue();
        else
            img = cv::Mat();
        mutex.unlock();

        if(!img.empty())
        {
            cv::cvtColor(img,tmp, CV_BGR2GRAY);
            cv::GaussianBlur(tmp,tmp,cv::Size(3,3),1.2);
            if(this->before.empty())
            {
                this->before = tmp;
            }
            else
            {
                cv::calcOpticalFlowFarneback(this->before, tmp, interResult, 0.5, 4, 21, 5, 5, 1.5, cv::OPTFLOW_FARNEBACK_GAUSSIAN);
                std::cout<<"Ok"<<std::endl;
                cv::normalize(interResult, interResult, 0, 255, cv::NORM_L2);
                interResult.convertTo(result,CV_8U);
                emit resultFrame(img,result);
            }
        }
    }



}
