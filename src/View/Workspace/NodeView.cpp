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

NodeView::NodeView(QGraphicsItem* parent)
    : QObject(),
      QGraphicsEllipseItem(-RADIUS, -RADIUS, RADIUS * 2, RADIUS * 2, parent),
      _id{},
      _type(NodeType::CUSTOMER),
      _posX{},
      _posY{},
      _variableParameter{},
      _label(new QGraphicsTextItem(_name, this))
{
    setBrush(Qt::blue);
    setPen(QPen(Qt::black));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setZValue(1);
}

int NodeView::id() const
{
    return _id;
}

const QString& NodeView::name() const
{
    return _name;
}

const NodeType& NodeView::nodeType() const
{
    return _type;
}

const double& NodeView::posX() const
{
    return _posX;
}

const double& NodeView::posY() const
{
    return _posY;
}

const double& NodeView::variableParam() const
{
    return _variableParameter;
}

bool NodeView::isConnectedTo(NodeView* node) const
{
    return _connectedNodes.contains(node);
}

const std::set<EdgeView*>& NodeView::edges() const
{
    return _edges;
}

const std::set<NodeView*>& NodeView::connectedNodes() const
{
    return _connectedNodes;
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

void NodeView::setPosX(const double x)
{
    setPos(x, _posY);
}

void NodeView::setPosY(const double y)
{
    setPos(_posX, y);
}

void NodeView::setVariableParam(const double variableParam)
{
    _variableParameter = variableParam;
}

void NodeView::connectNode(NodeView *node)
{
    _connectedNodes.insert(node);
}

void NodeView::disconnectNode(NodeView* node)
{
    _connectedNodes.erase(node);
}

void NodeView::addEdge(EdgeView* edge)
{
    _edges.insert(edge);
}

void NodeView::removeEdge(EdgeView* edge)
{
    _edges.erase(edge);
}

NodeData NodeView::toDTO()
{
    NodeData data{};

    data._id                = _id;
    data._name              = _name;
    data._posX              = _posX;
    data._posY              = _posY;
    data._type              = static_cast<int32_t>(_type);
    data._variableParameter = _variableParameter;

    return data;
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

        emit onMove(NodeData{
            _id,
            _name,
            static_cast<int32_t>(_type),
            _posX,
            _posY,
            _variableParameter
        });
    }
    return QGraphicsItem::itemChange(change, value);
}