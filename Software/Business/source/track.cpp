#include "include/track.hpp"

Track::Track(int numberOfStates, const cv::FileNode& motion, const cv::FileNode& appearance)
    : numberOfStates(numberOfStates)
    , motion(numberOfStates, motion)
    , appearance(numberOfStates, appearance)
{

}

