#ifndef NODEBUILDER_H
#define NODEBUILDER_H

#include <stdexcept>
#include "../../Model/Node.h"

class NodeBuilder
{
public:
    NodeBuilder()
        : _node{}
    {
        _node._id = -1;
    }

    NodeBuilder& id(int id)
    {
        _node._id = id;
        return *this;
    }

    NodeBuilder& type(const NodeType& type)
    {
        _node._type = type;
        return *this;
    }

    NodeBuilder& variableParameter(double variableParameter)
    {
        _node._variableParameter = variableParameter;
        return *this;
    }

    Node&& build()
    {
        if (_node._id == -1)
        {
            throw std::logic_error("Error while constructing Node: ID parameter is mandatory");
        }

        return std::move(_node);
    }

private:
    Node _node;
};

#endif // NODEBUILDER_H
