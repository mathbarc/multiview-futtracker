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
    delete ui;
}

void MultiviewFuttrackerMainWindow::addSubWindows(const QList<QSharedPointer<FrameWidget> > &widgets)
{
//    QMdiSubWindow* sub;
    for(int i = 0; i<widgets.size();i++)
    {
//        sub = new QMdiSubWindow(this->ui->mdiArea);
//        widgets[i]->setParent(sub);
//        sub->setWidget(widgets[i].data());
//        sub->setAttribute(Qt::WA_DeleteOnClose);
        this->ui->mdiArea->addSubWindow(widgets[i].data());
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
