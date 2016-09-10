#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "cameramarker.h"
#include "video_processor.hpp"
#include <QObject>

class Controller : public QObject
{
	Q_OBJECT

	private:
		CameraMarker* window;
        VideoProcessor* video_thread;


    private slots:
        void openVideo(QString path);
        void genCalibFile(QString path);
        void close();

	public:
        Controller();
        ~Controller();
};

#endif
