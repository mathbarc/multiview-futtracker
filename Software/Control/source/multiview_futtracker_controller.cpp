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
    }
    catch(std::string ex)
    {
        QMessageBox::warning(this->w,"Erro", tr(ex.c_str()));
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
