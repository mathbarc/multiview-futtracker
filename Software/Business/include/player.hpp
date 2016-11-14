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
        int shirtNumber;
        std::string name;

    public:
        Player();
        double getMeanAcceleration();
        double getMeanVelocity();
        cv::Mat3d getHistogram();
        cv::Mat3b genHeatMap();
        const std::vector<cv::Point2i> getOccupation();
        const int getShirtNumber();
        const std::string getName();
        double checkApperance(cv::Mat3b im);


};

#endif
