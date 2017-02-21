#include "video_processor.hpp"
#include "video_processor_bgs.hpp"
#include "video_processor_optical_flow.hpp"

VideoProcessor::VideoProcessor()
    :QThread()
{}


void VideoProcessor::queueFrame(const cv::Mat3b &frame)
{
    mutex.lock();

    this->queue.enqueue(frame);

    mutex.unlock();
}

QSharedPointer<VideoProcessor> VideoProcessor::getInstance(const cv::FileNode &settings)
{

    std::string type = settings["type"];
    if(type=="bgs")
    {
        return QSharedPointer<VideoProcessor>(new VideoProcessorBGS(settings));
    }
    else if(type=="opticalflow")
    {
        return QSharedPointer<VideoProcessor>(new VideoProcessorOpticalFlow(settings));
    }
    throw std::string("Invalid segmentation algorithm "+type+".");
}
