#include "video_processor_bgs.hpp"
#if(WITH_CUDA)
#include <opencv2/cudabgsegm.hpp>
#else
#include <opencv2/video/background_segm.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

VideoProcessorBGS::VideoProcessorBGS(int history, float threshold, double learningRate)
    :VideoProcessor()
    ,learningRate(learningRate)
{
    #if(WITH_CUDA)
        this->bgs = cv::cuda::createBackgroundSubtractorMOG2(history,threshold);
    #else
    #if(OPENCV_VERSION==3)
        this->bgs = cv::createBackgroundSubtractorMOG2(history, threshold);
    #elif(OPENCV_VERSION==2)
        this->bgs = new cv::BackgroundSubtractorMOG2(history, threshold);
    #endif
    #endif
}

void VideoProcessorBGS::run()
{
    cv::Mat3b img;
    cv::Mat1b fgmask;

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
            cv::GaussianBlur(img,img,cv::Size(3,3),1.2);
            #if(OPENCV_VERSION==3)
                #if(WITH_CUDA)
                    d_im.upload(img);
                    this->bgs->apply(d_im,d_fgmask,this->learningRate);
                    if(!d_fgmask.empty())
                    d_fgmask.download(fgmask);
                #else
                    this->bgs->apply(img,fgmask,this->learningRate);
                #endif
            #elif(OPENCV_VERSION==2)
                this->bgs->operator ()(img,fgmask,this->learningRate);
            #endif
            emit resultFrame(img,fgmask);
        }
    }
}

VideoProcessorBGS::~VideoProcessorBGS()
{
    #if(WITH_CUDA)
        if(!this->d_im.empty())
            this->d_im.release();
        if(!this->d_fgmask.empty())
            this->d_fgmask.release();
    #endif

}
