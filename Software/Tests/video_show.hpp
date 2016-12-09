#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "video_grabber.hpp"
#include "video_processor.hpp"

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
            ,vpros(new VideoProcessor(100,40,2e-3))
            ,count(0)
        {
            this->write.open("result.avi", CV_FOURCC('D','I','V','X'), 33, cv::Size(1440,480));
            std::cout << this->write.isOpened()<<std::endl;
            cv::namedWindow("image", cv::WINDOW_NORMAL);
            cv::namedWindow("fore", cv::WINDOW_NORMAL);
            QObject::connect(this->vgrab,SIGNAL(nextFrame(const cv::Mat3b&)),this->vpros,SLOT(queueFrame(const cv::Mat3b&)));
            QObject::connect(this->vpros,SIGNAL(resultFrame(const cv::Mat3b&, const cv::Mat1b&)),this,SLOT(showFrames(const cv::Mat3b&,const cv::Mat1b&)));
        }
        VideoShow(int c)
            :QObject()
            ,vgrab(new VideoGrabber(c))
            ,vpros(new VideoProcessor(70,30,0.0002))
        {
            cv::namedWindow("image", cv::WINDOW_NORMAL);
            cv::namedWindow("fore", cv::WINDOW_NORMAL);
            QObject::connect(this->vgrab,SIGNAL(nextFrame(const cv::Mat3b&)),this->vpros,SLOT(queueFrame(const cv::Mat3b&)));
            QObject::connect(this->vpros,SIGNAL(resultFrame(const cv::Mat3b&, const cv::Mat1b&)),this,SLOT(showFrames(const cv::Mat3b&,const cv::Mat1b&)));
        }

        void go()
        {
            vgrab->start();
            vpros->start();

        }
        ~VideoShow()
        {
            vgrab->requestInterruption();
            vpros->requestInterruption();

            vgrab->wait();
            vpros->wait();

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
