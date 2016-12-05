#ifndef MULTIVIEW_FUTTRACKER_CONTROLLER
#define MULTIVIEW_FUTTRACKER_CONTROLLER

#include <QObject>
#include "multiview_futtracker_mainwindow.hpp"
#include "data_base.hpp"

class MultiViewFuttrackerController : public QObject{
    Q_OBJECT
    private:
       MultiviewFuttrackerMainWindow* w;
       DAOWrapper* database;

    public:
        MultiViewFuttrackerController();
        ~MultiViewFuttrackerController();
        void show();
};


#endif
