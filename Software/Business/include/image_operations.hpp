#ifndef IMAGE_OPERATIONS_HPP
#define IMAGE_OPERATIONS_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


void calcHistogram(const cv::Mat1b& im, cv::Mat1d& hist);

#endif
