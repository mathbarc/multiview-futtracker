#include "calibration_processor.hpp"
#include <opencv2/calib3d.hpp>

const int CalibrationProcessor::HOMOGRAPHY = 0;
const int CalibrationProcessor::ZHENG = 1;

CalibrationProcessor::CalibrationProcessor(std::string path, CalibrationData input, cv::Size size, int method)
    : path(path)
    , input(input)
    , method(method)
    , size(size)
{ }

void CalibrationProcessor::run()
{

    switch (method)
    {
        case CalibrationProcessor::ZHENG:
                this->zhengCalibration();
            break;
        case CalibrationProcessor::HOMOGRAPHY:
                this->homography();
            break;
        default:
            break;
    }

}

void CalibrationProcessor::zhengCalibration()
{
    std::vector< std::vector<cv::Point2f> > image;
    std::vector< std::vector<cv::Point3f> > world;

    std::vector< cv::Mat > rvecs, tvecs;

    image.push_back(this->input.image);
    world.push_back(this->input.world);

    cv::Mat calibrationMatrix, distortionCoeff;

    cv::calibrateCamera(world, image, this->size, calibrationMatrix,
                        distortionCoeff, rvecs, tvecs,
                        CV_CALIB_ZERO_TANGENT_DIST );

    cv::FileStorage file(path, cv::FileStorage::WRITE);
    file<<"calibration"<<calibrationMatrix;
    file<<"distortion_coefficients"<<distortionCoeff;
    file.release();

}


void CalibrationProcessor::homography()
{

}
