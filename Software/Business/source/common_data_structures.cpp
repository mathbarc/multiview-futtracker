#include "common_data_structures.hpp"
#include <iostream>

void DetectionResult::clear()
{
    this->locations.clear();
    this->histograms.clear();
}

GaussianComponentGenerator::GaussianComponentGenerator(const cv::FileNode &stddev, const cv::FileNode &limits)
{
    this->stddev[0] = (double)stddev["x"];
    this->stddev[1] = (double)stddev["y"];

    this->limitDistance[0] = (int)limits["x"];
    this->limitDistance[1] = (int)limits["y"];
}

void GaussianComponentGenerator::addToImage(cv::Mat1d &img, const cv::Point &mean)
{
    cv::Point2i min, max;
    min.x = std::max<double>(std::ceil(mean.x - std::sqrt(limitDistance[0])), 0);
    min.y = std::max<double>(std::ceil(mean.y - std::sqrt(limitDistance[1])), 0);

    max.x = std::min<double>(std::ceil(mean.x + std::sqrt(limitDistance[0])), img.cols);
    max.y = std::min<double>(std::ceil(mean.y + std::sqrt(limitDistance[1])), img.rows);


    double constant = (1.0/std::sqrt(2.0*this->stddev[0]*this->stddev[1]*CV_PI));
    cv::Vec2d var;
    var[0] = 2.0*this->stddev[0]*this->stddev[0];
    var[1] = 2.0*this->stddev[1]*this->stddev[1];

//    std::cout<<var<<std::endl;
//    std::cout<<min<<", "<<max<<std::endl;

    double tmpx, tmpy;
    for(int i = min.y; i<max.y; i++)
    {
        for(int j = min.x; j<max.x; j++)
        {
            tmpx = i - mean.y;
            tmpy = j - mean.x;

            img.at<double>(i,j) += constant*std::exp(-1.0*(((tmpx*tmpx)/var[0]) + ((tmpy*tmpy)/var[1])));
        }
    }

}
