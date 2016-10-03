#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP
#include <opencv2/core/core.hpp>
#include <string>
#include <sstream>

struct CalibrationMarker
{
    cv::Point2d imagePoint;
    cv::Point3d worldPoint;
    CalibrationMarker(cv::Point2d image, cv::Point3d world)
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
        std::vector<cv::Point2d> image;
        std::vector<cv::Point3d> world;
};

#endif
