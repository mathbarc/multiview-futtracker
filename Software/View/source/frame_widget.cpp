#include "frame_widget.hpp"
#include "ui_frame_widget.h"
#include "util.hpp"
#include <iostream>

FrameWidget::FrameWidget(QString widgetName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameWidget)
{
    ui->setupUi(this);
    this->ui->groupBox->setTitle(widgetName);
}

FrameWidget::~FrameWidget()
{
    delete ui;
}

void FrameWidget::showFrame(const cv::Mat3b& frame, const cv::Mat1b& bgs)
{
    QImage img;
    if(this->showGray)
        img = cvMat3bToQImage(frame);
    else
        img = cvMat1bToQImage(bgs);
    this->ui->label_frame->setPixmap(QPixmap::fromImage(img));
}

void FrameWidget::setFlag(bool flag)
{
    std::cout<<flag<<std::endl;
    this->showGray = flag;
}
