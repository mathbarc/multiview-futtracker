#include "video_processor.hpp"
#if(WITH_CUDA)
#include <opencv2/cudabgsegm.hpp>
#else
#include <opencv2/video/background_segm.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

VideoProcessor::VideoProcessor(int history, float threshold, double learningRate)
    :QThread()
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

void VideoProcessor::run()
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
                    cv::cuda::GpuMat d_im,d_fgmask;
                    d_im.upload(img);
                    this->bgs->apply(d_im,d_fgmask,this->learningRate);
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

void VideoProcessor::queueFrame(const cv::Mat3b &frame)
{
    mutex.lock();

    this->queue.enqueue(frame);

    mutex.unlock();
}
