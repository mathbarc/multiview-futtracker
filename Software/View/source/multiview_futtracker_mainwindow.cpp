#include "multiview_futtracker_mainwindow.hpp"
#include "ui_multiview_futtracker_mainwindow.h"
#include <QMdiSubWindow>
#include <QResizeEvent>
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
        widgets[i]->resize(QSize(sw.width()-15,sw.height()-40));

        sub->setWidget(widgets[i].data());
        sub->setWindowTitle(widgets[i]->getWindowName());
        sub->setGeometry((i%ncols)*winc,(i/ncols)*hinc,sw.width(),sw.height());

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

void MultiviewFuttrackerMainWindow::resize(const QSize& size)
{
    QSize mdiAreaSize(size.width()-(this->ui->groupBox->width()+30), size.height()-10);
    QSize groupSize = this->ui->groupBox->size();
    this->ui->mdiArea->resize(mdiAreaSize);
    this->ui->groupBox->setGeometry(mdiAreaSize.width()+20, this->ui->groupBox->y(), groupSize.width(), groupSize.height());

    QList<QMdiSubWindow*> subWindows = this->ui->mdiArea->subWindowList();

    int ncols, nrows;
    if(subWindows.size()<3)
    {
        ncols = subWindows.size();
        nrows = 1;
    }
    else if(subWindows.size()==3)
    {
        ncols = 2;
        nrows = 2;
    }
    else
    {
        ncols = (subWindows.size()/2) + (subWindows.size()%2);
        nrows = subWindows.size()/ncols;
    }


    QSize sw(size.width()/ncols, size.height()/nrows);
    float winc = size.width() / (ncols);
    float hinc = size.height() / (nrows);

    for(int i = 0; i<subWindows.size(); i++)
    {
        subWindows[i]->setGeometry((i%ncols)*winc,(i/ncols)*hinc,sw.width(),sw.height());
        subWindows[i]->widget()->resize(QSize(sw.width()-15,sw.height()-40));
    }

}

void MultiviewFuttrackerMainWindow::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    QSize mdiAreaSize(size.width()-(this->ui->groupBox->width()+30), size.height()-10);
    QSize groupSize = this->ui->groupBox->size();
    this->ui->mdiArea->resize(mdiAreaSize);
    this->ui->groupBox->setGeometry(mdiAreaSize.width()+20, this->ui->groupBox->y(), groupSize.width(), groupSize.height());

    QList<QMdiSubWindow*> subWindows = this->ui->mdiArea->subWindowList();

    int ncols, nrows;
    if(subWindows.size()<3)
    {
        ncols = subWindows.size();
        nrows = 1;
    }
    else if(subWindows.size()==3)
    {
        ncols = 2;
        nrows = 2;
    }
    else
    {
        ncols = (subWindows.size()/2) + (subWindows.size()%2);
        nrows = subWindows.size()/ncols;
    }


    QSize sw(size.width()/ncols, size.height()/nrows);
    float winc = size.width() / (ncols);
    float hinc = size.height() / (nrows);

    for(int i = 0; i<subWindows.size(); i++)
    {
        subWindows[i]->setGeometry((i%ncols)*winc,(i/ncols)*hinc,sw.width(),sw.height());
        subWindows[i]->widget()->resize(QSize(sw.width()-15,sw.height()-40));
    }


    QMainWindow::resizeEvent(event);
}
