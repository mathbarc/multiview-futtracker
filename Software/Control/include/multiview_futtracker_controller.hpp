#ifndef MULTIVIEW_FUTTRACKER_CONTROLLER
#define MULTIVIEW_FUTTRACKER_CONTROLLER
#include <QObject>
#include "multiview_futtracker_mainwindow.hpp"

class MultiViewFuttrackerController : public QObject{
    Q_OBJECT
    private:
       MultiViewFuttrackerMainWindow* w;

    public:
        MultiViewFuttrackerController();
        ~MultiViewFuttrackerController();
        void show();
};


#endif
