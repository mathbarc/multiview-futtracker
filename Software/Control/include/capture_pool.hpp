#ifndef CAPTURE_POOL
#define CAPTURE_POOL

#include <QThread>
#include <QList>
#include <QSharedPointer>

#include "view.hpp"
#include "frame_widget.hpp"
#include "data_processor.hpp"

class CapturePool : public QObject
{
    Q_OBJECT
    public:
        CapturePool(const cv::FileNode& config);
        ~CapturePool();
        QList< QSharedPointer<FrameWidget> > getWidgets() const;

    private:
        QList< QSharedPointer<View> > grabberPool;
        QList< QSharedPointer<FrameWidget> > widgets;
        QSharedPointer<DataProcessor> tracker;

    signals:
        void setFlag(bool flag);

    public slots:
        void start();
        void showColorBGS(bool flag);
        void interrupt();
};

#endif
