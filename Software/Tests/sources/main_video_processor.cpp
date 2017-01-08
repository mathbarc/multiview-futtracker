#include <opencv2/core/core.hpp>
#include <QApplication>

#include <QMetaType>
#include <QFileDialog>

#include "main_window_video_player.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat3b>("cv::Mat3b");
    qRegisterMetaType<cv::Mat1b>("cv::Mat1b");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    MainWindowVideoPlayer w;

    w.show();

    return a.exec();
}
