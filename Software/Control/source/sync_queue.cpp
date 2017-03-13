#include "sync_queue.hpp"

SyncQueue::SyncQueue(QObject *parent) : QObject(parent)
{

}

bool SyncQueue::hasImage()
{
    bool has = false;
    if(mutex.tryLock())
    {
        has = (this->imgs.size()>0);
        mutex.unlock();
    }


    return has;
}

void SyncQueue::dequeue(cv::Mat3b &img, cv::Mat1b &fore)
{
    std::pair<cv::Mat3b, cv::Mat1b> next;
    mutex.lock();
    next = this->imgs.dequeue();
    mutex.unlock();

    next.first.copyTo(img);
    next.second.copyTo(fore);
}

void SyncQueue::enqueue(const cv::Mat3b &img, const cv::Mat1b &fore)
{
    std::pair<cv::Mat3b, cv::Mat1b> toEnqueue;
    toEnqueue.first = img;
    toEnqueue.second = fore;

    mutex.lock();
    this->imgs.enqueue(toEnqueue);
    mutex.unlock();
}
