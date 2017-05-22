#include "data_processor.hpp"
#include <iostream>

DataProcessor::DataProcessor(const cv::FileNode& config, int numberOfCaptures)
    :QThread()
    , numberOfCaptures(numberOfCaptures)
    , captureResults(numberOfCaptures)
    , chain(config)
{

    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"DataProcessor"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Number of captures: "<<this->numberOfCaptures<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;

}

DataProcessor::~DataProcessor()
{
    std::cout<<"~DataProcessor"<<std::endl;

    std::cout<<"~DataProcessor done"<<std::endl;
}

void DataProcessor::receiveResults(const DetectionResult &detections, const int captureId)
{
    this->queueMutex.lock();
    this->captureResults[captureId].enqueue(detections);
    this->queueMutex.unlock();
}

void DataProcessor::run()
{
    bool ok;
    std::vector<DetectionResult> detections(this->numberOfCaptures);
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
               detections[i] = this->captureResults[i].dequeue();
            }
            this->queueMutex.unlock();

        }
        else this->queueMutex.unlock();
    }
}
