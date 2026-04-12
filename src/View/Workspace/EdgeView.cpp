#include "EdgeView.h"
#include <QPainter>
#include <QPen>

EdgeView::EdgeView(NodeView* from, NodeView* to, QGraphicsItem* parent)
    : QGraphicsLineItem(parent), _from(from), _to(to)
{
    _from->addEdge(this);
    _to->addEdge(this);

    updatePosition();

    setPen(QPen(Qt::cyan, 2));
    setFlag(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);
}

void EdgeView::updatePosition()
{
    if (_from && _to)
    {
        QPointF p1 = _from->sceneBoundingRect().center();
        QPointF p2 = _to->sceneBoundingRect().center();

        setLine(QLineF(p1, p2));
    }
}