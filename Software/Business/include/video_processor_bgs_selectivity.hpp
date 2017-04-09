#ifndef VIDEO_PROCESSOR_BGS_SELECTIVITY_HPP
#define VIDEO_PROCESSOR_BGS_SELECTIVITY_HPP

#include "video_processor.hpp"

class VideoProcessorBGSSelectivity : public VideoProcessor
{
    public:
        VideoProcessorBGSSelectivity(const cv::FileNode& settings);
    private:
        cv::Mat1b backgroundModel;
        double learningRateBG, learningRateFG;
        uchar threshold;
        void run();
};

#endif
