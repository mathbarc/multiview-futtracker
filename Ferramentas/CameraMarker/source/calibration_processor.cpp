#include "calibration_processor.hpp"

const int CalibrationProcessor::HOMOGRAPHY = 0;
const int CalibrationProcessor::ZHENG = 1;

CalibrationProcessor::CalibrationProcessor(std::string path, CalibrationData input, int method)
    : path(path)
    , input(input)
    , method(method)
{ }

void CalibrationProcessor::run()
{

}
