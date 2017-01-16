#ifndef MAIN_WINDOW_VIDEO_PLAYER_HPP
#define MAIN_WINDOW_VIDEO_PLAYER_HPP

#include <QMainWindow>
#include <QImage>
#include <QResizeEvent>
#include <opencv2/highgui/highgui.hpp>
#include "video_grabber.hpp"
#include "video_processor_bgs.hpp"
#include "imagebuffer.hpp"

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
        ImageBuffer* imb;

        int nVideo;

        void inline interruptVideoGrabber();
        void cvToQImage(const cv::Mat3b &img);

    protected:
        void resizeEvent(QResizeEvent* event);

    private slots:
        void showResult(const cv::Mat3b& img);
};

#endif // MAIN_WINDOW_VIDEO_PLAYER_HPP
