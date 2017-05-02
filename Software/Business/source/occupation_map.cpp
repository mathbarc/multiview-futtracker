#include "occupation_map.hpp"
#include <iostream>

OccupationMap::OccupationMap(const cv::FileNode &config)
{
    cv::FileNode floorNode = config["floor"];
    floor = cv::Mat1d::zeros((int)floorNode["w"],(int)floorNode["h"]);

    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"Occupation Map"<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"size: "<<this->floor.size()<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
}

OccupationMap::~OccupationMap()
{
    std::cout<<"~OccupationMap"<<std::endl;

    std::cout<<"~OccupationMap done"<<std::endl;
}

void OccupationMap::processDetections(const std::vector<DetectionResult> &detections)
{

}

//std::vector<cv::Point2i> OccupationMap::getPeaks()
//{
//    std::vector<cv::Point2i> result;
//    if(this->floor.isContinuous())
//    {
//        double* ptr = this->floor.ptr<double>();
//        for(int i = 0; i<this->floor.rows; i++)
//        {
//            for(int j = 0; j<this->floor.cols; j++)
//            {
//                if(ptr[i*this->floor.cols + j]>this->threshold)
//                {
//                    result.push_back(cv::Point2i(j,i));
//                }
//            }
//        }
//    }
//    else
//    {
//        for(int i = 0; i<this->floor.rows; i++)
//        {
//            for(int j = 0; j<this->floor.cols; j++)
//            {
//                if(this->floor.at<double>(i,j)>this->threshold)
//                {
//                    result.push_back(cv::Point2i(j,i));
//                }
//            }
//        }
//    }
//    return result;
//}
