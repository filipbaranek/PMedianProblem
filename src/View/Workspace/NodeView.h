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

    int id() const { return _id; }

    void connectNode(NodeView* node) { _connectedNodes.insert(node); }

    bool isConnectedTo(NodeView* node) const { return _connectedNodes.contains(node); }

    void addEdge(EdgeView* edge) { _edges.insert(edge); }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    int                 _id;
    std::set<NodeView*> _connectedNodes;
    std::set<EdgeView*> _edges;
};

#endif // NODEVIEW_H
