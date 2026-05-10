#ifndef PMEDIAN_H
#define PMEDIAN_H

#include <vector>
#include <set>
#include <map>
#include <random>
#include "ievaluator.h"
#include "../Model/distancematrix.h"
#include "../Common/dtos.h"

struct NodeDataComparator
{
    bool operator()(const NodeData& first, const NodeData& second) const
    {
        return first._id < second._id;
    }
};

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

struct PMedianSolutionView : ISolution
{
    std::map<NodeData, NodeData, NodeDataComparator> assignments;
    std::set<NodeData, NodeDataComparator>           selectedStorages;
};

class PMedianEvaluator : public IEvaluator
{
public:
    PMedianEvaluator(const PMedianConfig& config, std::map<int, Node>& nodes);

    std::shared_ptr<ISolution> initialSolution() const override;

    std::shared_ptr<ISolution> getNeighbor(ISolution& currentSolution) const override;

    void evaluate(ISolution& solution) const override;

private:
    mutable std::mt19937        _rng;
    const PMedianConfig&        _config;
    const DistanceMatrix        _distMatrix;
    std::vector<Node*>          _storages;
    std::vector<Node*>          _customers;
};

#endif // PMEDIAN_H
