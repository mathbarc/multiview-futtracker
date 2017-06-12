#include "ground_truth_verify.hpp"
#include <fstream>
#include <iostream>
#include "util.hpp"

GroundTruthVerify::GroundTruthVerify(const cv::FileNode &settings)
    : tP(0)
    , fP(0)
    , fN(0)
    , nDetections(0)
    , nMarks(0)
    , frameCount(0)
{
    std::fstream file((std::string)settings["path"], std::fstream::in);

    std::string line;

    this->tolerance = (double)settings["tolerance"];

    while(std::getline(file,line))
    {

        std::stringstream ss(line);

        std::string cell;

        std::getline(ss,cell);
        int frame = std::stoi(cell);

        std::getline(ss,cell);
        int x = std::stod(cell);

        std::getline(ss,cell);
        int y = std::stod(cell);

        marks[frame].emplace_back(cv::Point(x,y));

    }

    file.close();
}

void GroundTruthVerify::checkDetections(const std::vector<cv::Point> &detections)
{
    this->frameCount++;
    try
    {
        auto& v = this->marks.at(this->frameCount);
        int tP = 0;
        int fP = 0;
        int fN = 0;

        for(const cv::Point& p : detections)
        {
            for(cv::Point& ref : v)
            {
                double tmp1 = p.x-ref.x;
                double tmp2 = p.y-ref.y;
                double dist = cv::sqrt(tmp1*tmp1+tmp2*tmp2);
                if(dist < this->tolerance)
                {
                    tP++;
                    break;
                }
            }
        }
        fP = std::abs(v.size() - tP);
        fN = std::abs(v.size() - detections.size());

        this->tP += tP;
        this->fN += fN;
        this->fP += fP;

        this->nDetections += detections.size();
        this->nMarks += v.size();
    }
    catch(std::out_of_range e){}
}


GroundTruthVerify::~GroundTruthVerify()
{
    std::cout<<"~GroundTruthVerify"<<std::endl;
    std::cout<< this->tP << ", " << this->fP<< ", "<< this->fN << std::endl;
    std::cout<< this->nDetections << " " << this->nMarks<<std::endl;

    double f1Score = (2.0*this->tP)/(2.0*this->tP + this->fN + this->fP);
    double nModa = 1.0 - ((this->fN + this->fP)/this->nMarks);

    std::cout<<f1Score<<" "<<nModa<<std::endl;
    std::cout<<"~GroundTruthVerify done"<<std::endl;

}
