#ifndef SYNC_QUEUE_HPP
#define SYNC_QUEUE_HPP

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <tuple>
#include <opencv2/core/core.hpp>

class SyncQueue : public QObject
{
        Q_OBJECT
    public:
        explicit SyncQueue(QObject *parent = 0);
        bool hasImage();
        void dequeue(cv::Mat3b& img, cv::Mat1b& fore);

    private:
        QQueue< std::pair<cv::Mat3b,cv::Mat1b> > imgs;
        QMutex mutex;

    public slots:
        void enqueue(const cv::Mat3b& img, const cv::Mat1b& fore);
};

#endif
