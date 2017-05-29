#include "gaussian_mixture_detector.hpp"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

GaussianMixtureDetector::GaussianMixtureDetector(const cv::FileNode& settings, const int numberOfCaptures, cv::Size floorSize)
    : numberOfCaptures(numberOfCaptures),
      captureResults(numberOfCaptures),
      floorSize(floorSize)
{
    for(cv::FileNodeIterator gen = settings.begin(); gen != settings.end(); ++gen)
    {
        this->componentGenerator.push_back(GaussianComponentGenerator((*gen)["stddev"], (*gen)["limit_distance"]));
    }

    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"Gaussian Mixture Detector"<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"Number of componentes: "<<this->componentGenerator.size()<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
}

void GaussianMixtureDetector::run()
{

    bool ok;
    std::vector<DetectionResult> detections(this->numberOfCaptures);
    cv::Mat1d floor(this->floorSize);
    floor.setTo(0);
    cv::Mat1f kernel(3,3);
    kernel.col(1).setTo(1);
    kernel.row(1).setTo(1);
    kernel(1,1) = -4;

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

            this->createDetectionMap(detections, floor);
//            cv::normalize(floor, floor, 0, 1.0, cv::NORM_MINMAX);
//            std::cout<<floor<<std::endl<<std::endl;
            emit sendResult(floor);
        }
        else
        {
            this->queueMutex.unlock();
            this->yieldCurrentThread();
        }

    }
}

void GaussianMixtureDetector::receiveResults(const DetectionResult &detections, const int captureId)
{
    this->queueMutex.lock();
    this->captureResults[captureId].enqueue(detections);
    this->queueMutex.unlock();
}

void GaussianMixtureDetector::createDetectionMap(const std::vector<DetectionResult>& detections, cv::Mat1d& floor)
{
    floor.setTo(0);
    cv::Rect fRec(0,0,floorSize.width, floorSize.height);
//    double aposteriori = 1.0/(double)(detections.size());
//    double factor;
    for(int i = 0; i<this->numberOfCaptures; i++)
    {
//        factor = aposteriori/((double)detections[i].locations.size());
        for(int j = 0; j<detections[i].locations.size(); j++)
        {
            if(fRec.contains(detections[i].locations[j]))
            this->componentGenerator[i].addToImage(floor,detections[i].locations[j]);
        }
//        std::cout<<floor<<std::endl;
    }
//    std::cout<<std::endl;
}
