#ifndef MAIN_WINDOW_VIDEO_PLAYER_HPP
#define MAIN_WINDOW_VIDEO_PLAYER_HPP

#include <QMainWindow>
#include <QImage>
#include <opencv2/highgui/highgui.hpp>
#include "video_grabber.hpp"
#include "video_processor_bgs.hpp"

namespace Ui {
    class MainWindowVideoPlayer;
}

class MainWindowVideoPlayer : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindowVideoPlayer(QWidget *parent = 0);
        ~MainWindowVideoPlayer();

    private slots:
        void on_actionAbrir_triggered();

    private:
        Ui::MainWindowVideoPlayer *ui;
        VideoProcessor* processor;
        VideoGrabber* grabber;
        cv::VideoWriter writer;
        int nVideo;

        void inline interruptVideoGrabber();
        void cvToQImage(cv::Mat3b img);

    private slots:
        void showResult(cv::Mat3b img, cv::Mat1b result);
};

#endif // MAIN_WINDOW_VIDEO_PLAYER_HPP
