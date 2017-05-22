#include "hidden_markov_chain.hpp"

HiddenMarkovChain::HiddenMarkovChain(const cv::FileNode &config)
    : numberOfStates(static_cast<double>(config["number_of_states"])),
      appearanceModel(config["appearance_model"]),
      motionModel(config["motion_model"])
{

}
