#include "video_processor.hpp"
#include "video_processor_bgs_gmm.hpp"
#include "video_processor_optical_flow.hpp"
#include "video_processor_bgs_selectivity.hpp"
#include <exception>

VideoProcessor::VideoProcessor()
{}

VideoProcessor* VideoProcessor::getInstance(const cv::FileNode &settings)
{

    std::string type = (std::string)settings["type"];
    if(type=="bgs_selectivity")
    {
        return new VideoProcessorBGSSelectivity(settings);
    }
    else if(type=="bgs_gmm")
    {
        return new VideoProcessorBGSGMM(settings);
    }
    else if(type=="opticalflow")
    {
        return new VideoProcessorOpticalFlow(settings);
    }
    else if(type == "dummy")
    {
        return new VideoProcessor();
    }
    else
    {
        throw std::logic_error("Invalid segmentation algorithm "+type);
    }
}

cv::Mat1b VideoProcessor::processFrame(const cv::Mat3b &frame)
{
    cv::Mat1b gray;
    cv::cvtColor(frame, gray,CV_BGR2GRAY);
    return gray;
}


VideoProcessor::~VideoProcessor()
{

}
