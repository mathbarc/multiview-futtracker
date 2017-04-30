#include "hidden_markov_model.hpp"
#include <iostream>

HiddenMarkovModel::HiddenMarkovModel(const cv::FileNode& config, int numberOfCaptures)
    :QThread()
    , numberOfCaptures(numberOfCaptures)
    , captureResults(numberOfCaptures)
    , occMap(config["occupation_map"])
{
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Hidden Markov Model"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Number of captures: "<<this->numberOfCaptures<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;

}

HiddenMarkovModel::~HiddenMarkovModel()
{
    std::cout<<"~HiddenMarkovModel"<<std::endl;

    std::cout<<"~HiddenMarkovModel done"<<std::endl;
}

void HiddenMarkovModel::receiveResults(const DetectionResult &detections, const int captureId)
{
    this->queueMutex.lock();
    this->captureResults[captureId].enqueue(detections);
    this->queueMutex.unlock();
}

void HiddenMarkovModel::run()
{
    bool ok;
    while(!this->isInterruptionRequested())
    {
        ok = true;
        this->queueMutex.lock();
        for(int i = 0; i < this->numberOfCaptures; i++)
        {
            ok = ok && (!this->captureResults[i].empty());
        }
        if(ok)
        {
            for(int i = 0; i < this->numberOfCaptures; i++)
            {
                std::cout<<this->captureResults[i].size()<<std::endl;
                this->captureResults[i].dequeue();
            }
            std::cout<<std::endl;
        }
        this->queueMutex.unlock();



    }
}
