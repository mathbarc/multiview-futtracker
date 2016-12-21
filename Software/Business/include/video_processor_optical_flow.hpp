#ifndef VIDEO_PROCESSOR_OPTICAL_FLOW_HPP
#define VIDEO_PROCESSOR_OPTICAL_FLOW_HPP
#include "video_processor.hpp"

#include <opencv2/core/core.hpp>

#if(WITH_CUDA)
    #include <opencv2/cudaoptflow.hpp>
#else
    #include <opencv2/video/video.hpp>
#endif

class VideoProcessorOpticalFlow : public VideoProcessor
{
    Q_OBJECT
    public:
        VideoProcessorOpticalFlow();

    private:
        cv::Mat1b before;
        void run();
};

#endif
