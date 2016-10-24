#ifndef CALIBRATION_PROCESSOR_HPP
#define CALIBRATION_PROCESSOR_HPP

#include <QThread>
#include <vector>
#include "data_types.hpp"

class CalibrationProcessor : public QThread
{
    Q_OBJECT
    public:
        CalibrationProcessor(std::string path, CalibrationData input, cv::Size size, int method);
        static const int HOMOGRAPHY;
        static const int ZHENG;

    private:
        CalibrationData input;
        std::string path;
        int method;
        cv::Size size;

        void zhengCalibration();
        void homography();

    public slots:
        void run();

};

#endif // CALIBRATION_PROCESSOR_HPP
