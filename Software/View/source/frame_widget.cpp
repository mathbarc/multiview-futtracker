#include "frame_widget.hpp"
#include "ui_frame_widget.h"
#include "util.hpp"

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

void FrameWidget::showFrame(const cv::Mat3b& frame)
{

    QImage img = cvMatToQImage(frame);

    QGraphicsScene scene;
    scene.addPixmap(QPixmap::fromImage(img));
    this->ui->graphicsView->setScene(&scene);

}
