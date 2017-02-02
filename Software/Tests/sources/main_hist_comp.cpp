#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <immintrin.h>
#include <iostream>
#include <chrono>

double checkApperance(cv::Mat3d hist, cv::Mat3d histogram)
{
    if(hist.cols!=256)
    {
        throw new std::string("Histogram of wrong size");
    }


    const cv::Vec3d* in;
    cv::Vec3d* loc;

    in = (const cv::Vec3d*)hist.ptr(0);
    loc = (cv::Vec3d*)histogram.ptr(0);

    double tmp;
    cv::Vec3d result(0,0,0);

    for(int i = 0; i<256; i++)
    {
        tmp = in[i][0]-loc[i][0];
        result[0] += tmp*tmp;

        tmp = in[i][1]-loc[i][1];
        result[1] += tmp*tmp;

        tmp = in[i][2]-loc[i][2];
        result[2] += tmp*tmp;
    }

    result[0] = sqrt(result[0]);
    result[1] = sqrt(result[1]);
    result[2] = sqrt(result[2]);


    return sqrt(result[0]*result[0]+result[1]*result[1]+result[2]*result[2]);
}

void calcHistogram(const cv::Mat3b& im, cv::Mat3d& hist)
{
    hist.setTo(cv::Scalar::all(0));
    cv::Vec3d* result = (cv::Vec3d*)hist.ptr(0);
    const cv::Vec3b* imt;

    for(int i = 0; i<im.rows; i++)
    {
        imt = (const cv::Vec3b*)im.ptr(i);
        for(int j = 0; j<im.cols; j++)
        {
            result[imt[j][0]][0]++;
            result[imt[j][1]][1]++;
            result[imt[j][2]][2]++;
        }
    }
    hist *= (1.0/(im.cols*im.rows));
}

int main()
{
    cv::Mat3b im1,im2;

    im1 = cv::imread("katana.jpg");
    im2 = cv::imread("t.jpg");

    cv::Mat3d h1(1,256),h2(1,256);

    calcHistogram(im1,h1);
    calcHistogram(im2,h2);

    std::cout<<h1<<std::endl<<h2<<std::endl;
    double v;
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
    v = checkApperance(h1,h2);

    std::cout<<v<<" t = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - t).count()<<std::endl;

    cv::imshow("i1",im1);
    cv::imshow("i2",im2);

    cv::waitKey(0);

    return 0;
}
