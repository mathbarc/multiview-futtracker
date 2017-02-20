#include <QThread>
#include <QList>
#include <QSharedPointer>

#include <boost/property_tree/ptree.hpp>

#include "video_grabber.hpp"
#include "video_processor.hpp"

class CapturePool : public QThread
{
    public:
        CapturePool(const boost::property_tree::ptree& config);
        void run();

    private:
        QList< QSharedPointer<VideoGrabber> > grabberPool;
        QList< QSharedPointer<VideoProcessor> > videoProcessorPool;



};
