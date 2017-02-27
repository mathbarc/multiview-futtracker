#include <QApplication>
#include "capture_pool.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include "frame_widget.hpp"


int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat3b>("cv::Mat3b");
    qRegisterMetaType<cv::Mat1b>("cv::Mat1b");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    cv::FileStorage conf("alg_config.yml", cv::FileStorage::READ);
    CapturePool pool(conf["captures"]);
    conf.release();





    pool.start();

    return a.exec();
}
