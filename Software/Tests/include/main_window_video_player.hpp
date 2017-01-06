#ifndef MAIN_WINDOW_VIDEO_PLAYER_HPP
#define MAIN_WINDOW_VIDEO_PLAYER_HPP

#include <QMainWindow>

namespace Ui {
    class MainWindowVideoPlayer;
}

class MainWindowVideoPlayer : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindowVideoPlayer(QWidget *parent = 0);
        ~MainWindowVideoPlayer();

    private:
        Ui::MainWindowVideoPlayer *ui;
};

#endif // MAIN_WINDOW_VIDEO_PLAYER_HPP
