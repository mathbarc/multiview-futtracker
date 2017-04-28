#ifndef COMMON_DATA_STRUCTURES_HPP
#define COMMON_DATA_STRUCTURES_HPP

#include <opencv2/core/core.hpp>

struct DetectionResult
{
    std::vector<cv::Point2d> locations;
    std::vector<cv::Mat1d> histograms;

    void clear();
};


#endif
