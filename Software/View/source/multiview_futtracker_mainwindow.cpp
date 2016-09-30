#include "include/multiview_futtracker_mainwindow.hpp"
#include "ui_multiview_futtracker_mainwindow.h"

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
