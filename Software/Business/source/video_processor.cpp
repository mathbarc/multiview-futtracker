#include "video_processor.hpp"

VideoProcessor::VideoProcessor()
    :QThread()
{}


void VideoProcessor::queueFrame(const cv::Mat3b &frame)
{
    mutex.lock();

    this->queue.enqueue(frame);

    mutex.unlock();
}
