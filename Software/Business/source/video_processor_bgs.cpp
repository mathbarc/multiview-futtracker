#include "video_processor_bgs.hpp"
#if(WITH_CUDA)
#include <opencv2/cudabgsegm.hpp>
#else
#include <opencv2/video/background_segm.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

VideoProcessorBGS::VideoProcessorBGS(const cv::FileNode& settings)
    :VideoProcessor()
    ,learningRate((double)settings["learning_rate"])
    ,gaussianStdDev((double)settings["gaussian_stddev"])
{

    cv::FileNode kernelsize = settings["gaussian_kernel_size"];

    this->gaussianKernelSize.width = (int)kernelsize["w"];
    this->gaussianKernelSize.height = (int)kernelsize["h"];

    int history = (int)settings["history"];
    int threshold = (int)settings["threshold"];

    #if(WITH_CUDA)
        this->bgs = cv::cuda::createBackgroundSubtractorMOG2(history,threshold);
    #else
        #if(OPENCV_VERSION==3)
            this->bgs = cv::createBackgroundSubtractorMOG2(history, threshold);
        #elif(OPENCV_VERSION==2)
            this->bgs = new cv::BackgroundSubtractorMOG2(history, threshold);
        #endif
    #endif

    std::string bgModel = "N/A";
    if(!settings["bg_model"].empty())
    {
        bgModel = (std::string)settings["bg_model"];
        cv::Mat3b img = cv::imread(bgModel, CV_LOAD_IMAGE_COLOR);

       #if(OPENCV_VERSION==3)
           #if(WITH_CUDA)
//             std::cout<<"Gaussian applyed"<<std::endl;
               this->d_im.upload(img,this->stream);
//             std::cout<<"CPU ---> GPU wait"<<std::endl;
               this->stream.waitForCompletion();
//             std::cout<<"CPU ---> GPU"<<std::endl;
               this->bgs->apply(this->d_im, this->d_fgmask,1, this->stream);
               this->stream.waitForCompletion();
               if(!d_fgmask.empty())
               {
                   d_fgmask.download(fgmask,this->stream);
                   this->stream.waitForCompletion();
               }
           #else
               this->bgs->apply(img,cv::Mat1b(),1);
           #endif
           #elif(OPENCV_VERSION==2)
               this->bgs->operator ()(img,cv::Mat1b(img.size()),1);
           #endif
    }

    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Algorithm BGS"<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"history: "<<history<<std::endl;
    std::cout<<"threshold: "<<threshold<<std::endl;
    std::cout<<"learning rate: "<<this->learningRate<<std::endl;
    std::cout<<"gaussian stddev: "<<this->gaussianStdDev<<std::endl;
    std::cout<<"gaussian kernel size: "<<this->gaussianKernelSize<<std::endl;
    std::cout<<"backgrond model: "<<bgModel<<std::endl;
    std::cout<<"-----------------------------"<<std::endl<<std::endl;

}


VideoProcessorBGS::VideoProcessorBGS(int history, float threshold, double learningRate,
                                     cv::Size gaussianKernelSize, double gaussianStdDev)
    :VideoProcessor()
    ,learningRate(learningRate)
    ,gaussianKernelSize(gaussianKernelSize)
    ,gaussianStdDev(gaussianStdDev)
{
    #if(WITH_CUDA)
        this->bgs = cv::cuda::createBackgroundSubtractorMOG2(history,threshold);
    #else
    #if(OPENCV_VERSION==3)
        this->bgs = cv::createBackgroundSubtractorMOG2(history, threshold);
    #elif(OPENCV_VERSION==2)
        this->bgs = new cv::BackgroundSubtractorMOG2(history, threshold);
    #endif
    #endif
}

void VideoProcessorBGS::run()
{
    cv::Mat3b img;
    cv::Mat1b fgmask;

    while(!this->isInterruptionRequested())
    {
        mutex.lock();
        if(!this->queue.empty())
            img = this->queue.dequeue();
        else
            img = cv::Mat();
        mutex.unlock();

        if(!img.empty())
        {
//            std::cout<<this<<" frame"<<std::endl;
            cv::GaussianBlur(img,img,gaussianKernelSize,gaussianStdDev);
            #if(OPENCV_VERSION==3)
                #if(WITH_CUDA)
//                    std::cout<<"Gaussian applyed"<<std::endl;
                    d_im.upload(img,this->stream);
//                    std::cout<<"CPU ---> GPU wait"<<std::endl;
                    this->stream.waitForCompletion();
//                    std::cout<<"CPU ---> GPU"<<std::endl;
                    this->bgs->apply(d_im,d_fgmask,this->learningRate,this->stream);
                    this->stream.waitForCompletion();
                    if(!d_fgmask.empty())
                    {
                        d_fgmask.download(fgmask,this->stream);
                        this->stream.waitForCompletion();
                    }
                #else
                    this->bgs->apply(img,fgmask,this->learningRate);
                #endif
            #elif(OPENCV_VERSION==2)
                this->bgs->operator ()(img,fgmask,this->learningRate);
            #endif
            cv::threshold(fgmask,fgmask, 250, 255, cv::THRESH_BINARY);
            cv::erode(fgmask, fgmask, cv::Mat(), cv::Point(), 1);
            cv::dilate(fgmask, fgmask, cv::Mat(), cv::Point(), 1);
            emit resultFrame(img,fgmask);
        }
    }
    return;
}

VideoProcessorBGS::~VideoProcessorBGS()
{
    #if(WITH_CUDA)
        this->stream.waitForCompletion();
        if(!this->d_im.empty())
            this->d_im.release();
        if(!this->d_fgmask.empty())
            this->d_fgmask.release();
    #endif

}

