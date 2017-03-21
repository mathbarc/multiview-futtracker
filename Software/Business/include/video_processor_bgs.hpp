#ifndef VIDEO_PROCESSOR_BGS_HPP
#define VIDEO_PROCESSOR_BGS_HPP
#include "video_processor.hpp"

#if(WITH_CUDA)
#include <opencv2/cudabgsegm.hpp>
#else
#include <opencv2/video/background_segm.hpp>
#endif


class VideoProcessorBGS : public VideoProcessor
{
    Q_OBJECT
    public:
        VideoProcessorBGS(int history, float threshold, double learningRate,
                          cv::Size gaussianKernelSize, double gaussianStdDev);
        VideoProcessorBGS(const cv::FileNode& settings);
        ~VideoProcessorBGS();

    private:
        double learningRate;
        cv::Size gaussianKernelSize;
        double gaussianStdDev;
        void run();
        #if WITH_CUDA
            cv::Ptr<cv::cuda::BackgroundSubtractorMOG2> bgs;
            cv::cuda::GpuMat d_im, d_fgmask;
            cv::cuda::Stream stream;
        #else
            cv::Ptr<cv::BackgroundSubtractor> bgs;
        #endif
};

#endif
