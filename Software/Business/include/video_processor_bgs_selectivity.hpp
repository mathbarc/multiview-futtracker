#ifndef VIDEO_PROCESSOR_BGS_SELECTIVITY_HPP
#define VIDEO_PROCESSOR_BGS_SELECTIVITY_HPP

#include "video_processor.hpp"

class VideoProcessorBGSSelectivity : public VideoProcessor
{
    public:
        VideoProcessorBGSSelectivity(const cv::FileNode& config);
    private:
        cv::Mat3b backgroundModel;
        double learningRate;
        void run();
};

#endif
