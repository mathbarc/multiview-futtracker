#ifndef VIDEO_PROCESSOR_HPP
#define VIDEO_PROCESSOR_HPP
#include <opencv2/core/core.hpp>
#include <QThread>
#include <QQueue>
#include <opencv2/video/video.hpp>
#include <QMutex>

class VideoProcessor : public QThread
{
    Q_OBJECT
    public:
        VideoProcessor();

    private:
        cv::BackgroundSubtractor* bgs;
        QQueue<cv::Mat3b> to_process;
        QQueue queue;
        QMutex mutex;

    public slots:
        void queueFrame(const cv::Mat3b& frame);

    signals:
        void resultFrame(const cv::Mat3b& frame);

};

#endif
