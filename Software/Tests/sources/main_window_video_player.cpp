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
    nVideo(0)
{
    ui->setupUi(this);
    connect(this->processor,SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),this,SLOT(showResult(cv::Mat3b,cv::Mat1b)));
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
        disconnect(this->processor,SIGNAL(resultFrame(cv::Mat3b,cv::Mat1b)),this,SLOT(showResult(cv::Mat3b,cv::Mat1b)));
        delete this->processor;
        this->processor = nullptr;
    }
    if(writer.isOpened())
    {
        writer.release();
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

        if(writer.isOpened())
        {
            writer.release();
        }

        this->grabber = new VideoGrabber(path.toStdString());
        connect(this->grabber,SIGNAL(nextFrame(cv::Mat3b)),this->processor,SLOT(queueFrame(cv::Mat3b)));

        cv::Size fs = this->grabber->getFrameSize();
        std::cout<<fs<<std::endl;
        writer.open(std::to_string(nVideo)+".mpeg",CV_FOURCC('M','P','E','G'),30,cv::Size(fs.width*2, fs.height),true);
        nVideo++;
        this->grabber->start();
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
}

void MainWindowVideoPlayer::showResult(cv::Mat3b img, cv::Mat1b result)
{
    cv::Mat3b is, rim;
    cv::cvtColor(result, rim, CV_GRAY2BGR);
    is.create(rim.cols*2, rim.rows);
    cv::hconcat(img,rim,is);
    cvToQImage(is);
    this->writer.write(is);
}

void MainWindowVideoPlayer::cvToQImage(cv::Mat3b img)
{
    QImage to_show(img.cols, img.rows, QImage::Format_ARGB32);
    cv::Vec3b* v;
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
