#ifndef OCCUPATION_MAP_HPP
#define OCCUPATION_MAP_HPP

#include <opencv2/core/core.hpp>

#include "common_data_structures.hpp"

class OccupationMap
{
    public:
        OccupationMap(const cv::FileNode& config);
        ~OccupationMap();
//        std::vector<cv::Point2i> getPeaks();

        void processDetections(const std::vector<DetectionResult>& detections);

    private:
        cv::Mat1d floor;








};

#endif
