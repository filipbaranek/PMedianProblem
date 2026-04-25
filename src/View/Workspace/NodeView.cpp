#include "NodeView.h"
#include "EdgeView.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPen>

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
    : QGraphicsEllipseItem(-RADIUS, -RADIUS, RADIUS * 2, RADIUS * 2, parent),
      _id(id), _type(NodeType::CUSTOMER), _posX(x), _posY(y)
{
    setPos(x, y);

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

void NodeView::setName(const QString& name)
{
    _name = name;
    _label->setPlainText(_name);
    setupLabel(_label, boundingRect());
}

void NodeView::setNodeType(const NodeType& type)
{
    _type = type;
    if (type == NodeType::STORAGE)
    {
        setBrush(Qt::red);
    }
    else
    {
        setBrush(Qt::blue);
    }
}

QVariant NodeView::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionChange)
    {
        QPointF newPos = value.toPointF();
        _posX = newPos.x();
        _posY = newPos.y();

        for (auto& edge : _edges)
        {
            edge->updatePosition();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}