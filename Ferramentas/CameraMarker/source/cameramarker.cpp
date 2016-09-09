#include "cameramarker.h"
#include "ui_cameramarker.h"
#include <QMessageBox>
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
