#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <set>
#include <QGraphicsEllipseItem>
#include "../../Common/NodeType.h"

class EdgeView;

class NodeView : public QGraphicsEllipseItem
{
public:
    NodeView(int id, float x, float y, const QString& name = {}, QGraphicsItem* parent = nullptr);

    int id() const
    {
        return _id;
    }

    const QString& name() const
    {
        return _name;
    }

    void setName(const QString& name);

    const NodeType& nodeType() const
    {
        return _type;
    }

    void setNodeType(const NodeType& type);

    void setPosX(const double x)
    {
        setPos(x, _posY);
    }

    const double& posX() const
    {
        return _posX;
    }

    void setPosY(const double y)
    {
        setPos(_posX, y);
    }

    const double& posY() const
    {
        return _posY;
    }

    void connectNode(NodeView* node)
    {
        _connectedNodes.insert(node);
    }

    void disconnectNode(NodeView* node)
    {
        _connectedNodes.erase(node);
    }

    bool isConnectedTo(NodeView* node) const
    {
        return _connectedNodes.contains(node);
    }

    const std::set<NodeView*>& connectedNodes() const
    {
        return _connectedNodes;
    }

    void addEdge(EdgeView* edge)
    {
        _edges.insert(edge);
    }

    void removeEdge(EdgeView* edge)
    {
        _edges.erase(edge);
    }

    const std::set<EdgeView*>& edges() const
    {
        return _edges;
    }

    constexpr const float radius() const
    {
        return RADIUS;
    }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    double              _posX;
    double              _posY;
    int                 _id;
    QString             _name;
    NodeType            _type;
    QGraphicsTextItem*  _label;
    std::set<EdgeView*> _edges;
    std::set<NodeView*> _connectedNodes;

    static constexpr float RADIUS = 30.0f;
};

#endif // NODEVIEW_H
