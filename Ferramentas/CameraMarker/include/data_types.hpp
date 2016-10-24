#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP
#include <opencv2/core/core.hpp>
#include <string>
#include <sstream>

struct CalibrationMarker
{
    cv::Point2f imagePoint;
    cv::Point3f worldPoint;
    CalibrationMarker(cv::Point2f image, cv::Point3f world)
    {
        this->imagePoint=image;
        this->worldPoint=world;
    }
    std::string toString()
    {
        std::stringstream ss;
        ss << this->imagePoint << ", " << this->worldPoint;
        return ss.str();
    }
};

struct CalibrationData
{
        std::vector<cv::Point2f> image;
        std::vector<cv::Point3f> world;
};

#endif
