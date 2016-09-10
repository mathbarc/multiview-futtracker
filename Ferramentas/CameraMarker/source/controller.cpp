#include "controller.h"
#include <QMessageBox>


Controller::Controller()
    : window(new CameraMarker(0))
    , video_thread(0)
{
    this->window->show();
    connect(this->window,SIGNAL(openVideo(QString)), this, SLOT(openVideo(QString)));
    connect(this->window, SIGNAL(genCalibFile(QString)),this, SLOT(genCalibFile(QString)));
    connect(this->window, SIGNAL(destroyed()), this, SLOT(close()));
}


Controller::~Controller()
{
    if(this->window!=0)
    {
        delete this->window;
    }
    if(this->video_thread!=0)
    {
        this->video_thread->quit();
        this->video_thread->wait();
        delete this->video_thread;
    }
}


void Controller::openVideo(QString path)
{
    std::string pathVideo = path.toStdString();
    try{
        if(this->video_thread!=0)
        {
            this->video_thread->quit();
            this->video_thread->wait();
            disconnect(this->video_thread,SIGNAL(showImage(QImage)),this->window,SLOT(showImage(QImage)));
            delete this->video_thread;
        }
        this->video_thread = new VideoProcessor(pathVideo);
        this->video_thread->start();
    }
    catch(std::string message){
        QMessageBox::warning(this->window,"Problema na abertura do vídeo",QString(message.c_str()));
        connect(this->video_thread,SIGNAL(showImage(QImage)),this->window,SLOT(showImage(QImage)));

    }


}

void Controller::genCalibFile(QString path)
{

}

void Controller::close(){
    if(this->video_thread!=0){
        this->video_thread->quit();
        this->video_thread->wait();
        delete this->video_thread;
    }
}
