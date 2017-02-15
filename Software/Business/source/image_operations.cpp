#include "image_operations.hpp"

void calcHistogram(const cv::Mat1b& im, cv::Mat1d& hist)
{
    hist.create(1,256);
    hist.setTo(0);

    const uchar* img;
    double* his = (double*)hist.ptr();

    for(int i = 0; i<im.rows; i++)
    {
        img = im.ptr(i);
        for(int j = 0; j<im.cols; j++)
        {
            his[img[j]]++;
        }
    }

    hist/=255.0*(double)(im.cols*im.rows);

}
