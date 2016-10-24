#ifndef CALIBRATION_PROCESSOR_HPP
#define CALIBRATION_PROCESSOR_HPP

#include <QThread>
#include <vector>
#include "data_types.hpp"

class CalibrationProcessor : public QThread
{
    Q_OBJECT
    public:
        CalibrationProcessor(std::string path, CalibrationData input, int method);
        static const int HOMOGRAPHY;
        static const int ZHENG;

    private:
        CalibrationData input;
        std::string path;
        int method;

    public slots:
        void run();

};

#endif // CALIBRATION_PROCESSOR_HPP
