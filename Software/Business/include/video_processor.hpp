#include <opencv2/core/core.hpp>
#include <QThread>
#include <QQueue>
#include <opencv2/video/video.hpp>


class VideoProcessor : public QThread
{
    Q_OBJECT
    public:
        VideoProcessor();

    private:
        cv::BackgroundSubtractor* bgs;
        QQueue<cv::Mat3b> to_process;

    public slots:


};

