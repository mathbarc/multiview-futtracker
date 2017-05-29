#include "multiview_futtracker_mainwindow.hpp"
#include "ui_multiview_futtracker_mainwindow.h"
#include <QMdiSubWindow>
#include <iostream>

MultiviewFuttrackerMainWindow::MultiviewFuttrackerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MultiviewFuttrackerMainWindow)
{
    ui->setupUi(this);
}

MultiviewFuttrackerMainWindow::~MultiviewFuttrackerMainWindow()
{
    std::cout<<"~MultiviewFuttrackerMainWindow"<<std::endl;
    delete ui;
    std::cout<<"~MultiviewFuttrackerMainWindow done"<<std::endl;
}

void MultiviewFuttrackerMainWindow::addSubWindows(const QList<QSharedPointer<QWidget> > &widgets)
{
    int ncols, nrows;
    if(widgets.size()<3)
    {
        ncols = widgets.size();
        nrows = 1;
    }
    else if(widgets.size()==3)
    {
        ncols = 2;
        nrows = 2;
    }
    else
    {
        ncols = (widgets.size()/2) + (widgets.size()%2);
        nrows = widgets.size()/ncols;
    }


    for(int i = 0; i<widgets.size();i++)
    {

        widgets[i]->setParent(this);
        this->ui->gridLayout_cams->addWidget(widgets[i].data(),i/ncols,i%ncols,1,1);
    }


}

void MultiviewFuttrackerMainWindow::on_radioButton_color_clicked()
{
    emit setViewFlag(true);
}

void MultiviewFuttrackerMainWindow::on_radioButton_foreground_clicked()
{
    emit setViewFlag(false);
}

void MultiviewFuttrackerMainWindow::on_pushButton_clicked()
{
    this->close();
}

void MultiviewFuttrackerMainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_P)
    {
        emit pause();
    }
}
