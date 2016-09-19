#include "multiview_futtracker_mainwindow.hpp"
#include "ui_multiview_futtracker_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <QKeyEvent>
#include <QKeySequence>
#include <opencv2/core/core.hpp>

MultiViewFuttrackerMainWindow::MultiViewFuttrackerMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MultiViewFuttrackerMainWindow)
{
    ui->setupUi(this);
}

MultiViewFuttrackerMainWindow::~MultiViewFuttrackerMainWindow()
{
    delete ui;
}

void MultiViewFuttrackerMainWindow::on_actionAbrir_Video_triggered()
{
    QString path = QFileDialog::getOpenFileName(0,"Abrir Vídeo", "", "MP4 (*.mp4);;MPEG (*.mpg *.mpeg *.MPG *.MPEG);;AVI (*.avi *.AVI)");
    emit openVideo(path);

}

void MultiViewFuttrackerMainWindow::showImage(QImage img)
{

    this->ui->label_frame->setPixmap(QPixmap::fromImage(img));

}

void MultiViewFuttrackerMainWindow::keyPressEvent(QKeyEvent *event)
{
    this->focusPolicy();

    if(event->matches(QKeySequence::Open)){
        QString path = QFileDialog::getOpenFileName(0,"Abrir Vídeo", "", "MP4 (*.mp4);;MPEG (*.mpg *.mpeg *.MPG *.MPEG);;AVI (*.avi *.AVI)");
        emit openVideo(path);
    }

    if(event->matches(QKeySequence::Close)|| event->key()==Qt::Key_Escape){
        emit this->close();
    }

    if(event->key() == Qt::Key_Space){
        emit playPauseVideo();
    }

}

void MultiViewFuttrackerMainWindow::mousePressEvent(QMouseEvent* event)
{
    QPoint p = this->ui->label_frame->mapFromParent(event->pos());
    QSize s = this->ui->label_frame->size();
    if(p.x() >= 0 && p.y() >= 0 && p.x() < s.width() && p.y() < s.height()){
        cv::Vec<int,5> point;

        point[0] = p.x();
        point[1] = p.y();

        std::cout<<point<<std::endl;



    }
}

void MultiViewFuttrackerMainWindow::mouseMoveEvent(QMouseEvent* event)
{
    QPoint p = this->ui->label_frame->mapFromParent(event->pos());
    QSize s = this->ui->label_frame->size();
    std::cout<<p.x()<<", "<<p.y()<<std::endl;
    if(p.x() >= 0 && p.y() >= 0 && p.x() < s.width() && p.y() < s.height()){
        std::stringstream ss;
        ss << "["<<p.x()<<", "<<p.y()<<"]";
        this->ui->label_2->setText(ss.str().c_str());
    }
}
