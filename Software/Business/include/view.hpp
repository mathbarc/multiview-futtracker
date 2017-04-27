#ifndef VIEW_HPP
#define VIEW_HPP

#include <QThread>
#include <QTimer>
#include <QQueue>
#include <QMutex>
#include <memory>
#include <opencv2/core/core.hpp>
#include "video_processor.hpp"

class View : public QThread
{
    Q_OBJECT
    public:
        explicit View(const cv::FileNode& config);
        static View* createView(const cv::FileNode& config);
        virtual ~View();


    signals:
        void showFrame(const cv::Mat3b& frame, const cv::Mat1b& mask);
        void sendDetections();

    protected slots:
        virtual void requestCapture()=0;

    protected:
        QTimer captureTimer;
        QMutex captureMutex;
        QQueue<cv::Mat3b> frameQueue;
        std::unique_ptr<VideoProcessor> processor;
        cv::Mat1d homography;


};

#endif // VIEW_H
