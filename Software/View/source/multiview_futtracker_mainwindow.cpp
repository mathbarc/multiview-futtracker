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

void MultiviewFuttrackerMainWindow::addSubWindows(const QList<QSharedPointer<FrameWidget> > &widgets)
{
    QMdiSubWindow* sub;
    QSize s = this->ui->mdiArea->size();
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


    QSize sw(s.width()/ncols, s.height()/nrows);
    float winc = s.width() / (ncols);
    float hinc = s.height() / (nrows);

    for(int i = 0; i<widgets.size();i++)
    {
        sub = new QMdiSubWindow(this->ui->mdiArea, Qt::Window | Qt::CustomizeWindowHint |
                                Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
        widgets[i]->setParent(sub);
        widgets[i]->resize(sw);
        sub->setWidget(widgets[i].data());
        sub->setWindowTitle(widgets[i]->getWindowName());
        sub->setGeometry((i%ncols)*winc,(i/ncols)*hinc,sw.width(),sw.height());
        std::cout<<(i%ncols)*winc<<", "<<(i/ncols)*hinc<<std::endl;
//        sub->setAttribute(Qt::WA_LaidOut);
        this->ui->mdiArea->addSubWindow(sub);
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
