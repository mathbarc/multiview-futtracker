#include "multiview_futtracker_mainwindow.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MultiViewFuttrackerMainWindow w;

    w.show();

    return a.exec();
}
