#include "multiview_futtracker_controller.hpp"
#include "player.hpp"
#include "common_data_structures.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat3b>("cv::Mat3b");
    qRegisterMetaType<cv::Mat1b>("cv::Mat1b");
    qRegisterMetaType<cv::Mat1b>("cv::Mat1d");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<DetectionResult>("DetectionResult");

    Q_INIT_RESOURCE(resource);
    MultiViewFuttrackerController c;
    c.show();
    int result = a.exec();
    Q_CLEANUP_RESOURCE(resource);

    return result;
}
