#include "imagebuffer.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

int ImageBuffer::nVideo=0;

ImageBuffer::ImageBuffer(cv::Size fs)
    :imgs()
{
    writer.open(std::to_string(nVideo)+".avi",CV_FOURCC('D','I','V','X'),30,cv::Size(fs.width*2, fs.height),true);
    nVideo++;
}

void ImageBuffer::run()
{
    cv::Mat3b im;
    while(!this->isInterruptionRequested())
    {
        this->mutex.lock();

        if(!this->imgs.empty())
            im = this->imgs.dequeue();
        else
            im = cv::Mat3b();

        this->mutex.unlock();
        if(!im.empty())
        {
            emit show(im);
            writer<<im;
        }

        this->msleep(10);

    }

}

void ImageBuffer::enqueue(const cv::Mat3b& img, const cv::Mat1b& fgmask)
{
    cv::Mat3b is, rim;
    cv::cvtColor(fgmask, rim, CV_GRAY2BGR);
    is.create(rim.cols*2, rim.rows);
    cv::hconcat(img,rim,is);
    mutex.lock();
    this->imgs.enqueue(is);
    mutex.unlock();

}

ImageBuffer::~ImageBuffer()
{
    if(this->writer.isOpened())
    {
        this->writer.release();
    }
}
