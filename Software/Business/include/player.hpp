#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <opencv2/core/core.hpp>

class Player
{
    private:
        std::vector<cv::Point2i> occupation;
        int lastOccupation;
        cv::Mat1d histogram;
        int shirtNumber;
        std::string name;

    public:
        Player();
        double getMeanAcceleration();
        double getMeanVelocity();
        const cv::Mat1d& getHistogram() const;
        cv::Mat3b genHeatMap();
        const std::vector<cv::Point2i> getOccupation();
        const int getShirtNumber();
        const std::string getName();
        double checkApperance(const cv::Mat1d& hist);


};

#endif
