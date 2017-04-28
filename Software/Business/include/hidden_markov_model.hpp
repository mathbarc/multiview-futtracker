#ifndef HIDDEN_MARKOV_MODEL_HPP
#define HIDDEN_MARKOV_MODEL_HPP

#include <QThread>
#include <QQueue>
#include <QMutex>

#include "common_data_structures.hpp"
#include "occupation_map.hpp"

class HiddenMarkovModel : public QThread
{
    Q_OBJECT
    public:
        HiddenMarkovModel(const cv::FileNode& config, int numberOfCaptures);


    private:
        const int numberOfCaptures;
        QMutex queueMutex;
        std::vector< QQueue<DetectionResult> > captureResults;
        OccupationMap occMap;



    public slots:
        void receiveResults(const DetectionResult& detections, const int captureId);



};

#endif // HIDDEN_MARKOV_MODEL_HPP
