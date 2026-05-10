#include "gridviewmodel.h"
#include "../Services/filemanager.h"
#include "../Services/graphconnectioncheck.h"
#include "../Services/pmediansolver.h"
#include "../Model/node.h"
#include "../Model/edge.h"
#include "../Common/Builders/nodebuilder.h"
#include "../Common/Builders/edgebuilder.h"

namespace
{

NodeData modelToView(const Node& model)
{
    NodeData data;
    data._id         = model.id();
    data._name       = model.name();
    data._type       = static_cast<int32_t>(model.type());
    data._fixedCosts = model.fixedCosts();

    return data;
}

PMedianSolutionView solutionToSolutionView(const PMedianSolution& solution)
{
    PMedianSolutionView solutionView;

    solutionView.totalCost = solution.totalCost;

    for (auto& [customer, storage] : solution.assignments)
    {
        solutionView.assignments.emplace(modelToView(*customer), modelToView(*storage));
    }

    for (auto* storage : solution.selectedStorages)
    {
        solutionView.selectedStorages.emplace(modelToView(*storage));
    }

    return solutionView;
}

std::pair<std::map<int, Node>, std::map<int, Edge>>
dtosToModels(const std::map<int, NodeData>& nodes, const std::map<int, EdgeData>& edges)
{
    std::pair<std::map<int, Node>, std::map<int, Edge>> models;
    auto& [nodeModels, edgeModels] = models;

    for (auto& [id, node] : nodes)
    {
        nodeModels.emplace(id, NodeBuilder()
            .id(id)
            .name(node._name)
            .type(static_cast<NodeType>(node._type))
            .fixedCosts(node._fixedCosts)
            .build());
    }

    for (auto& [id, edge] : edges)
    {
        Node* from = &nodeModels.at(edge._from);
        Node* to   = &nodeModels.at(edge._to);

        auto [it, inserted] = edgeModels.emplace(id, EdgeBuilder()
            .id(id)
            .from(from)
            .to(to)
            .distance(edge._distance)
            .isOriented(edge._isOriented)
            .isValid(edge._isValid)
            .build());

        Edge* newEdge = &it->second;

        from->connectNode(newEdge, to);
        to->connectNode(newEdge, from);
    }

    return models;
}

} // namespace

GridViewModel::GridViewModel(std::shared_ptr<FileManager> fileManager, QObject* parent)
    : QObject(parent)
    , _pMedianConfig{}
    , _simAnnealConfig{}
    , _fileManager(std::move(fileManager))
{ }

void GridViewModel::saveItemsToFile()
{
    _fileManager->saveToFile(_nodes, _edges);
}

void GridViewModel::loadItemsFromFile()
{
    _nodes.clear();
    _edges.clear();

    auto [nodes, edges] = _fileManager->loadFromFile();

    if (nodes.empty() || edges.empty())
    {
        return;
    }

    _nodes = std::move(nodes);
    _edges = std::move(edges);

    emit onLoadFromFile(_nodes, _edges);
}

void GridViewModel::setNode(const NodeData& node)
{
    _nodes[node._id] = node;
}

void GridViewModel::setEdge(const EdgeData& edge)
{
    _edges[edge._id] = edge;
}

void GridViewModel::removeNode(int id)
{
    _nodes.erase(id);
}

void GridViewModel::removeEdge(int id)
{
    _edges.erase(id);
}

void GridViewModel::updateConfigs()
{
    emit onUpdateConfigs(_pMedianConfig, _simAnnealConfig);
}

void GridViewModel::clear()
{
    _nodes.clear();
    _edges.clear();
}

void GridViewModel::clearSolution()
{
    emit onClearSolution(_lastSol);
}

void GridViewModel::checkGraphConnection()
{
    if (_nodes.empty())
    {
        emit onCheckGraphConnection("There is no graph yet to check");
        return;
    }

    auto [nodeModels, edgeModels] = dtosToModels(_nodes, _edges);

    bool isGraphConnected = GraphConnectionCheck::checkGraphConnection(nodeModels);

    QString message = isGraphConnected ? "Graph is fully connected" : "There is more than 1 graph";

    emit onCheckGraphConnection(message);
}

void GridViewModel::solvePMedianProblem()
{
    if (_nodes.empty())
    {
        emit onCheckGraphConnection("There is no graph yet to solve");
        return;
    }

    auto [nodeModels, edgeModels] = dtosToModels(_nodes, _edges);

    if (!GraphConnectionCheck::checkGraphConnection(nodeModels))
    {
        emit onCheckGraphConnection("There needs to be only 1 graph to run solver");
        return;
    }

    PMedianSolution rawSol = PMedianSolver::solve(_pMedianConfig, _simAnnealConfig, nodeModels);

    _lastSol = {};
    _lastSol = solutionToSolutionView(rawSol);

    emit onShowOutput(_lastSol);
}

void GridViewModel::showLastSolutionOutput()
{
    emit onShowOutput(_lastSol);
}
