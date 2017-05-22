#ifndef HIDDEN_MARKOV_CHAIN_HPP
#define HIDDEN_MARKOV_CHAIN_HPP

#include "common_data_structures.hpp"

#include "appearance_model.hpp"
#include "motion_model.hpp"
#include "track.hpp"

#include <queue>


class HiddenMarkovChain
{
    public:
        HiddenMarkovChain(const cv::FileNode& config);

    private:
        cv::FileNode motionModel;
        cv::FileNode appearanceModel;
        int numberOfStates;

        std::vector<Track> tracks;



        void processDetections(std::vector<DetectionResult> observations);


};


#endif
