#include "video_processor.hpp"
#if(WITH_CUDA)
#include <opencv2/cudabgsegm.hpp>
#else
#include <opencv2/video/background_segm.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

VideoProcessor::VideoProcessor(int history, float threshold )
{
    #if(WITH_CUDA)
        this->bgs = cv::cuda::createBackgroundSubtractorMOG2(history,threshold);
    #else
        this->bgs = cv::createBackgroundSubtractorMOG2(history, threshold);
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
            this->bgs->apply(img,fgmask,0.2);
            emit resultFrame(img,fgmask);
        }
    }



}

void VideoProcessor::queueFrame(const cv::Mat3b &frame)
{
    std::cout<<"Queueing "<<std::endl;
    mutex.lock();

    this->queue.enqueue(frame);
    std::cout<<"Queued "<<this->queue.size()<<std::endl;

    mutex.unlock();
}
