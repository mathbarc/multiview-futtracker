#include "hidden_markov_model.hpp"

HiddenMarkovModel::HiddenMarkovModel(const cv::FileNode& config, int numberOfCaptures)
    :QThread()
    , numberOfCaptures(numberOfCaptures)
    , captureResults(numberOfCaptures)
    , occMap(config["occupation_map"])
{

}


void HiddenMarkovModel::receiveResults(const DetectionResult &detections, const int captureId)
{
    this->queueMutex.lock();
    this->captureResults[captureId].enqueue(detections);
    this->queueMutex.unlock();
}
