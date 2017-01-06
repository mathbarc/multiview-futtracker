#include "main_window_video_player.hpp"
#include "ui_main_window_video_player.h"

MainWindowVideoPlayer::MainWindowVideoPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowVideoPlayer)
{
    ui->setupUi(this);
}

MainWindowVideoPlayer::~MainWindowVideoPlayer()
{
    delete ui;
}
