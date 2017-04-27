#include <exception>

#include "view.hpp"
#include "file_view.hpp"


View::View(const cv::FileNode &config)
    :QThread()
{
    this->processor.reset(VideoProcessor::getInstance(config["video_processor"]));
}

View* View::createView(const cv::FileNode& config)
{
    std::string type = (std::string)config["type"];
    if(type == "file")
    {
        return new FileView(config);
    }
    else
    {
        throw std::logic_error("Tipo de captura indisponível: "+type);
    }

}

View::~View()
{
}
