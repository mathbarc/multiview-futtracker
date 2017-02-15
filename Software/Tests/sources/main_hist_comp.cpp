#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <immintrin.h>
#include <iostream>
#include <chrono>

double compHistogram(const cv::Mat1d& h1, const cv::Mat1d& h2)
{
    const double* hist1;
    const double* hist2;
    hist1 = (const double*) h1.ptr();
    hist2 = (const double*) h2.ptr();

    double mean1 = 0, mean2 = 0;

    for(int i = 0; i<256; i++)
    {
        mean1 += hist1[i];
        mean2 += hist2[i];
    }
    mean1/=256.0;
    mean2/=256.0;

    double r1=0,r2=0,r3=0;
    double t1,t2;
    for(int i = 0; i<256; i++)
    {
        t1 = hist1[i]-mean1;
        t2 = hist2[i]-mean2;

        r1+=t1*t1;
        r2+=t2*t2;
        r3+=t1*t2;
    }
    return r3/sqrt(r1*r2);

}

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


int main(int argc, char** argv)
{
    cv::Mat3b im1 = cv::imread(argv[1]);
    cv::Mat3b im2 = cv::imread(argv[2]);

    cv::cvtColor(im1,im1,CV_BGR2HSV);
    cv::cvtColor(im2,im2,CV_BGR2HSV);

    cv::Mat1b im1c[3];
    cv::Mat1b im2c[3];


    cv::split(im1,im1c);
    cv::split(im2,im2c);



    cv::imshow("im1",im1c[0]);
    cv::imshow("im2",im2c[0]);


    cv::Mat1d h1,h2;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    calcHistogram(im1c[0],h1);
    calcHistogram(im2c[0],h2);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()/2<<" us"<<std::endl;

    double v;

    t1 = std::chrono::high_resolution_clock::now();
    v = compHistogram(h1,h2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout<<v<<" "<<std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count()/2<<" us"<<std::endl;
    cv::waitKey(0);

    return 0;
}
