#ifndef CAPTURE_POOL
#define CAPTURE_POOL

#include <QThread>
#include <QList>
#include <QSharedPointer>

#include "video_grabber.hpp"
#include "video_processor.hpp"
#include "frame_widget.hpp"
#include "sync_queue.hpp"

class CapturePool : public QThread
{
    Q_OBJECT
    public:
        CapturePool(const cv::FileNode& config);
        ~CapturePool();
        QList< QSharedPointer<FrameWidget> > getWidgets() const;

    private:
        QList< QSharedPointer<VideoGrabber> > grabberPool;
        QList< QSharedPointer<VideoProcessor> > videoProcessorPool;
        QList< QSharedPointer<FrameWidget> > widgets;
        QList< QSharedPointer<SyncQueue> > queues;
        void run();


    signals:
        void setFlag(bool flag);

    public slots:
        void showColorBGS(bool flag);
//        void interrupt();
};

#endif
