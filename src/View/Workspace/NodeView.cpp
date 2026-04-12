#include "NodeView.h"
#include "EdgeView.h"
#include <QGraphicsSceneMouseEvent>

NodeView::NodeView(int id, float x, float y, float radius, QGraphicsItem* parent)
    : QGraphicsEllipseItem(x - radius, y - radius, radius * 2, radius * 2, parent), _id(id)
{
    auto* text = new QGraphicsTextItem(QString::number(_id), this);
    QRectF rect = boundingRect();
    QRectF textRect = text->boundingRect();
    text->setDefaultTextColor(Qt::white);
    text->setPos(rect.center().x() - textRect.width() / 2, rect.center().y() - textRect.height() / 2);

    setBrush(Qt::blue);
    setPen(QPen(Qt::black));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setZValue(1);
}

QVariant NodeView::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionChange)
    {
        for (auto& edge : _edges)
        {
            edge->updatePosition();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}