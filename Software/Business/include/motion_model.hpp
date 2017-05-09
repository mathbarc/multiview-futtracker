#ifndef MOTION_MODEL_HPP
#define MOTION_MODEL_HPP

#include <opencv2/core/core.hpp>

class MotionModel
{
    private:
        cv::Mat1d stateTransition;
    public:
        MotionModel();
};

#endif // MOTION_MODEL_HPP
