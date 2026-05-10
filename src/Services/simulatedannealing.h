#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <random>
#include <memory>
#include "ievaluator.h"

class Node;

struct SimulatedAnnealingConfig
{
    double startTemp   = 1000.0;
    double minTemp     = 0.01;
    double alpha       = 0.95;
    int    iterPerTemp = 100;
};

class SimulatedAnnealing {
public:
    SimulatedAnnealing(const SimulatedAnnealingConfig& config);

    std::shared_ptr<ISolution> optimize(const IEvaluator& evaluator);

private:
    bool accept(double currentCost, double newCost, double temperature);

private:
    double       _startTemp;
    double       _minTemp;
    double       _alpha;
    int          _iterPerTemp;
    std::mt19937 _rng;
};

#endif // SIMULATEDANNEALING_H
