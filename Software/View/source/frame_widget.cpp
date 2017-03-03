#include "frame_widget.hpp"
#include "ui_frame_widget.h"
#include "util.hpp"
#include <iostream>

FrameWidget::FrameWidget(QString windowName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameWidget),
    windowName(windowName),
    showGray(true)
{
    ui->setupUi(this);
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

//    QGraphicsScene scene;
//    scene.addPixmap(QPixmap::fromImage(img));
//    this->ui->graphicsView->setScene(&scene);

    this->ui->label_frame->setPixmap(QPixmap::fromImage(img));
}

void FrameWidget::setFlag(bool flag)
{
//    std::cout<<flag<<std::endl;
    this->showGray = flag;
}

QString FrameWidget::getWindowName() const
{
    return this->windowName;
}

void FrameWidget::resize(const QSize &size)
{
    this->ui->label_frame->resize(size.width()-20, size.height()-20);
}

