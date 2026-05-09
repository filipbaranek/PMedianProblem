#ifndef PMEDIAN_H
#define PMEDIAN_H

#include <vector>
#include <set>
#include <map>
#include <random>
#include "ievaluator.h"
#include "../Model/distancematrix.h"

struct PMedianConfig
{
    int    p;
    double transportCosts;
};

struct PMedianSolution : ISolution
{
    std::map<Node*, Node*> assignments;
    std::set<Node*>        selectedStorages;
};

class PMedianEvaluator : public IEvaluator
{
public:
    PMedianEvaluator(const PMedianConfig& config, const std::map<int, Node*>& nodes);

    std::shared_ptr<ISolution> initialSolution() const override;

    std::shared_ptr<ISolution> getNeighbor(ISolution& currentSolution) const override;

    void evaluate(ISolution& solution) const override;

private:
    mutable std::mt19937        _rng;
    const std::map<int, Node*>& _nodes;
    const PMedianConfig&        _config;
    const DistanceMatrix        _distMatrix;
    std::vector<Node*>          _storages;
    std::vector<Node*>          _customers;
};

#endif // PMEDIAN_H
