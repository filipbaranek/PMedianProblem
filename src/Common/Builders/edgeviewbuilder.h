#ifndef EDGEVIEWBUILDER_H
#define EDGEVIEWBUILDER_H

#include "../../View/Workspace/EdgeView.h"

class NodeView;
class QGraphicsItem;

class EdgeViewBuilder
{
public:
    EdgeViewBuilder& from(NodeView* node)
    {
        _from = node;
        return *this;
    }

    EdgeViewBuilder& to(NodeView* node)
    {
        _to = node;
        return *this;
    }

    EdgeViewBuilder& useEuclideanDistance(bool useEuclideanDist)
    {
        _useEuclideanDistance = useEuclideanDist;
        return *this;
    }

    EdgeViewBuilder& isValid(bool isValid)
    {
        _isValid = isValid;
        return *this;
    }

    EdgeViewBuilder& isOriented(bool isOriented)
    {
        _isOriented = isOriented;
        return *this;
    }

    EdgeViewBuilder& distance(double distance)
    {
        _distance = distance;
        return *this;
    }

    [[nodiscard]] EdgeView* build(QGraphicsItem* parent = {})
    {
        if (_from == nullptr || _to == nullptr)
        {
            throw std::logic_error("Members from and to needs to be defined when creating Edge");
        }

        auto* edge = new EdgeView(parent);

        edge->setFrom(_from);
        edge->setTo(_to);
        edge->setUseEuclideanDistance(_useEuclideanDistance);
        edge->setIsValid(_isValid);
        edge->setIsOriented(_isOriented);

        if (_useEuclideanDistance)
        {
            edge->setDistance();
        }
        else
        {
            edge->setDistance(_distance);
        }

        edge->updatePosition();

        return edge;
    }

private:
    NodeView* _from{};
    NodeView* _to{};
    bool      _useEuclideanDistance{true};
    bool      _isValid{true};
    bool      _isOriented{};
    double    _distance{-1};
};

#endif // EDGEVIEWBUILDER_H
