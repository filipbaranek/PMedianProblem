#include "pmedianevaluator.h"
#include "../Model/node.h"
#include <stdexcept>

namespace
{

enum class NeighborhoodType
{
    ADD         = 0,
    REMOVE      = 1,
    EXCHANGE    = 2
};

} // namespace

PMedianEvaluator::PMedianEvaluator(const PMedianConfig& config, std::map<int, Node>& nodes)
    : _config(config)
    , _distMatrix(nodes)
{
    if (config.p > nodes.size())
    {
        throw std::invalid_argument("p is greater than available storage nodes.");
    }

    std::random_device rd;
    _rng.seed(rd());

    _customers.reserve(nodes.size());
    _storages.reserve(nodes.size());

    for(auto& [id, node] : nodes)
    {
        if(node.type() == NodeType::CUSTOMER)
        {
            _customers.push_back(&node);
        }
        else if (node.type() == NodeType::STORAGE)
        {
            _storages.push_back(&node);
        }
    }
}

std::shared_ptr<ISolution> PMedianEvaluator::initialSolution() const
{
    std::uniform_int_distribution rand(0, static_cast<int>(_storages.size() - 1));

    auto solution       = std::make_shared<PMedianSolution>();
    Node* randomStorage = _storages.at(rand(_rng));

    solution->selectedStorages.insert(randomStorage);
    solution->totalCost += randomStorage->fixedCosts();

    for (auto* customer : _customers)
    {
        solution->assignments[customer] = randomStorage;
        solution->totalCost             += _distMatrix.distance(customer->id(), randomStorage->id());
    }

    return solution;
}

std::shared_ptr<ISolution> PMedianEvaluator::getNeighbor(ISolution& currentSolution) const
{
    static std::uniform_int_distribution randNeighborhood(
        static_cast<int>(NeighborhoodType::ADD), static_cast<int>(NeighborhoodType::EXCHANGE));
    static std::uniform_int_distribution randStorage(0, static_cast<int>(_storages.size() - 1));

    auto& currentSol              = dynamic_cast<PMedianSolution&>(currentSolution);
    auto newSolution              = std::make_shared<PMedianSolution>(currentSol);
    NeighborhoodType neighborhood = static_cast<NeighborhoodType>(randNeighborhood(_rng));

    int maxStorages  = _storages.size();
    int currentCount = newSolution->selectedStorages.size();
    int p            = _config.p;

    if (maxStorages <= 1)
    {
        return newSolution;
    }
    if (neighborhood == NeighborhoodType::ADD && currentCount >= p)
    {
        neighborhood = NeighborhoodType::EXCHANGE;
    }
    if (neighborhood == NeighborhoodType::REMOVE && currentCount <= 1)
    {
        if (currentCount < p)
        {
            neighborhood = NeighborhoodType::ADD;
        }
        else
        {
            neighborhood = NeighborhoodType::EXCHANGE;
        }
    }
    if (neighborhood == NeighborhoodType::EXCHANGE && currentCount >= maxStorages)
    {
        neighborhood = NeighborhoodType::REMOVE;
    }

    switch (neighborhood)
    {
    case NeighborhoodType::ADD:
    {
        Node* newStorage{};
        do
        {
            newStorage = _storages.at(randStorage(_rng));
        } while (newSolution->selectedStorages.contains(newStorage));

        newSolution->selectedStorages.insert(newStorage);
        break;
    }
    case NeighborhoodType::REMOVE:
    {
        std::uniform_int_distribution randStorageRemove(0, currentCount - 1);
        auto it = newSolution->selectedStorages.begin();
        std::advance(it, randStorageRemove(_rng));

        newSolution->selectedStorages.erase(it);
        break;
    }
    case NeighborhoodType::EXCHANGE:
    {
        std::uniform_int_distribution randStorageRemove(0, currentCount - 1);
        auto it = newSolution->selectedStorages.begin();
        std::advance(it, randStorageRemove(_rng));
        Node* storageToRemove = *it;

        Node* storageToAdd{};
        do
        {
            storageToAdd = _storages.at(randStorage(_rng));
        } while (newSolution->selectedStorages.contains(storageToAdd));

        newSolution->selectedStorages.erase(storageToRemove);
        newSolution->selectedStorages.insert(storageToAdd);
        break;
    }
    default:
        break;
    }

    evaluate(*newSolution);

    return newSolution;
}

void PMedianEvaluator::evaluate(ISolution& solution) const
{
    auto& pmedianSolution = dynamic_cast<PMedianSolution&>(solution);
    pmedianSolution.assignments.clear();

    std::set<Node*> actuallyUsedStorages;

    double cost = 0.0;

    for (auto* customer : _customers)
    {
        Node* bestStorage{};
        double minDistance = std::numeric_limits<double>::infinity();

        for (auto* storage : pmedianSolution.selectedStorages)
        {
            double dist = _distMatrix.distance(customer->id(), storage->id()) * _config.transportCosts;
            if (dist < minDistance)
            {
                minDistance = dist;
                bestStorage = storage;
            }
        }

        cost += minDistance;

        if (bestStorage != nullptr)
        {
            pmedianSolution.assignments[customer] = bestStorage;
            actuallyUsedStorages.insert(bestStorage);
        }
    }

    for (auto* storage : actuallyUsedStorages)
    {
        cost += storage->fixedCosts();
    }

    pmedianSolution.selectedStorages = std::move(actuallyUsedStorages);
    pmedianSolution.totalCost = cost;
}
