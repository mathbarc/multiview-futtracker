#include "video_processor.hpp"
#include "video_processor_bgs.hpp"
#include "video_processor_optical_flow.hpp"
#include "video_processor_bgs_selectivity.hpp"

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
    QSharedPointer<VideoProcessor> ptr;
    std::string type = settings["type"];
    if(type=="bgs_selectivity")
    {
        ptr.reset(new VideoProcessorBGSSelectivity(settings));
    }
    else if(type=="bgs")
    {
        ptr.reset(new VideoProcessorBGS(settings));
    }
    else if(type=="opticalflow")
    {
        ptr.reset(new VideoProcessorOpticalFlow(settings));
    }
    else if(type == "dummy")
    {
        ptr.reset(new VideoProcessor());
    }
    else
    {
        throw std::string("Invalid segmentation algorithm "+type+".");
    }
    return ptr;
}

void VideoProcessor::run()
{
    cv::Mat3b img;
    cv::Mat1b gray;

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
            cv::cvtColor(img,gray,CV_BGR2GRAY);
            emit resultFrame(img, gray);
        }
    }


}
