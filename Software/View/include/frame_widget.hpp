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
        explicit FrameWidget(QString windowName, QWidget *parent = 0);
        ~FrameWidget();
        QString getWindowName() const;
        void resize(const QSize& size);

    private:
        Ui::FrameWidget *ui;
        bool showGray;
        QString windowName;

    public slots:
        void showFrame(const cv::Mat3b& frame, const cv::Mat1b& bgs);
        void setFlag(bool flag);



};

#endif // FRAME_WIDGET_HPP
