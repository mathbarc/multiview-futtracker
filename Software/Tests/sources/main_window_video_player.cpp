#include "main_window_video_player.hpp"
#include "ui_main_window_video_player.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include <QFileDialog>

MainWindowVideoPlayer::MainWindowVideoPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowVideoPlayer),
    grabber(nullptr),
    processor(new VideoProcessorBGS(100,40,2e-3, cv::Size(3,3), 1.2)),
    imb(nullptr)
{
    ui->setupUi(this);

    this->processor->start();
}

MainWindowVideoPlayer::~MainWindowVideoPlayer()
{
    std::cout<<"~MainWindowVideoPlayer ... ";
    interruptVideoGrabber();
    if(this->processor!=nullptr)
    {
        this->processor->requestInterruption();
        this->processor->wait();
        delete this->processor;
        this->processor = nullptr;
    }

    delete ui;
    std::cout<<"done"<<std::endl;
}

void MainWindowVideoPlayer::on_actionAbrir_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "Arquivo de Vídeo", "", "*.mpg;;*.mp4;;*.*" );

    if(path!="")
    {
        interruptVideoGrabber();

        this->grabber = new VideoGrabber(path.toStdString());
        connect(this->grabber,SIGNAL(nextFrame(cv::Mat3b)),this->processor,SLOT(queueFrame(cv::Mat3b)));

        cv::Size fs = this->grabber->getFrameSize();
        this->imb = new ImageBuffer(fs);
        connect(this->processor,SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),this->imb,SLOT(enqueue(cv::Mat3b,cv::Mat1b)));
        connect(this->imb,SIGNAL(show(cv::Mat3b)),this,SLOT(showResult(cv::Mat3b)));
//        std::cout<<fs<<std::endl;

        this->grabber->start();
        this->imb->start();
    }
}

void inline MainWindowVideoPlayer::interruptVideoGrabber()
{
    if(this->grabber!=nullptr)
    {
        this->grabber->requestInterruption();
        this->grabber->wait();
        disconnect(this->grabber,SIGNAL(nextFrame(cv::Mat3b)),this->processor,SLOT(queueFrame(cv::Mat3b)));
        delete this->grabber;
        this->grabber=nullptr;
    }
    if(this->imb!=nullptr)
    {
        disconnect(this->processor,SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),this->imb,SLOT(enqueue(cv::Mat3b,cv::Mat1b)));
        this->imb->requestInterruption();
        this->imb->wait();
        disconnect(this->imb,SIGNAL(show(cv::Mat3b)),this,SLOT(showResult(cv::Mat3b)));
        delete this->imb;
        this->imb = nullptr;
    }
}

void MainWindowVideoPlayer::showResult(const cv::Mat3b &img)
{
    cvToQImage(img);
}

void MainWindowVideoPlayer::cvToQImage(const cv::Mat3b& img)
{
    QImage to_show(img.cols, img.rows, QImage::Format_ARGB32);
    const cv::Vec3b* v;
    QRgb* v_show;
    for(int i = 0; i<img.rows; i++)
    {
        v = img.ptr<cv::Vec3b>(i);
        v_show = (QRgb*)to_show.scanLine(i);
        for(int j = 0; j<img.cols; j++)
        {
            v_show[j] = qRgba(v[j][2],v[j][1],v[j][0],255);
        }
    }
    this->ui->label->setPixmap(QPixmap::fromImage(to_show));
}
