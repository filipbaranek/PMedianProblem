#ifndef NODE_H
#define NODE_H

#include <map>
#include <QString>
#include "../Common/nodetype.h"

class Edge;

class Node
{
public:
    Node()
        : _isMarked{}
    { }

    const int id() const
    {
        return _id;
    }

    const QString& name() const
    {
        return _name;
    }

    const bool isMarked() const
    {
        return _isMarked;
    }

    const NodeType& type() const
    {
        return _type;
    }

    const double fixedCosts() const
    {
        return _fixedCosts;
    }

    const std::map<Edge*, Node*> connectedNodes() const
    {
        return _connectedNodes;
    }

    void setIsMarked(bool isMarked)
    {
        _isMarked = isMarked;
    }

    void connectNode(Edge* edge, Node* node)
    {
        _connectedNodes[edge] = node;
    }

    friend class NodeBuilder;

private:
    QString                _name;
    int                    _id;
    bool                   _isMarked;
    NodeType               _type;
    double                 _fixedCosts;
    std::map<Edge*, Node*> _connectedNodes;
};

#endif // NODE_H
