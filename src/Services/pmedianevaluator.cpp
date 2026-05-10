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
    static std::uniform_int_distribution rand(0, static_cast<int>(_storages.size() - 1));

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
    static std::uniform_int_distribution randStorage(0, static_cast<int>(_storages.size() - 1));
    static std::uniform_int_distribution randNeighborhood(
        static_cast<int>(NeighborhoodType::ADD), static_cast<int>(NeighborhoodType::EXCHANGE));


    auto& currentSol              = dynamic_cast<PMedianSolution&>(currentSolution);
    auto newSolution              = std::make_shared<PMedianSolution>(currentSol);
    NeighborhoodType neighborhood = static_cast<NeighborhoodType>(randNeighborhood(_rng));

    switch (neighborhood)
    {
    case NeighborhoodType::ADD:
    {
        Node* newStorage = _storages.at(randStorage(_rng));
        newSolution->selectedStorages.insert(newStorage);
        break;
    }
    case NeighborhoodType::REMOVE:
    {
        if (newSolution->selectedStorages.size() <= 1)
        {
            Node* newStorage = _storages.at(randStorage(_rng));
            newSolution->selectedStorages.insert(newStorage);
        }
        else
        {
            std::uniform_int_distribution randStorageRemove(0, static_cast<int>(newSolution->selectedStorages.size() - 1));
            newSolution->selectedStorages.erase(_storages.at(randStorageRemove(_rng)));
        }
        break;
    }
    case NeighborhoodType::EXCHANGE:
    {
        if (newSolution->selectedStorages.size() <= 1)
        {
            Node* newStorage = _storages.at(randStorage(_rng));
            newSolution->selectedStorages.insert(newStorage);
        }
        else
        {
            std::uniform_int_distribution randStorageRemove(0, static_cast<int>(newSolution->selectedStorages.size() - 1));
            Node* storageToRemove = _storages.at(randStorageRemove(_rng));
            Node* storageToAdd{};

            do
            {
                storageToAdd = _storages.at(randStorage(_rng));
            } while (storageToRemove == storageToAdd);

            newSolution->selectedStorages.erase(storageToRemove);
            newSolution->selectedStorages.insert(storageToAdd);
        }
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

    double cost = 0.0;
    for (auto* storage : pmedianSolution.selectedStorages)
    {
        cost += storage->fixedCosts();
    }

    pmedianSolution.assignments.clear();
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
        }
    }

    pmedianSolution.totalCost = cost;
}
