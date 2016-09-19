#include "multiview_futtracker_controller.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MultiViewFuttrackerController c;

    c.show();

    return a.exec();
}
