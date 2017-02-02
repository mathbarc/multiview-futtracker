#ifndef OCCUPATION_MAP_HPP
#define OCCUPATION_MAP_HPP

#include <opencv2/core/core.hpp>

class OccupationMap
{
    public:
        OccupationMap(cv::Size floorSize);

    private:
        cv::Mat1d floor;


};

#endif
