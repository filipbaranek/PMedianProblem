#include "NodeView.h"
#include "EdgeView.h"
#include <QGraphicsSceneMouseEvent>

namespace
{
    void setupLabel(QGraphicsTextItem* label, const QRectF& rect)
    {
        QRectF textRect = label->boundingRect();
        label->setDefaultTextColor(Qt::white);
        label->setPos(rect.center().x() - textRect.width() / 2, rect.center().y() - textRect.height() / 2);
    }
} // namespace

NodeView::NodeView(int id, float x, float y, const QString& name, QGraphicsItem* parent)
    : QGraphicsEllipseItem(x - RADIUS, y - RADIUS, RADIUS * 2, RADIUS * 2, parent), _id(id)
{
    _name = !name.isEmpty() ? name : QString::number(id);
    _label = new QGraphicsTextItem(_name, this);
    setupLabel(_label, boundingRect());

    setBrush(Qt::blue);
    setPen(QPen(Qt::black));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setZValue(1);
}

void NodeView::setName(const QString &name)
{
    _name = name;
    _label->setPlainText(_name);
    setupLabel(_label, boundingRect());
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