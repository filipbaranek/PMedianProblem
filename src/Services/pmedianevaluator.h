#ifndef PMEDIAN_H
#define PMEDIAN_H

#include <vector>
#include <set>
#include <map>
#include <limits>
#include <random>
#include "ievaluator.h"
#include "distancematrix.h"

struct PMedianConfig
{
    const int    p;
    const double transportCosts;
};

struct PMedianSolution : ISolution
{
    std::map<Node*, Node*> assignments;
    std::set<Node*>        selectedStorages;
    double                 totalCost = std::numeric_limits<double>::infinity();
};

class PMedianEvaluator : public IEvaluator
{
public:
    PMedianEvaluator(const PMedianConfig& config, const std::map<int, Node*>& nodes);

    std::shared_ptr<ISolution> initialSolution() const override;

    std::shared_ptr<ISolution> getNeighbor(ISolution& currentSolution) const override;

    void evaluate(ISolution& solution) const override;

private:
    //

private:
    mutable std::mt19937        _rng;
    const std::map<int, Node*>& _nodes;
    const PMedianConfig&        _config;
    const DistanceMatrix        _distMatrix;
    std::vector<Node*>          _storages;
    std::vector<Node*>          _customers;
};

#endif // PMEDIAN_H
