#include "video_processor_optical_flow.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

VideoProcessorOpticalFlow::VideoProcessorOpticalFlow(double pyr_scale, int level, int winsize,
                                                     int iterations, int poly_n, double poly_sigma)
    : VideoProcessor()
    , before()
    , pyr_scale(pyr_scale)
    , level(level)
    , winsize(winsize)
    , iterations(iterations)
    , poly_n(poly_n)
    , poly_sigma(poly_sigma)
{}

void VideoProcessorOpticalFlow::run()
{
    cv::Mat3b img;
    cv::Mat1b result;
    cv::Mat2f interResult;
    cv::Mat1b tmp;
    cv::Mat1b tmpr[2];
    cv::Mat1f r;

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
                #if WITH_CUDA



                #else
                cv::calcOpticalFlowFarneback(this->before, tmp, interResult, this->pyr_scale, this->level, this->winsize,
                                             this->iterations, this->poly_n, this->poly_sigma, cv::OPTFLOW_FARNEBACK_GAUSSIAN);
                #endif
                cv::split(interResult,tmpr);
                cv::magnitude(tmpr[0], tmpr[1], r);
                cv::normalize(r, r, 0, 255, cv::NORM_L2);
                r.convertTo(result,CV_8U);

                emit resultFrame(img,result);
            }
            this->before = tmp;
        }
    }
    return;


}
