#ifndef VIDEO_PROCESSOR_BGS_HPP
#define VIDEO_PROCESSOR_BGS_HPP
#include "video_processor.hpp"
#include <opencv2/core/core.hpp>
#include <QThread>
#include <QQueue>
#include <opencv2/video/background_segm.hpp>
#include <QMutex>


class VideoProcessorBGS : public VideoProcessor
{
    Q_OBJECT
    public:
        VideoProcessorBGS(int history, float threshold, double learningRate);

    private:
        cv::Ptr<cv::BackgroundSubtractor> bgs;
        double learningRate;
        void run();
};

#endif
