#include <opencv2/core/core.hpp>

struct CalibrationMarker
{
    cv::Point2d imagePoint;
    cv::Point3d worldPoint;
    CalibrationMarker(cv::Point2d image, cv::Point3d world)
    {
        this->imagePoint=image;
        this->worldPoint=world;
    }
};

