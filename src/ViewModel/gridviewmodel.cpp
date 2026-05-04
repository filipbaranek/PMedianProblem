#include "gridviewmodel.h"
#include "../Services/filemanager.h"
#include "../Services/graphconnectioncheck.h"
#include "../Model/Node.h"
#include "../Model/Edge.h"
#include "../Common/Builders/nodebuilder.h"
#include "../Common/Builders/edgebuilder.h"

GridViewModel::GridViewModel(std::shared_ptr<FileManager> fileManager, QObject* parent)
    : QObject(parent),
      _fileManager(std::move(fileManager))
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

void GridViewModel::clear()
{
    _nodes.clear();
    _edges.clear();
}

void GridViewModel::checkGraphConnection()
{
    if (_nodes.empty())
    {
        emit onCheckGraphConnection("There is no graph yet to check");
        return;
    }

    std::map<int, Node> nodeModels;
    std::map<int, Edge> edgeModels;

    for (auto& [id, node] : _nodes)
    {
        nodeModels.emplace(id, NodeBuilder()
            .id(id)
            .type(static_cast<NodeType>(node._type))
            .variableParameter(node._variableParameter)
            .build());
    }

    for (auto& [id, edge] : _edges)
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

        from->addEdge(newEdge);
        to->addEdge(newEdge);

        from->connectNode(to);
        to->connectNode(from);
    }

    bool isGraphConnected = GraphConnectionCheck::checkGraphConnection(nodeModels);

    QString message = isGraphConnected ? "Graph is fully connected" : "There is more than 1 graph";

    emit onCheckGraphConnection(message);
}
