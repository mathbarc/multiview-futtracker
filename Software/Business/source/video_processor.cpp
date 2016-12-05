#include "video_processor.hpp"

#include <opencv2/objdetect/objdetect.hpp>

VideoProcessor::VideoProcessor(int history, float threshold )
{
    this->bgs = new cv::BackgroundSubtractorMOG2(history, threshold);
}

void VideoProcessor::run()
{
    cv::Mat3b img;

    mutex.lock();

    img = this->queue.dequeue();

    mutex.unlock();



}

void VideoProcessor::queueFrame(const cv::Mat3b &frame)
{

    mutex.lock();

    this->queue.enqueue(frame);

    mutex.unlock();

}
