#ifndef VIDEO_PROCESSOR_HPP
#define VIDEO_PROCESSOR_HPP
#include <opencv2/core/core.hpp>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QSharedPointer>
#include <boost/property_tree/ptree.hpp>

class VideoProcessor : public QThread
{
    Q_OBJECT
    public:
        VideoProcessor();
        QSharedPointer<VideoProcessor> getInstance(const boost::property_tree::ptree& settings);

    protected:
        QQueue<cv::Mat3b> queue;
        QMutex mutex;
        virtual void run() = 0;

    public slots:
        void queueFrame(const cv::Mat3b& frame);

    signals:
        void resultFrame(const cv::Mat3b& frame, const cv::Mat1b& fgmask);


};

#endif
