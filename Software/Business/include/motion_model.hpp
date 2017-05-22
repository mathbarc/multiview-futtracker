#ifndef MOTION_MODEL_HPP
#define MOTION_MODEL_HPP

#include <opencv2/core/core.hpp>

class MotionModel
{
    private:
        cv::Mat1d stateTransition;

    public:
        MotionModel(int numberOfStates, const cv::FileNode& config);
        double operator()(int i, int j) const;
        const double* ptr();

};

#endif // MOTION_MODEL_HPP
