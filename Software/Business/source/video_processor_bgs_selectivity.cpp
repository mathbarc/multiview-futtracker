#include "video_processor_bgs_selectivity.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

VideoProcessorBGSSelectivity::VideoProcessorBGSSelectivity(const cv::FileNode& settings)
    :VideoProcessor()
    ,learningRateBG((double)settings["learning_rate_background"])
    ,learningRateFG((double)settings["learning_rate_foreground"])
    ,threshold((int)settings["threshold"])
{
    std::string bgModel = (std::string)settings["bg_model"];
    this->backgroundModel = cv::imread(bgModel, CV_LOAD_IMAGE_GRAYSCALE);
    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"Algorithm BGS Selectivity"<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<"learning rate Background: "<<this->learningRateBG<<std::endl;
    std::cout<<"learning rate Foreground: "<<this->learningRateFG<<std::endl;
    std::cout<<"threshold: "<<this->threshold<<std::endl;
    std::cout<<"backgrond model: "<<bgModel<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl<<std::endl;
}

cv::Mat1b VideoProcessorBGSSelectivity::processFrame(const cv::Mat3b& frame)
{
    cv::Mat3b img = frame.clone();
    cv::Mat1b fg, tmp;
    int index;

    cv::cvtColor(img, tmp, CV_BGR2GRAY);
    cv::absdiff(tmp, this->backgroundModel, fg);
    cv::threshold(fg,fg,this->threshold,255,cv::THRESH_BINARY);
    uchar* tmpPtr = tmp.ptr<uchar>();
    uchar* fgPtr = fg.ptr<uchar>();
    uchar* bgPtr = this->backgroundModel.ptr<uchar>();
    for(int i = 0; i<tmp.rows; i++)
    {
        for(int j =0; j<tmp.cols; j++)
        {
            index = i*tmp.cols+j;
            if(fgPtr[index])
            {
                bgPtr[index] = (uchar)((1-this->learningRateFG)*(double)bgPtr[index] +
                                                       this->learningRateFG*(double)tmpPtr[index]);
            }
            else
            {
                bgPtr[index] = (uchar)((1-this->learningRateBG)*(double)bgPtr[index] +
                                                       this->learningRateBG*(double)tmpPtr[index]);
            }
        }
    }
    return fg;
}

VideoProcessorBGSSelectivity::~VideoProcessorBGSSelectivity()
{
    std::cout<<"~VideoProcessorBGSSelectivity"<<std::endl;

    std::cout<<"~VideoProcessorBGSSelectivity done"<<std::endl;
}
