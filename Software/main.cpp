#include "multiview_futtracker_controller.hpp"
#include "player.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat3b>("cv::Mat3b");
    qRegisterMetaType<cv::Mat1b>("cv::Mat1b");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    Q_INIT_RESOURCE(resource);
    MultiViewFuttrackerController c;
    c.show();
    int result = a.exec();
    Q_CLEANUP_RESOURCE(resource);

    return result;
}
