#ifndef CAPTURE_POOL
#define CAPTURE_POOL

#include <QThread>
#include <QList>
#include <QSharedPointer>

#include "video_grabber.hpp"
#include "video_processor.hpp"

class CapturePool : public QObject
{
    Q_OBJECT
    public:
        CapturePool(const cv::FileNode& config);
        void start();

    private:
        QList< QSharedPointer<VideoGrabber> > grabberPool;
        QList< QSharedPointer<VideoProcessor> > videoProcessorPool;
};

#endif
