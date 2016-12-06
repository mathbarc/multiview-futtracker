#include "video_grabber.hpp"
#include "video_processor.hpp"
#include "video_show.hpp"


int main(int argc, char* argv[])
{
    VideoShow vs;
    vs.go();

    cv::waitKey(0);



    return 1;
}
