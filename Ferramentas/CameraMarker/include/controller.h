#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "cameramarker.h"
#include "video_processor.hpp"
#include <QObject>
#include <vector>

class Controller : public QObject
{
	Q_OBJECT

	private:
		CameraMarker* window;
        VideoProcessor* video_thread;
        std::vector<CalibrationMarker> markers;


    private slots:
        void openVideo(QString path);
        void genCalibFile(QString path);
        void addCalibrationMarker(CalibrationMarker cm);
        void close();

    signals:
        void insertOnTable(CalibrationMarker cm);

	public:
        Controller();
        ~Controller();
};

#endif
