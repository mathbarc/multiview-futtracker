#ifndef MAP_WIDGET_HPP
#define MAP_WIDGET_HPP

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <QGraphicsScene>

namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit MapWidget(QString windowName, QWidget *parent = 0);
        ~MapWidget();
        QString getWindowName() const;

    private:
        Ui::MapWidget *ui;
        QString windowName;
        QGraphicsScene scene;

    public slots:
        void showFrame(const cv::Mat1d& frame);

    protected:
        void resizeEvent(QResizeEvent* event);
};

#endif // MAP_WIDGET_HPP
