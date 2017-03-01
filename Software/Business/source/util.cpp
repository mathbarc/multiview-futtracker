#include "util.hpp"

QImage cvMat3bToQImage(const cv::Mat3b& img)
{
    QImage to_show(img.cols, img.rows, QImage::Format_ARGB32);
    const cv::Vec3b* v;
    QRgb* v_show;
    for(int i = 0; i<img.rows; i++)
    {
        v = img.ptr<cv::Vec3b>(i);
        v_show = (QRgb*)to_show.scanLine(i);
        for(int j = 0; j<img.cols; j++)
        {
            v_show[j] = qRgba(v[j][2],v[j][1],v[j][0],255);
        }
    }
    return to_show;
}

QImage cvMat1bToQImage(const cv::Mat1b& img)
{
    QImage to_show(img.cols, img.rows, QImage::Format_ARGB32);
    const uchar* v;
    QRgb* v_show;
    for(int i = 0; i<img.rows; i++)
    {
        v = img.ptr<uchar>(i);
        v_show = (QRgb*)to_show.scanLine(i);
        for(int j = 0; j<img.cols; j++)
        {
            v_show[j] = qRgba(v[j],v[j],v[j],255);
        }
    }
    return to_show;
}
