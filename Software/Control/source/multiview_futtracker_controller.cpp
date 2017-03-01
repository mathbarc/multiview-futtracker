#include "multiview_futtracker_controller.hpp"
#include <QMessageBox>


MultiViewFuttrackerController::MultiViewFuttrackerController()
    : QObject(0)
{

    cv::FileStorage configFile("config.yml",cv::FileStorage::READ);

    if(!configFile.isOpened())
    {
        QMessageBox::warning(this->w,"Erro", "Arquivo de configuração não encontrado");
        exit(-2);
    }

    try
    {
//        this->database = new DAOWrapper(configFile["database"]);
        this->w = new MultiviewFuttrackerMainWindow();
        this->cappool = new CapturePool(configFile["captures"]);
        this->w->addSubWindows(this->cappool->getWidgets());
        QObject::connect(this->w,SIGNAL(setViewFlag(bool)),this->cappool,SLOT(showColorBGS(bool)));
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
    this->cappool->interrupt();
    if(this->w!=0)
    {
        delete this->w;
    }
    if(this->cappool!=0)
    {
        delete this->cappool;
    }
    if(this->database!=0)
    {
        delete this->database;
    }
}

void MultiViewFuttrackerController::show()
{
    this->w->show();
//    this->cappool->start();
}
