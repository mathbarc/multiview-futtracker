#include "capture_pool.hpp"
#include <iostream>
CapturePool::CapturePool(const cv::FileNode& config)
    :QObject(0)
{
    for(cv::FileNodeIterator it = config.begin(); it!=config.end(); ++it)
    {
        QSharedPointer<VideoGrabber> grabber(new VideoGrabber((std::string)(*it)["path"]));
        QSharedPointer<VideoProcessor> processor(VideoProcessor::getInstance((*it)["video_processor"]));
        QObject::connect(grabber.data(),SIGNAL(nextFrame(cv::Mat3b)),processor.data(),SLOT(queueFrame(cv::Mat3b)));
        this->grabberPool.push_back(grabber);
        this->videoProcessorPool.push_back(processor);
    }
}

void CapturePool::start()
{
    for(int i = 0; this->grabberPool.size(); i++)
    {
        this->grabberPool[i]->start();
        this->videoProcessorPool[i]->start();
    }
}
