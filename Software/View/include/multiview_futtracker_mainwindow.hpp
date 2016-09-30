#ifndef MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP
#define MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class MultiviewFuttrackerMainWindow;
}

class MultiviewFuttrackerMainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MultiviewFuttrackerMainWindow(QWidget *parent = 0);
        ~MultiviewFuttrackerMainWindow();

    private:
        Ui::MultiviewFuttrackerMainWindow *ui;
};

#endif // MULTIVIEW_FUTTRACKER_MAINWINDOW_HPP
