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
    for(int i = 0; i<widgets.size();i++)
    {
        sub = new QMdiSubWindow(this->ui->mdiArea, Qt::Window | Qt::CustomizeWindowHint |
                                Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
        widgets[i]->setParent(sub);
        sub->setWidget(widgets[i].data());
        sub->setWindowTitle(widgets[i]->getWindowName());
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
