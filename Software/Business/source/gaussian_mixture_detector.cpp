#include "gaussian_mixture_detector.hpp"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

GaussianMixtureDetector::GaussianMixtureDetector(const cv::FileNode& settings, const int numberOfCaptures, cv::Size floorSize)
    : numberOfCaptures(numberOfCaptures),
      captureResults(numberOfCaptures),
      floorSize(floorSize)
{
    if(!settings["groundtruth"].empty())
    {
        this->verifier.reset(new GroundTruthVerify(settings["groundtruth"]));
        this->connect(this, SIGNAL(sendPeaks(std::vector<cv::Point>)),
                      this->verifier.data(), SLOT(checkDetections(std::vector<cv::Point>)));
    }


    cv::FileNode generators = settings["generators"];
    for(cv::FileNodeIterator gen = generators.begin(); gen != generators.end(); ++gen)
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
    std::vector<cv::Point> peaks;
//    this->floorSize.width*=2;
//    this->floorSize.height*=2;
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
//            std::cout<<floor<<std::endl<<std::endl;
//            cv::normalize(floor, floor, 0, 1.0, cv::NORM_MINMAX);
            this->findPeaks(floor, peaks);
//            std::cout<<peaks.size()<<std::endl;
            for(int i = 0; i<peaks.size(); i++)
            {
                floor.at<double>(peaks[i]) = 1;
//                std::cout<<peaks[i]<<std::endl;
            }
            emit sendResult(floor);
            emit sendPeaks(peaks);
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

void GaussianMixtureDetector::findPeaks(const cv::Mat1d& floor, std::vector<cv::Point>& peaks)
{
    double tmp;
    peaks.clear();
    for(int i = 1; i < floor.rows-1; i++)
    {
        for(int j = 1; j < floor.cols-1; j++)
        {
            tmp = floor.at<double>(i,j);
            if(tmp > 0.3 && tmp > floor.at<double>(i-1,j) && tmp > floor.at<double>(i,j-1) &&
               tmp > floor.at<double>(i+1,j) && tmp > floor.at<double>(i,j+1)&&
               tmp > floor.at<double>(i-1,j-1) && tmp > floor.at<double>(i-1,j+1) &&
               tmp > floor.at<double>(i+1,j+1) && tmp > floor.at<double>(i+1,j-1)/*&&
               std::abs(floor.at<double>(i+1,j)-floor.at<double>(i-1,j))<1e-5 &&
               std::abs(floor.at<double>(i,j+1)-floor.at<double>(i,j-1))<1e-5*/)
            {
                peaks.push_back(cv::Point(j,i));
            }

        }
    }
}
