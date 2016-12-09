#ifndef VIDEO_PROCESSOR_HPP
#define VIDEO_PROCESSOR_HPP
#include <opencv2/core/core.hpp>
#include <QThread>
#include <QQueue>
#include <opencv2/video/background_segm.hpp>
#include <QMutex>


class VideoProcessor : public QThread
{
    Q_OBJECT
    public:
        VideoProcessor(int history, float threshold, double learningRate);

    private:
        cv::Ptr<cv::BackgroundSubtractor> bgs;
        QQueue<cv::Mat3b> queue;
        QMutex mutex;
        double learningRate;
        void run();

    public slots:
        void queueFrame(const cv::Mat3b& frame);

    signals:
        void resultFrame(const cv::Mat3b& frame, const cv::Mat1b& fgmask);


};

#endif
