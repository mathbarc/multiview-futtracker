#include "video_show.hpp"

#include <QApplication>

#include <QMetaType>
#include <QFileDialog>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat3b>("cv::Mat3b");
    qRegisterMetaType<cv::Mat1b>("cv::Mat1b");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    QString file = QFileDialog::getOpenFileName(nullptr,"Open File", ".", "*.mpg(MPG);;*.mp4(MP4)");
    std::cout<<file.toStdString()<<std::endl;
    VideoShow vs(file.toStdString());
    vs.go();

    return a.exec();
}
