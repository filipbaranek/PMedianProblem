#ifndef NODE_H
#define NODE_H

#include <set>
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

    const bool isMarked() const
    {
        return _isMarked;
    }

    const NodeType& type() const
    {
        return _type;
    }

    const double variableParameter() const
    {
        return _variableParameter;
    }

    const std::set<Edge*>& edges() const
    {
        return _edges;
    }

    const std::set<Node*> connectedNodes() const
    {
        return _connectedNodes;
    }

    void setIsMarked(bool isMarked)
    {
        _isMarked = isMarked;
    }

    void addEdge(Edge* edge)
    {
        _edges.insert(edge);
    }

    void connectNode(Node* node)
    {
        _connectedNodes.insert(node);
    }

    friend class NodeBuilder;

private:
    int             _id;
    bool            _isMarked;
    NodeType        _type;
    double          _variableParameter;
    std::set<Edge*> _edges;
    std::set<Node*> _connectedNodes;
};

#endif // NODE_H
