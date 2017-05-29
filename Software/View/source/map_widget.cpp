#include "map_widget.hpp"
#include "ui_map_widget.h"
#include "util.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <QResizeEvent>
#include <iostream>

MapWidget::MapWidget(QString windowName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapWidget),
    windowName(windowName),
    scene(this)
{
    ui->setupUi(this);
    this->ui->groupBox->setTitle(windowName);
}

MapWidget::~MapWidget()
{
    delete ui;
}

void MapWidget::showFrame(const cv::Mat1d& frame)
{
    QImage img;
    cv::Mat3b tmp;

//    std::cout<<"ok"<<std::endl;

    generateHeatMap(frame, tmp);
//    cv::imwrite("map.png",tmp);
    img = cvMat3bToQImage(tmp);

    this->scene.clear();

    this->scene.addPixmap(QPixmap::fromImage(img));

    this->ui->graphicsView_image->setScene(&this->scene);

    this->ui->graphicsView_image->fitInView(0,0,img.width(),img.height(),Qt::KeepAspectRatio);

}

QString MapWidget::getWindowName() const
{
    return this->windowName;
}

void MapWidget::resizeEvent(QResizeEvent* event)
{
    QSize size = event->size();
    this->ui->groupBox->setGeometry(this->ui->groupBox->x(), this->ui->groupBox->y(),
                                    size.width()-20, size.height()-10);

    QWidget::resizeEvent(event);
}
