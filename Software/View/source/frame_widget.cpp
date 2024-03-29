#include "frame_widget.hpp"
#include "ui_frame_widget.h"
#include "util.hpp"
#include <iostream>

FrameWidget::FrameWidget(QString windowName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameWidget),
    windowName(windowName),
    showGray(true),
    scene(this)
{
    ui->setupUi(this);
    this->ui->groupBox->setTitle(windowName);
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

    this->scene.clear();

    this->scene.addPixmap(QPixmap::fromImage(img));

    this->ui->graphicsView_image->setScene(&this->scene);

    this->ui->graphicsView_image->fitInView(0,0,img.width(),img.height(),Qt::KeepAspectRatio);

}

void FrameWidget::setFlag(bool flag)
{
    this->showGray = flag;
}

QString FrameWidget::getWindowName() const
{
    return this->windowName;
}

void FrameWidget::resizeEvent(QResizeEvent* event)
{
    QSize size = event->size();
    this->ui->groupBox->setGeometry(this->ui->groupBox->x(), this->ui->groupBox->y(),
                                    size.width()-20, size.height()-10);

    QWidget::resizeEvent(event);
}
