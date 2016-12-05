#ifndef VIDEO_GRABBER_HPP
#define VIDEO_GRABBER_HPP

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
