#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "video_grabber.hpp"
#include "video_processor.hpp"

#include <QObject>

class VideoShow : public QObject
{
        Q_OBJECT
    public:
        VideoShow()
            :QObject()
            ,vgrab(new VideoGrabber(0))
            ,vpros(new VideoProcessor(50,16))
        {
            qRegisterMetaType<cv::Mat3b>("cv::Mat3b");
            qRegisterMetaType<cv::Mat1b>("cv::Mat1b");

            cv::namedWindow("image", cv::WINDOW_NORMAL);
            cv::namedWindow("fore", cv::WINDOW_NORMAL);
            connect(vgrab,SIGNAL(nextFrame(cv::Mat3b)),vpros,SLOT(queueFrame(cv::Mat3b)));
            connect(vpros,SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),this,SLOT(showFrames(cv::Mat3b,cv::Mat1b)));
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

    private:
        VideoGrabber* vgrab;
        VideoProcessor* vpros;

    public slots:
        void showFrames(const cv::Mat3b& frame, const cv::Mat1b& fgmask)
        {
            cv::imshow("image", frame);
            cv::imshow("fore",fgmask);
        }

};
