#ifndef HIDDEN_MARKOV_MODEL_HPP
#define HIDDEN_MARKOV_MODEL_HPP

#include <QThread>
#include <QQueue>
#include <QMutex>

#include "common_data_structures.hpp"
#include "occupation_map.hpp"
#include <dlib/optimization.h>

class HiddenMarkovModel : public QThread
{
    Q_OBJECT
    public:
        HiddenMarkovModel(const cv::FileNode& config, int numberOfCaptures);
        ~HiddenMarkovModel();

    private:
        const int numberOfCaptures;
        QMutex queueMutex;
        std::vector< QQueue<DetectionResult> > captureResults;
        OccupationMap occMap;
        void run();

    public slots:
        void receiveResults(const DetectionResult& detections, const int captureId);



};

#endif // HIDDEN_MARKOV_MODEL_HPP
