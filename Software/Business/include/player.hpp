#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <opencv2/core/core.hpp>

class Player
{
    private:
        std::vector<cv::Point2i> occupation;
        int lastOccupation;
        cv::Mat3d histogram;

    public:
        Player();
        double getMeanAcceleration();
        double getMeanVelocity();
        cv::Mat3d getHistogram();
        double checkApperance(cv::Mat3b im);


};

#endif
