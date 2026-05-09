#include "simulatedannealing.h"
#include <cmath>

SimulatedAnnealing::SimulatedAnnealing(const SimulatedAnnealingConfig& config)
    : _startTemp(config.startTemp)
    , _minTemp(config.minTemp)
    , _alpha(config.alpha)
    , _iterPerTemp(config.iterPerTemp)
{
    std::random_device rd;
    _rng.seed(rd());
}

std::shared_ptr<ISolution> SimulatedAnnealing::optimize(const IEvaluator& evaluator)
{
    std::shared_ptr<ISolution> currentSol = evaluator.initialSolution();
    std::shared_ptr<ISolution> bestSol    = currentSol;

    double temperature = _startTemp;
    while (temperature > _minTemp)
    {
        for (int i = 0; i < _iterPerTemp; ++i)
        {
            std::shared_ptr<ISolution> neighborSol = evaluator.getNeighbor(*currentSol);

            if (accept(currentSol->totalCost, neighborSol->totalCost, temperature))
            {
                currentSol = neighborSol;
                if (currentSol->totalCost < bestSol->totalCost)
                {
                    bestSol = currentSol;
                }
            }
        }
        temperature *= _alpha;
    }

    return bestSol;
}

bool SimulatedAnnealing::accept(double currentCost, double newCost, double temperature)
{
    static std::uniform_real_distribution<double> rand(0.0, 1.0);

    if (newCost < currentCost)
    {
        return true;
    }

    double acceptanceProbability = std::exp(-(newCost - currentCost) / temperature);

    return rand(_rng) < acceptanceProbability;
}

