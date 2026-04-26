#include "gridviewmodel.h"
#include "../Services/filemanager.h"

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
