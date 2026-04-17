#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <set>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

class EdgeView;

class NodeView : public QGraphicsEllipseItem
{
public:
    NodeView(int id, float x, float y, float radius = 30.0f, QGraphicsItem* parent = nullptr);

    int id() const
    {
        return _id;
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

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    int                       _id;
    std::set<EdgeView*>       _edges;
    std::set<NodeView*> _connectedNodes;
};

#endif // NODEVIEW_H
