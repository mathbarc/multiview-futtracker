#ifndef GROUND_HPP
#define GROUND_HPP

#include <opencv2/core/core.hpp>

class Ground
{
    public:
        Ground();

    private:
        cv::Size groundSize;
        cv::Size gridSize;
};

#endif // GROUND_H
