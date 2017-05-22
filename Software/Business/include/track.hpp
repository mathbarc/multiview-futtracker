#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <queue>
#include "opencv2/core/core.hpp"
#include "appearance_model.hpp"
#include "motion_model.hpp"

class Track
{
    public:
        Track(int numberOfStates, const cv::FileNode& motion, const cv::FileNode& appearance);
        void processDetections(const std::vector<DetectionResult>& detections);

    private:
        std::vector<int> positions;
        std::queue<cv::Mat1d> delta;
        std::queue<cv::Mat1d> epsilon;

        MotionModel motion;
        AppearanceModel appearance;
        int numberOfStates;

};

#endif // TRACK_H
