#ifndef FILEVIEW_HPP
#define FILEVIEW_HPP

#include "view.hpp"
#include <opencv2/highgui/highgui.hpp>

class FileView : public View
{
public:
    FileView(const cv::FileNode& config);
    ~FileView();

private:
    void run();
    cv::VideoCapture capture;


protected slots:
    void requestCapture();

};

#endif // FILEVIEW_H
