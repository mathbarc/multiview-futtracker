#include "video_grabber.hpp"

VideoGrabber::VideoGrabber(std::string path)
    : QThread()
{
    this->cap.open(path);
    if(!this->cap.isOpened()){
        throw std::string("Erro ao abrir o arquivo");
    }
}


VideoGrabber::VideoGrabber(int id)
{
    this->cap.open(id);
    if(!this->cap.isOpened()){
        throw std::string("Erro ao abrir o arquivo");
    }
}

VideoGrabber::~VideoGrabber()
{
    if(this->cap.isOpened()){
        this->cap.release();
    }
}
