#include "video_processor_bgs_selectivity.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

VideoProcessorBGSSelectivity::VideoProcessorBGSSelectivity(const cv::FileNode& settings)
    :VideoProcessor()
    ,learningRateBG((double)settings["learning_rate_background"])
    ,learningRateFG((double)settings["learning_rate_foreground"])
    ,threshold((int)settings["threshold"])
{
    this->backgroundModel = cv::imread((std::string)settings["bg_model"], CV_LOAD_IMAGE_GRAYSCALE);
}

void VideoProcessorBGSSelectivity::run()
{
    cv::Mat3b img;
    cv::Mat1b fg, tmp;
    int index;
    while (!this->isInterruptionRequested()) {

        this->mutex.lock();
        if(!this->queue.empty())
        {
            img = this->queue.dequeue();
            this->mutex.unlock();
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
            emit resultFrame(img,fg);
        }
        else
        {
            this->mutex.unlock();
        }

    }
}
