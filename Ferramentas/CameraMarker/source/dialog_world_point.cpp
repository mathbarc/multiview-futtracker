#include "include/dialog_world_point.hpp"
#include "ui_dialog_world_point.h"
#include <iostream>

DialogWorldPoint::DialogWorldPoint() :
    QDialog(0),
    ui(new Ui::DialogWorldPoint)
{
    ui->setupUi(this);
}

DialogWorldPoint::~DialogWorldPoint()
{
    delete ui;
}


void DialogWorldPoint::on_buttonBox_accepted()
{
    if(ui->lineEdit_x->text()!="X"&&ui->lineEdit_y->text()!="Y"&&ui->lineEdit_z->text()!="Z"){
        this->worldPoint.x = this->ui->lineEdit_x->text().toFloat();
        this->worldPoint.y = this->ui->lineEdit_y->text().toFloat();
        this->worldPoint.z = this->ui->lineEdit_z->text().toFloat();
    }
    else{
        this->worldPoint.x = -1.0;
        this->worldPoint.y = -1.0;
        this->worldPoint.z = -1.0;
    }

}

cv::Point3f DialogWorldPoint::getWorldPoint()
{
    static DialogWorldPoint dWorldPoint;
    dWorldPoint.exec();
    dWorldPoint.ui->lineEdit_x->setText("X");
    dWorldPoint.ui->lineEdit_y->setText("Y");
    dWorldPoint.ui->lineEdit_z->setText("Z");
    return dWorldPoint.worldPoint;
}
