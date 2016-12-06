#ifndef VIDEO_GRABBER_HPP
#define VIDEO_GRABBER_HPP

#include <QThread>
#include <opencv2/highgui/highgui.hpp>

class VideoGrabber : public QThread{
        Q_OBJECT
    public:
        VideoGrabber(std::string path);
        VideoGrabber(int id);
        ~VideoGrabber();

    private:
        cv::VideoCapture cap;
        void run();

    signals:
        void nextFrame(const cv::Mat3b& im);

};

#endif
