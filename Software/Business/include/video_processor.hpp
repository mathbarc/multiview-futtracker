#ifndef VIDEO_PROCESSOR_HPP
#define VIDEO_PROCESSOR_HPP

#include <opencv2/core/core.hpp>


class VideoProcessor
{
    public:
        VideoProcessor();
        static VideoProcessor* getInstance(const cv::FileNode& settings);
        virtual cv::Mat1b processFrame(const cv::Mat3b& frame);
        virtual ~VideoProcessor();
};

#endif
