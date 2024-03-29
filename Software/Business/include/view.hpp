#ifndef VIEW_HPP
#define VIEW_HPP

#include <QThread>
#include <QTimer>
#include <QQueue>
#include <QMutex>
#include <memory>
#include <opencv2/core/core.hpp>
#include "video_processor.hpp"
#include "common_data_structures.hpp"

class View : public QThread
{
    Q_OBJECT
    public:
        enum class Type{
            TOP = 0,
            SIDE = 1
        };

        explicit View(const cv::FileNode& config);
        static View* createView(const cv::FileNode& config);
        const int getId() const;
        virtual ~View();
        void pause();

    signals:
        void showFrame(const cv::Mat3b& frame, const cv::Mat1b& mask);
        void sendDetections(const DetectionResult& detections, int captureId);

    protected slots:
        virtual void requestCapture()=0;

    protected:
        QTimer captureTimer;
        QMutex captureMutex;
        const int captureId;
        QQueue<cv::Mat3b> frameQueue;
        std::unique_ptr<VideoProcessor> processor;
        cv::Mat1d homography;
        Type type;

        static cv::Mat1d calcHistogram(const cv::Mat3b& region, cv::Mat1d& histogram);

    private:
        cv::Mat1b occupationMask;
        static int captureCounter;
        int closeIterations;
        int minArea;
        int maxArea;

        void run() final;

        void calculateOccupationMask();


};

#endif // VIEW_H
