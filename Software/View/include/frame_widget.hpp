#ifndef FRAME_WIDGET_HPP
#define FRAME_WIDGET_HPP

#include <QWidget>
#include <QResizeEvent>
#include <QGraphicsScene>
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

    private:
        Ui::FrameWidget *ui;
        bool showGray;
        QString windowName;
        QGraphicsScene scene;

    public slots:
        void showFrame(const cv::Mat3b& frame, const cv::Mat1b& bgs);
        void setFlag(bool flag);

    protected:
        void resizeEvent(QResizeEvent* event);
};

#endif // FRAME_WIDGET_HPP
