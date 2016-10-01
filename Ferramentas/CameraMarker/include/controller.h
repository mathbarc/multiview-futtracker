#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "cameramarker.h"
#include "video_processor.hpp"
#include <opencv2/core/core.hpp>
#include <QObject>
#include <vector>

class Controller : public QObject
{
	Q_OBJECT

	private:
		CameraMarker* window;
        VideoProcessor* video_thread;
        std::vector<CalibrationMarker> markers;
        QImage cvToQImage(cv::Mat img);
        cv::Mat recentFrame;


    private slots:
        void openVideo(QString path);
        void genCalibFile(QString path);
        void addCalibrationMarker(CalibrationMarker cm);
        void close();
        void showImage(cv::Mat img);

    signals:
        void insertOnTable(CalibrationMarker cm);
        void showImage(QImage img);

	public:
        Controller();
        ~Controller();
};

#endif
