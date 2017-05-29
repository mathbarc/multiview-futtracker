#ifndef COMMON_DATA_STRUCTURES_HPP
#define COMMON_DATA_STRUCTURES_HPP

#include <opencv2/core/core.hpp>

struct DetectionResult
{
    std::vector<cv::Point2d> locations;
    std::vector<cv::Mat1d> histograms;
    cv::Mat1b foreground;

    void clear();
};



class GaussianComponentGenerator
{
    public:
        GaussianComponentGenerator(const cv::FileNode& stddev, const cv::FileNode& limits);
        void addToImage(cv::Mat1d& img, const cv::Point& mean);

    private:
        cv::Vec2d stddev;
        cv::Vec2i limitDistance;
};

#endif
