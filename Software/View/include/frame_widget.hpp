#ifndef FRAME_WIDGET_HPP
#define FRAME_WIDGET_HPP

#include <QWidget>
#include <opencv2/core/core.hpp>

namespace Ui {
class FrameWidget;
}

class FrameWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit FrameWidget(QString widgetName, QWidget *parent = 0);
        ~FrameWidget();

    private:
        Ui::FrameWidget *ui;

    public slots:
        void showFrame(const cv::Mat3b& frame);

};

#endif // FRAME_WIDGET_HPP
