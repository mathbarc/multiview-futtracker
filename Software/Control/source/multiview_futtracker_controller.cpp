#include "multiview_futtracker_controller.hpp"
#include <QMessageBox>
#include <iostream>


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
        this->database = new DAOWrapper(configFile["database"]);
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
    connect(this->w, SIGNAL(startExecution()), this, SLOT(startExecution()));
}

MultiViewFuttrackerController::~MultiViewFuttrackerController()
{
    std::cout<<"~MultiViewFuttrackerController"<<std::endl;
    QObject::disconnect(this->w,SIGNAL(setViewFlag(bool)),this->cappool,SLOT(showColorBGS(bool)));
    if(this->cappool!=0)
    {
        delete this->cappool;
    }
    if(this->w!=0)
    {
        delete this->w;
    }
    if(this->database!=0)
    {
        delete this->database;
    }
    std::cout<<"~MultiViewFuttrackerController done"<<std::endl;
}

void MultiViewFuttrackerController::show()
{
    this->w->showFullScreen();
}

void MultiViewFuttrackerController::startExecution()
{
    this->cappool->start();
}
