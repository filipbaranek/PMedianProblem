#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include <QGraphicsItem>
#include "NodeView.h"

class EdgeView : public QGraphicsLineItem
{
public:
    EdgeView(NodeView* from, NodeView* to, QGraphicsItem* parent = nullptr);

    void updatePosition();

    const NodeView* from() const { return _from; }

    const NodeView* to() const { return _to; }

private:
    const NodeView* _from;
    const NodeView* _to;
};

#endif // EDGEVIEW_H