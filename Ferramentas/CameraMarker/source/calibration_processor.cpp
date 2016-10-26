#include "calibration_processor.hpp"
#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
#include <QMessageBox>


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

    std::cout<<"Starting Calibration"<<std::endl;
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

    if(this->input.image.size()<4){
        return;
    }

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
    file<<"type"<<"zheng";
    file<<"calibration"<<calibrationMatrix;
    file<<"distortion_coefficients"<<distortionCoeff;
    file.release();

}


void CalibrationProcessor::homography()
{
    cv::Mat mask;
    cv::Mat homographyMatrix = cv::findHomography(this->input.image,this->input.world, mask);
    cv::FileStorage file(path, cv::FileStorage::WRITE);
    file<<"type"<<"homography";
    file<<"homography"<<homographyMatrix;
    file<<"mask"<<mask;
    file.release();
}
