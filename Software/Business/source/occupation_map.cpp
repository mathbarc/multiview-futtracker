#include "occupation_map.hpp"

OccupationMap::OccupationMap(const cv::FileNode &config)
    : floor(cv::Mat1d::zeros((int)config["floor.w"],(int)config["floor.h"]))
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
