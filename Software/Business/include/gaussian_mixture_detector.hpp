#ifndef GAUSSIAN_MIXTURE_DETECTOR_HPP
#define GAUSSIAN_MIXTURE_DETECTOR_HPP

#include <QThread>
#include <opencv2/core/core.hpp>
#include <QQueue>
#include <QMutex>
#include "common_data_structures.hpp"

class GaussianMixtureDetector : public QThread
{
    Q_OBJECT

    public:
        GaussianMixtureDetector(const cv::FileNode& settings, const int numberOfCaptures, cv::Size floorSize);

    public slots:
        void receiveResults(const DetectionResult& detections, const int captureId);

    private:
        void run();
        void createDetectionMap(const std::vector<DetectionResult>& detections, cv::Mat1d& floor);
        void findPeaks(const cv::Mat1d& floor, std::vector<cv::Point>& peaks);
        const int numberOfCaptures;
        QMutex queueMutex;
        cv::Size floorSize;
        std::vector< QQueue<DetectionResult> > captureResults;
        std::vector< GaussianComponentGenerator > componentGenerator;

    signals:
        void sendResult(const cv::Mat1d& floor);
};

#endif
