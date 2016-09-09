#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "cameramarker.h"
#include <QObject>

class controller : public QObject
{
	Q_OBJECT

	private:
		CameraMarker* window;

	public:
		controller();
		~controller();
};

#endif
