#include "multiview_futtracker_controller.hpp"
#include "player.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(resource);
    MultiViewFuttrackerController c;
    c.show();
    int result = a.exec();
    Q_CLEANUP_RESOURCE(resource);

    return result;
}
