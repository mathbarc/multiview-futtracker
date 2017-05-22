#include "motion_model.hpp"

#include <iostream>

MotionModel::MotionModel(int numberOfStates, const cv::FileNode &config)
    : stateTransition(cv::Mat1d::zeros(numberOfStates,numberOfStates))
{
    double rho = (double)config["rho"];
    double maxDistance = (int)config["max_distance"];

    double Z = 1.0/(static_cast<double>(config["Z"]));
    double tmp;
    for(int i = 0; i<numberOfStates; i++)
    {
        for(int j = 0; j<numberOfStates; j++)
        {
            tmp = std::abs(i-j);
            if(tmp < maxDistance)
            {
                this->stateTransition(i,j) = Z*std::exp(-rho*tmp);
            }
            else
            {
                this->stateTransition(i,j) = 0;
            }
        }
    }

    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Motion Model"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"rho: "<<rho<<std::endl;
    std::cout<<"max distance: "<<maxDistance<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;

}

double MotionModel::operator ()(int i, int j) const
{
    return this->stateTransition(i,j);
}

const double* MotionModel::ptr()
{
    return this->stateTransition.ptr<const double>();
}
