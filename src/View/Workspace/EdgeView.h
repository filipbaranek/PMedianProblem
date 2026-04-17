#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include <QGraphicsItem>
#include "NodeView.h"

class EdgeView : public QGraphicsLineItem
{
public:
    EdgeView(NodeView* from, NodeView* to, QGraphicsItem* parent = nullptr);

    void updatePosition();

    NodeView* from() const
    {
        return _from;
    }

    NodeView* to() const
    {
        return _to;
    }

private:
    NodeView* _from;
    NodeView* _to;
};

#endif // EDGEVIEW_H