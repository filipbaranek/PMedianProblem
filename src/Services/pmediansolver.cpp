#include "pmediansolver.h"


PMedianSolution PMedianSolver::solve(const PMedianConfig&            pmedianConfig,
                                     const SimulatedAnnealingConfig& simAnnealConfig,
                                     std::map<int, Node>&            nodes)
{
    PMedianEvaluator   evaluator(pmedianConfig, nodes);
    SimulatedAnnealing simAnneal(simAnnealConfig);

    std::shared_ptr<PMedianSolution> solution =
        std::dynamic_pointer_cast<PMedianSolution>(simAnneal.optimize(evaluator));

    return *solution;
}
