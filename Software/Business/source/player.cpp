#include "player.hpp"
#include <immintrin.h>

Player::Player()
{

}

const std::string Player::getName()
{
    return this->name;
}

const int Player::getShirtNumber()
{
    return this->shirtNumber;
}

double Player::checkApperance(const cv::Mat1d& hist)
{
    if(hist.cols!=256)
    {
        throw new std::string("Histogram of wrong size");
    }


    const double* hist1;
    const double* hist2;
    hist1 = (double*) this->histogram.ptr();
    hist2 = (const double*) hist.ptr();

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

const cv::Mat1d& Player::getHistogram() const
{
    return this->histogram;
}
