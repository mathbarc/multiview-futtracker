#ifndef OCCUPATION_MAP_HPP
#define OCCUPATION_MAP_HPP

#include <opencv2/core/core.hpp>

class OccupationMap
{
    public:
        OccupationMap(const cv::FileNode& config);
//        std::vector<cv::Point2i> getPeaks();

    private:
        cv::Mat1d floor;








};

#endif
