#include <QApplication>
#include <QMainWindow>
#include "capture_pool.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include "frame_widget.hpp"
#include <QLayout>


int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat3b>("cv::Mat3b");
    qRegisterMetaType<cv::Mat1b>("cv::Mat1b");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    cv::FileStorage conf("config.yml", cv::FileStorage::READ);
    CapturePool pool(conf["captures"]);
    conf.release();

    QMainWindow win;

    QList< QSharedPointer<FrameWidget> > wid = pool.getWidgets();
    std::cout<<wid.size()<<std::endl;
    for(int i = 0; i < wid.size(); i++ )
    {
        win.layout()->addWidget(wid[i].data());
    }

    pool.start();
    win.show();

    return a.exec();
}
