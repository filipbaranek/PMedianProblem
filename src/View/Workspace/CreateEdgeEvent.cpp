#include "CreateEdgeEvent.h"
#include <QPen>

CreateEdgeEvent::CreateEdgeEvent(QGraphicsItem* parent)
    : QGraphicsLineItem(parent)
{
    setVisible(false);
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

void CreateEdgeEvent::setPosFrom(const QPointF& from)
{
    _posFrom = from;
}

void CreateEdgeEvent::setPosTo(const QPointF& to)
{
    _posTo = to;
}

const QPointF& CreateEdgeEvent::posFrom() const
{
    return _posFrom;
}

const QPointF& CreateEdgeEvent::posTo() const
{
    return _posTo;
}
