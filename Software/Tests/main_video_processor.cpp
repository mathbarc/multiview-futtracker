#include "video_grabber.hpp"
#include "video_processor.hpp"
#include "video_show.hpp"

#include <QMetaType>

int main(int argc, char* argv[])
{
    qRegisterMetaType<cv::Mat3b>("cv::Mat3b");
    qRegisterMetaType<cv::Mat1b>("cv::Mat1b");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    VideoShow vs;
    vs.go();

    cv::waitKey(0);



    return 1;
}
