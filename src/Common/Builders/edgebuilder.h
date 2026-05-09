#ifndef EDGEBUILDER_H
#define EDGEBUILDER_H

#include <stdexcept>
#include "../../Model/edge.h"

class EdgeBuilder
{
public:
    EdgeBuilder()
        : _edge{}
    {
        _edge._id = -1;
    }

    EdgeBuilder& id(int id)
    {
        _edge._id = id;
        return *this;
    }

    EdgeBuilder& from(Node* from)
    {
        _edge._from = from;
        return *this;
    }

    EdgeBuilder& to(Node* to)
    {
        _edge._to = to;
        return *this;
    }

    EdgeBuilder& distance(double distance)
    {
        _edge._distance = distance;
        return *this;
    }

    EdgeBuilder& isValid(bool isValid)
    {
        _edge._isValid = isValid;
        return *this;
    }

    EdgeBuilder& isOriented(bool isOriented)
    {
        _edge._isOriented = isOriented;
        return *this;
    }

    Edge&& build()
    {
        if (_edge._id == -1)
        {
            throw std::logic_error("Error while constructing Edge: ID parameter is mandatory");
        }
        if (_edge._from == nullptr)
        {
            throw std::logic_error("Error while constructing Edge: From parameter is mandatory");
        }
        if (_edge._to == nullptr)
        {
            throw std::logic_error("Error while constructing Edge: To parameter is mandatory");
        }

        return std::move(_edge);
    }

private:
    Edge _edge;
};

#endif // EDGEBUILDER_H
