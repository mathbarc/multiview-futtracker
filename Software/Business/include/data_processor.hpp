#ifndef HIDDEN_MARKOV_MODEL_HPP
#define HIDDEN_MARKOV_MODEL_HPP

#include <QThread>
#include <QQueue>
#include <QMutex>

#include <queue>
#include "common_data_structures.hpp"
#include "hidden_markov_chain.hpp"

class DataProcessor : public QThread
{
    Q_OBJECT
    public:
        DataProcessor(const cv::FileNode& config, int numberOfCaptures);
        ~DataProcessor();

    private:
        const int numberOfCaptures;
        QMutex queueMutex;
        std::vector< QQueue<DetectionResult> > captureResults;
        HiddenMarkovChain chain;

        int numberOfStates;
        void run();

    public slots:
        void receiveResults(const DetectionResult& detections, const int captureId);
};

#endif // HIDDEN_MARKOV_MODEL_HPP
