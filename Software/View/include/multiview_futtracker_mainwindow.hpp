#ifndef MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP
#define MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP

#include <QMainWindow>
#include <QScopedPointer>
#include <QList>
#include <QResizeEvent>
#include "frame_widget.hpp"


namespace Ui {
    class MultiviewFuttrackerMainWindow;
}

class MultiviewFuttrackerMainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MultiviewFuttrackerMainWindow(QWidget *parent = 0);
        void addSubWindows(const QList< QSharedPointer<FrameWidget> >& widgets);
        ~MultiviewFuttrackerMainWindow();

    signals:
        void setViewFlag(bool flag);

    private slots:
        void on_radioButton_color_clicked();
        void on_radioButton_foreground_clicked();

        void on_pushButton_clicked();

    private:
        Ui::MultiviewFuttrackerMainWindow *ui;



};

#endif // MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP
