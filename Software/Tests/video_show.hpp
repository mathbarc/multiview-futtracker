#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "video_grabber.hpp"
#include "video_processor_bgs.hpp"
#include "video_processor_optical_flow.hpp"

#include <iostream>
#include <QObject>

class VideoShow : public QObject
{
        Q_OBJECT
    private:
        VideoGrabber* vgrab;
        VideoProcessor* vpros;
        cv::VideoWriter write;
        int count;

    public:
        VideoShow(std::string path)
            :QObject()
            ,vgrab(new VideoGrabber(path))
            ,vpros(new VideoProcessorBGS(100,40,2e-3, cv::Size(3,3), 1.2))
//            ,vpros(new VideoProcessorOpticalFlow(0.2, 5, 11, 5, 20, 3.5))
            ,count(0)
        {
            this->write.open("result.avi", CV_FOURCC('D','I','V','X'), 33, cv::Size(1440,480));
            std::cout << this->write.isOpened()<<std::endl;
            cv::namedWindow("image", cv::WINDOW_NORMAL);
            cv::namedWindow("fore", cv::WINDOW_NORMAL);
            QObject::connect(this->vgrab,SIGNAL(nextFrame(const cv::Mat3b&)),this->vpros,SLOT(queueFrame(const cv::Mat3b&)));
            QObject::connect(this->vpros,SIGNAL(resultFrame(const cv::Mat3b&, const cv::Mat1b&)),this,SLOT(showFrames(const cv::Mat3b&,const cv::Mat1b&)));
            std::cout<<"Created"<<std::endl;
        }
        VideoShow(int c)
            :QObject()
            ,vgrab(new VideoGrabber(c))
            ,vpros(new VideoProcessorBGS(70,30,0.0002, cv::Size(3,3), 1.2))
        {
            cv::namedWindow("image", cv::WINDOW_NORMAL);
            cv::namedWindow("fore", cv::WINDOW_NORMAL);
            QObject::connect(this->vgrab,SIGNAL(nextFrame(const cv::Mat3b&)),this->vpros,SLOT(queueFrame(const cv::Mat3b&)));
            QObject::connect(this->vpros,SIGNAL(resultFrame(const cv::Mat3b&, const cv::Mat1b&)),this,SLOT(showFrames(const cv::Mat3b&,const cv::Mat1b&)));
        }

        void go()
        {
            std::cout<<"Starting"<<std::endl;
            vpros->start();
            std::cout<<"Started Video Processor"<<std::endl;
            vgrab->start();
            std::cout<<"Started Video Grabber"<<std::endl;

        }
        ~VideoShow()
        {
            vgrab->requestInterruption();
            vpros->requestInterruption();

            std::cout<<"Interruption Requested"<<std::endl;

            vgrab->wait();
            vpros->wait();

            std::cout<<"Threads ended"<<std::endl;

            if(this->write.isOpened())
            {
                this->write.release();
            }

            delete vgrab;
            delete vpros;
        }

    public slots:
        void showFrames(const cv::Mat3b& frame, const cv::Mat1b& fgmask)
        {
            cv::imshow("image", frame);
            cv::imshow("fore",fgmask);

            cv::Mat3b tmp;
            cv::cvtColor(fgmask,tmp,CV_GRAY2BGR);
            cv::Mat3b result(frame.cols*2,frame.rows);
            cv::hconcat(frame, tmp,result);
            if(count<2000){
                std::cout<<count<<std::endl;
                this->write.write(result);
                count++;
            }
            else{
                if(this->write.isOpened())
                {
                    this->write.release();
                }
            }
        }

};
