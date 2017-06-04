#include "util.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

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

cv::Size getSize(const cv::FileNode &node)
{
    cv::Size size;
    size.width = (int)node["width"];
    size.height = (int)node["height"];
    return size;
}

void generateHeatMap(const cv::Mat1d& in, cv::Mat3b& out)
{

    std::vector<cv::Mat1b> ch(3);
    ch[2] = cv::Mat1b(in.size()).setTo(255);
    ch[1] = cv::Mat1b(in.size()).setTo(127);

    in.convertTo(ch[0],CV_8U,-120.0, 120.0);
//    std::cout<<ch[0]<<std::endl;

    cv::Mat3b img;
    cv::merge(ch, img);
    ch.clear();

    cv::cvtColor(img, out, CV_HLS2BGR);
}
