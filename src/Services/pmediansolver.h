#ifndef PMEDIANSOLVER_H
#define PMEDIANSOLVER_H

#include "pmedianevaluator.h"
#include "simulatedannealing.h"

class PMedianSolver
{
public:
    PMedianSolver() = delete;

    static PMedianSolution solve(const PMedianConfig& pmedianConfig,
                                 const SimulatedAnnealingConfig& simAnnealConfig,
                                 const std::map<int, Node*>& nodes);
};

#endif // PMEDIANSOLVER_H
