#include "multiview_futtracker_controller.hpp"
#include <QMessageBox>


MultiViewFuttrackerController::MultiViewFuttrackerController()
    : QObject(0)
{
    this->w = new MultiviewFuttrackerMainWindow(0);
    cv::FileStorage configFile("config.yml",cv::FileStorage::READ);

    if(!configFile.isOpened())
    {
        QMessageBox::warning(this->w,"Erro", "Arquivo de configuração não encontrado");
        exit(-2);
    }

    try
    {
        this->database = new DAOWrapper(configFile["database"]);
        this->cappool = new CapturePool(configFile["captures"]);
    }
    catch(std::string ex)
    {
        QMessageBox::warning(NULL,"Erro", tr(ex.c_str()));
        configFile.release();
        exit(-1);
    }
    configFile.release();
}

MultiViewFuttrackerController::~MultiViewFuttrackerController()
{
    if(this->w!=0){
        delete this->w;
    }
}

void MultiViewFuttrackerController::show()
{
    this->w->showFullScreen();
}
