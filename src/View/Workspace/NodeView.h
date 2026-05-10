#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <map>
#include <QGraphicsEllipseItem>
#include "../../Common/nodetype.h"
#include "../../Common/dtos.h"
#include "../../Common/idata.h"

class NodeViewBuilder;
class EdgeView;

class NodeView : public QObject, public QGraphicsEllipseItem, public IData<NodeData>
{
    Q_OBJECT

public:
    NodeView(QGraphicsItem* parent = nullptr);

    int id() const;

    const QString& name() const;

    const NodeType& nodeType() const;

    const double posX() const;

    const double posY() const;

    const double fixedCosts() const;

    bool isConnectedTo(NodeView* node) const;

    const std::map<NodeView*, EdgeView*>& connectedNodes() const;

    void setName(const QString& name);

    void setNodeType(const NodeType& type);

    void setPosX(const double x);

    void setPosY(const double y);

    void setFixedCosts(const double fixedCosts);

    void connectNode(NodeView* node, EdgeView* edge);

    void disconnectNode(NodeView* node);

    NodeData toDTO() override;

    constexpr const float radius() const
    {
        return RADIUS;
    }

    friend class NodeViewBuilder;

signals:
    void onMove(const NodeData& node);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    int                            _id;
    QString                        _name;
    NodeType                       _type;
    double                         _posX;
    double                         _posY;
    double                         _fixedCosts;
    QGraphicsTextItem*             _label;
    std::map<NodeView*, EdgeView*> _connectedNodes;

    static constexpr float RADIUS = 30.0f;
};

#endif // NODEVIEW_H
