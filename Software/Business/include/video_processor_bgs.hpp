#ifndef VIDEO_PROCESSOR_BGS_HPP
#define VIDEO_PROCESSOR_BGS_HPP
#include "video_processor.hpp"
#include <opencv2/core/core.hpp>
#include <QThread>
#include <QQueue>
#include <opencv2/video/background_segm.hpp>
#if(WITH_CUDA)
#include <opencv2/cudabgsegm.hpp>
#endif
#include <QMutex>


class VideoProcessorBGS : public VideoProcessor
{
    Q_OBJECT
    public:
        VideoProcessorBGS(int history, float threshold, double learningRate,
                          cv::Size gaussianKernelSize, double gaussianStdDev);
        ~VideoProcessorBGS();

    private:
        cv::Ptr<cv::BackgroundSubtractor> bgs;
        double learningRate;
        cv::Size gaussianKernelSize;
        double gaussianStdDev;
        void run();
        #if WITH_CUDA
            cv::cuda::GpuMat d_im,d_fgmask;
        #endif
};

#endif
