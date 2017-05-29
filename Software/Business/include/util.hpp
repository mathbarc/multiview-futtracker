#ifndef UTIL_HPP
#define UTIL_HPP

#include <opencv2/core/core.hpp>
#include <QImage>

QImage cvMat3bToQImage(const cv::Mat3b& img);
QImage cvMat1bToQImage(const cv::Mat1b& img);
cv::Size getSize(const cv::FileNode& node);
void generateHeatMap(const cv::Mat1d& in, cv::Mat3b& out);


#endif
