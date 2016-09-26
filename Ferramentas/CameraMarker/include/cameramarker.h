#ifndef CAMERAMARKER_H
#define CAMERAMARKER_H

#include <QtWidgets/QMainWindow>

namespace Ui{
    class CameraMarker;
}

class CameraMarker : public QMainWindow
{
	Q_OBJECT

    public:
        explicit CameraMarker(QWidget *parent = 0);
        ~CameraMarker();

    signals:
        void openVideo(QString path);
        void genCalibFile(QString path);
        void playPauseVideo();

    public slots:
        void showImage(QImage img);

    private slots:
        void on_actionAbrir_Video_triggered();

    private:
        Ui::CameraMarker* ui;

    protected:
        void keyPressEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent* event);
};

#endif // CAMERAMARKER_H
