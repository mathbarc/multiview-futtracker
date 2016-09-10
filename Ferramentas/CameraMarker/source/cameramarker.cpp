#include "cameramarker.h"
#include "ui_cameramarker.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>

CameraMarker::CameraMarker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CameraMarker)
{
    ui->setupUi(this);
}

CameraMarker::~CameraMarker()
{
    delete ui;
}

void CameraMarker::on_actionAbrir_Video_triggered()
{
    QString path = QFileDialog::getOpenFileName(0,"Abrir Vídeo", "", "MP4 (*.mp4);;MPEG (*.mpg *.mpeg *.MPG *.MPEG);;AVI (*.avi *.AVI)");
    emit openVideo(path);

}

void CameraMarker::showImage(QImage img)
{

    this->ui->label_frame->setPixmap(QPixmap::fromImage(img));

}
