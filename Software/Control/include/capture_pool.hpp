#ifndef CAPTURE_POOL
#define CAPTURE_POOL

#include <QThread>
#include <QList>
#include <QSharedPointer>

#include "view.hpp"
#include "frame_widget.hpp"
#include "map_widget.hpp"
#include "gaussian_mixture_detector.hpp"

class CapturePool : public QObject
{
    Q_OBJECT
    public:
        CapturePool(const cv::FileNode& config);
        ~CapturePool();
        QList< QSharedPointer<QWidget> > getWidgets() const;

    private:
        QList< QSharedPointer<View> > grabberPool;
        QList< QSharedPointer<FrameWidget> > widgets;
        QSharedPointer<GaussianMixtureDetector> detector;
        QSharedPointer<MapWidget> resultWidget;

    signals:
        void setFlag(bool flag);

    public slots:
        void start();
        void showColorBGS(bool flag);
        void interrupt();
};

#endif
