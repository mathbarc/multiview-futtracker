#ifndef MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP
#define MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>

namespace Ui{
    class MultiViewFuttrackerMainWindow;
}

class MultiViewFuttrackerMainWindow : public QMainWindow
{
	Q_OBJECT

    public:
        explicit MultiViewFuttrackerMainWindow(QWidget *parent = 0);
        ~MultiViewFuttrackerMainWindow();

    signals:
        void openVideo(QString path);
        void genCalibFile(QString path);
        void playPauseVideo();

    public slots:
        void showImage(QImage img);

    private slots:
        void on_actionAbrir_Video_triggered();

    private:
        Ui::MultiViewFuttrackerMainWindow* ui;

    protected:
        void keyPressEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

};

#endif // MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP
