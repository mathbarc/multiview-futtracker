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

private:
    Ui::CameraMarker* ui;

};

#endif // CAMERAMARKER_H
