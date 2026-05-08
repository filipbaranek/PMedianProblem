#ifndef NODEVIEWBUILDER_H
#define NODEVIEWBUILDER_H

#include <QString>
#include "../nodetype.h"
#include "../../View/Workspace/NodeView.h"

class NodeViewBuilder
{
public:
    NodeViewBuilder& id(int id)
    {
        _id = id;
        return *this;
    }

    NodeViewBuilder& name(const QString& name)
    {
        _name = name;
        return *this;
    }

    NodeViewBuilder& type(const NodeType& type)
    {
        _type = type;
        return *this;
    }

    NodeViewBuilder& posX(double x)
    {
        _posX = x;
        return *this;
    }

    NodeViewBuilder& posY(double y)
    {
        _posY = y;
        return *this;
    }

    NodeViewBuilder& fixedCosts(double fixedCosts)
    {
        _fixedCosts = fixedCosts;
        return *this;
    }

    [[nodiscard]] NodeView* build(QGraphicsItem* parent = {})
    {
        if (_id == -1)
        {
            throw std::logic_error("Member value id needs to be defined when creating Node");
        }

        if (_name.isEmpty())
        {
            _name = QString::number(_id);
        }

        auto* node = new NodeView(parent);

        node->_id = _id;
        node->setName(_name);
        node->setNodeType(_type);
        node->setPosX(_posX);
        node->setPosY(_posY);
        node->setFixedCosts(_fixedCosts);

        return node;
    }

private:
    int                 _id{-1};
    NodeType            _type{NodeType::CUSTOMER};
    QString             _name{};
    double              _posX{};
    double              _posY{};
    double              _fixedCosts{};
};

#endif // NODEVIEWBUILDER_H
