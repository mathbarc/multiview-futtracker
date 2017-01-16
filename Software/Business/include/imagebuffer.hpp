#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <QThread>
#include <QQueue>
#include <QMutex>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImageBuffer : public QThread
{
    Q_OBJECT

    public:
        ImageBuffer(cv::Size fs);
        ~ImageBuffer();

    private:
        QQueue<cv::Mat3b> imgs;
        QMutex mutex;
        cv::VideoWriter writer;
        static int nVideo;

    public slots:
        void enqueue(const cv::Mat3b& img, const cv::Mat1b& fgmask);
        void run();

    signals:
        void show(const cv::Mat3b& im);

};

#endif // IMAGEBUFFER_H
