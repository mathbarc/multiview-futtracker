#ifndef GROUND_TRUTH_VERIFY_HPP
#define GROUND_TRUTH_VERIFY_HPP

#include <map>
#include <opencv2/core/core.hpp>
#include <vector>

#include <QObject>


class GroundTruthVerify : public QObject
{
    Q_OBJECT

    public:
        GroundTruthVerify(const cv::FileNode& settings);
        ~GroundTruthVerify();

    private:
        std::map< int, std::vector<cv::Point> > marks;

        double tP, fP, fN;
        double nDetections;
        double nMarks;
        int frameCount;
        double tolerance;

    public slots:
        void checkDetections(const std::vector<cv::Point>& detections);



};

#endif
