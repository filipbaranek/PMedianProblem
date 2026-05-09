#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <random>
#include <memory>
#include "ievaluator.h"

class Node;

struct SimulatedAnnealingConfig
{
    double startTemp;
    double minTemp;
    double alpha;
    int    iterPerTemp;
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
