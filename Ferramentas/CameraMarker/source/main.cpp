#include "cameramarker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CameraMarker w;
	w.show();
	return a.exec();
}
