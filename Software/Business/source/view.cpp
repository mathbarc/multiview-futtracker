#include <exception>

#include "view.hpp"
#include "file_view.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <chrono>


int View::captureCounter = 0;

View::View(const cv::FileNode &config)
    : QThread()
    , captureId(captureCounter)
    , closeIterations((int)config["close_iterations"])
    , type((Type)(int)config["view_type"])
    , minArea((int)config["min_area"])
{
    this->processor.reset(VideoProcessor::getInstance(config["video_processor"]));
    if(config["homography"].empty())
    {
        this->homography = cv::Mat::eye(3,3,CV_64F);
    }
    else
    {
        cv::FileStorage homographyFile((std::string)config["homography"], cv::FileStorage::READ);
        homographyFile["homography"] >> this->homography;
    }

    if(config["max_area"].empty())
    {
        maxArea = INT_MAX;
    }
    else
    {
        maxArea = (int)config["max_area"];
    }


    captureCounter++;
}

const int View::getId() const
{
    return this->captureId;
}

View* View::createView(const cv::FileNode& config)
{
    std::string type = (std::string)config["type"];
    if(type == "file")
    {
        return new FileView(config);
    }
    else
    {
        throw std::logic_error("Tipo de captura indisponível: "+type);
    }

}

cv::Mat1d View::calcHistogram(const cv::Mat3b &region, cv::Mat1d& histogram)
{
    histogram.create(3,256);
    histogram.setTo(0);
    cv::Vec3b* regPtr = (cv::Vec3b*) region.ptr();

    double* redPtr = (double*) histogram.ptr(2);
    double* greenPtr = (double*) histogram.ptr(1);
    double* bluePtr = (double*) histogram.ptr(0);

    cv::Vec3b pixel;
    long r;
    for(int i = 0; i<region.rows; i++)
    {
        r = i*region.cols;
        for(int j = 0; j<region.cols; j++)
        {
            pixel = regPtr[r+j];
            redPtr[pixel[2]]++;
            greenPtr[pixel[1]]++;
            bluePtr[pixel[0]]++;
        }
    }
    histogram *= (1.0/(region.cols*region.rows));

    return histogram;
}

void View::run()
{
    cv::Mat3b frame;
    cv::Mat1b result;
    std::vector< std::vector<cv::Point> > components;
    DetectionResult detections;
    cv::Rect boundRect;
    cv::Mat1d histogram;
    cv::Mat1d l(3,1);
    cv::Mat morphologyKernel = cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(3,3));
    int area;

    bool notEmpty;
    while(!this->isInterruptionRequested())
    {
        this->captureMutex.lock();
        notEmpty = !this->frameQueue.empty();
        this->captureMutex.unlock();
        if(notEmpty)
        {
//            std::chrono::high_resolution_clock::time_point tp1 = std::chrono::high_resolution_clock::now();
            this->captureMutex.lock();
            frame = this->frameQueue.dequeue();
            this->captureMutex.unlock();
            result = this->processor->processFrame(frame);
            if(this->closeIterations)
                cv::morphologyEx(result,result,cv::MORPH_CLOSE,morphologyKernel,cv::Point(-1,-1), this->closeIterations);
            detections.clear();
            detections.foreground = result.clone();
            components.clear();
            cv::findContours(result, components, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

            for(int i = 0; i<components.size(); i++)
            {
                area = cv::contourArea(components[i]);
                if(area > this->minArea && area < this->maxArea)
                {
                    boundRect = cv::boundingRect(components[i]);
                    calcHistogram(frame(boundRect), histogram);
                    detections.histograms.push_back(histogram);
                    cv::drawContours(frame, components,i, cv::Scalar(0,0,255),CV_FILLED);
                    cv::rectangle(frame, boundRect, cv::Scalar(0,255,0));

                    switch(this->type)
                    {
                        case Type::SIDE:
                            l(0,0) = boundRect.x + boundRect.width/2.0;
                            l(1,0) = boundRect.y + boundRect.height;
                        break;
                        case Type::TOP:
                            l(0,0) = boundRect.x + boundRect.width/2.0;
                            l(1,0) = boundRect.y + boundRect.height/2.0;
                        break;

                    }
                    l(2,0) = 1.0;

                    cv::circle(frame, cv::Point(l(0,0),l(1,0)), 3, cv::Scalar(0,255,0), CV_FILLED);

                    l = this->homography * l;

                    detections.locations.push_back(cv::Point(l(0,0)/l(2,0), l(1,0)/l(2,0)));

                }
            }
            emit showFrame(frame, detections.foreground);

            emit sendDetections(detections, this->captureId);
//            std::chrono::high_resolution_clock::time_point tp2 = std::chrono::high_resolution_clock::now();
//            std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>(tp2-tp1).count()<<" ms"<<std::endl;
        }
        else
        {
            this->yieldCurrentThread();
        }
    }
}

View::~View()
{
    std::cout<<"~View"<<std::endl;

    std::cout<<"~View done"<<std::endl;
}

void View::pause()
{
    if(this->captureTimer.isActive())
    {
        this->captureTimer.stop();
    }
    else
    {
        this->captureTimer.start();
    }
}
