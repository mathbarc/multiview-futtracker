#include "multiview_futtracker_controller.hpp"

MultiViewFuttrackerController::MultiViewFuttrackerController()
    : QObject(0)
{
    this->w = new MultiviewFuttrackerMainWindow(0);
}

MultiViewFuttrackerController::~MultiViewFuttrackerController()
{
    if(this->w!=0){
        delete this->w;
    }
}

void MultiViewFuttrackerController::show()
{
    this->w->show();
}
