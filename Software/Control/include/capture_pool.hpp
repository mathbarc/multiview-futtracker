#include <QThread>
#include <boost/property_tree/ptree.hpp>
#include <QList>

#include "video_grabber.hpp"

class CapturePool : public QThread
{
    public:
        CapturePool(const boost::property_tree::ptree& config);
        void run();

    private:
        QList<VideoGrabber*> pool;




};
