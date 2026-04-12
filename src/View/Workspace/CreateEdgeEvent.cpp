#include "CreateEdgeEvent.h"

CreateEdgeEvent::CreateEdgeEvent(QGraphicsItem* parent)
    : QGraphicsLineItem(parent)
{
    setPen(QPen(Qt::cyan, 2));
    setZValue(-1);
}

void CreateEdgeEvent::updatePos()
{
    setLine(QLineF(_posFrom, _posTo));
}

void CreateEdgeEvent::reset()
{
    _posFrom = QPointF();
    _posTo   = QPointF();

    setLine(QLineF());
    update();
}
