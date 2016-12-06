#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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

    public:
        VideoShow()
            :QObject()
            ,vgrab(new VideoGrabber(0))
            ,vpros(new VideoProcessor(50,16))
        {
            cv::namedWindow("image", cv::WINDOW_NORMAL);
            cv::namedWindow("fore", cv::WINDOW_NORMAL);
            connect(this->vgrab,SIGNAL(nextFrame(const cv::Mat3b&)),this->vpros,SLOT(queueFrame(const cv::Mat3b&)));
            connect(this->vpros,SIGNAL(resultFrame(const cv::Mat3b&, const cv::Mat1b&)),this,SLOT(showFrames(const cv::Mat3b&,const cv::Mat1b&)));
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

            while(vgrab->isRunning()||vpros->isRunning());
            delete vgrab;
            delete vpros;
        }

    public slots:
        void showFrames(const cv::Mat3b& frame, const cv::Mat1b& fgmask)
        {
            cv::imshow("image", frame);
            cv::imshow("fore",fgmask);
        }

};
