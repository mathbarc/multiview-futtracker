#ifndef APPEARANCE_MODEL_HPP
#define APPEARANCE_MODEL_HPP

#include "common_data_structures.hpp"

class AppearanceModel
{
    public:
        AppearanceModel(int numberOfStates, const cv::FileNode& config);
        void processObservations(std::vector<DetectionResult> observations);

        std::vector<cv::Mat1d> last_observations;
};

#endif // APPEARANCE_MODEL_HPP
