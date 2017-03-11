#ifndef MULTIVIEW_FUTTRACKER_CONTROLLER
#define MULTIVIEW_FUTTRACKER_CONTROLLER

#include <QObject>
#include "multiview_futtracker_mainwindow.hpp"
#include "data_base.hpp"
#include "capture_pool.hpp"

class MultiViewFuttrackerController : public QObject{
    Q_OBJECT
    private:
       MultiviewFuttrackerMainWindow* w;
       DAOWrapper* database;
       CapturePool* cappool;

    public:
        MultiViewFuttrackerController();
        ~MultiViewFuttrackerController();
        void show();

    private slots:
        void startExecution();
};


#endif
