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

double Player::checkApperance(const cv::Mat3d& hist)
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
