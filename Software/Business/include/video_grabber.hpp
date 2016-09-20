#ifndef VIDEO_GRABBER
#define VIDEO_GRABBER

#include <QThread>
#include <opencv2/highgui/highgui.hpp>

class VideoGrabber : public QThread{
    public:
        VideoGrabber(std::string path);
        VideoGrabber(int id);
        ~VideoGrabber();
    private:
        cv::VideoCapture cap;
    public slots:

    private slots:

    signals:

};

#endif
