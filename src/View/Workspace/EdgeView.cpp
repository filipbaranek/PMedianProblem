#include "EdgeView.h"
#include "NodeView.h"
#include <cmath>
#include <QPainter>
#include <QPen>

namespace
{
    constexpr double square(double x)
    {
        return x * x;
    }

    constexpr double euclideanDistance(const QPointF& from, const QPointF& to)
    {
        return std::sqrt(square(from.x() - to.x()) + square(from.y() - to.y()));
    }
} // namespace


EdgeView::EdgeView(QGraphicsItem* parent)
    : QGraphicsLineItem(parent),
      _from{},
      _to{},
      _useEuclideanDistance(true),
      _isValid(true),
      _isOriented{}
{
    setZValue(-1);
}

void EdgeView::updatePosition()
{
    if (_from && _to)
    {
        QPointF p1 = _from->sceneBoundingRect().center();
        QPointF p2 = _to->sceneBoundingRect().center();

        setLine(QLineF(p1, p2));

        if (_useEuclideanDistance)
        {
            setDistance();
        }
    }
}

void EdgeView::setFrom(const QString& from)
{
    if (from == _from->name())
    {
        return;
    }
    NodeView* temp = _from;
    _from = _to;
    _to = temp;

    updatePosition();
    update(boundingRect());
}

void EdgeView::setFrom(NodeView* from)
{
    _from = from;
    _from->addEdge(this);
}

void EdgeView::setTo(NodeView* to)
{
    _to = to;
    _to->addEdge(this);
}

void EdgeView::setUseEuclideanDistance(const bool& useEuclideanDistance)
{
    _useEuclideanDistance = useEuclideanDistance;
}

void EdgeView::setIsValid(const bool& isValid)
{
    _isValid = isValid;
}

void EdgeView::setIsOriented(const bool& isOriented)
{
    _isOriented = isOriented;
    update(boundingRect());
}

void EdgeView::setDistance(const double distance)
{
    _distance = distance;
}

void EdgeView::setDistance()
{
    _distance = euclideanDistance(_from->pos(), _to->pos());
}

NodeView* EdgeView::from() const
{
    return _from;
}

NodeView* EdgeView::to() const
{
    return _to;
}

const bool& EdgeView::useEuclideanDistance() const
{
    return _useEuclideanDistance;
}

const bool& EdgeView::isValid() const
{
    return _isValid;
}

const bool& EdgeView::isOriented() const
{
    return _isOriented;
}

const double& EdgeView::distance() const
{
    return _distance;
}

EdgeData EdgeView::toDTO()
{
    EdgeData data{};

    data._from                 = _from->id();
    data._to                   = _to->id();
    data._isValid              = _isValid;
    data._isOriented           = _isOriented;
    data._useEuclideanDistance = _useEuclideanDistance;
    data._distance             = _distance;

    return data;
}

QRectF EdgeView::boundingRect() const
{
    QPointF p1 = _from->sceneBoundingRect().center();
    QPointF p2 = _to->sceneBoundingRect().center();

    QRectF rect(p1, p2);

    static constexpr qreal extra = 50.0;
    return rect.normalized().adjusted(-extra, -extra, extra, extra);
}

void EdgeView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsLineItem::paint(painter, option, widget);

    QPen pen;
    if (_isValid)
    {
        pen = QPen(Qt::cyan, 2);
    }
    else
    {
        pen = QPen(Qt::red, 2);
    }
    painter->setPen(pen);
    painter->drawLine(line());

    if (_isOriented)
    {
        const float nodeRadius = _to->radius();
        const double angle = std::atan2(line().dy(), line().dx());

        QPointF offset(std::cos(angle) * nodeRadius, std::sin(angle) * nodeRadius);
        QPointF arrowTip = line().p2() - offset;
        QPointF arrowP1 = arrowTip - QPointF(std::cos(angle + M_PI / 6) * 10, std::sin(angle + M_PI / 6) * 10);
        QPointF arrowP2 = arrowTip - QPointF(std::cos(angle - M_PI / 6) * 10, std::sin(angle - M_PI / 6) * 10);

        painter->drawLine(arrowTip, arrowP1);
        painter->drawLine(arrowTip, arrowP2);
    }
}