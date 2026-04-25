#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include <QGraphicsItem>

class NodeView;

class EdgeView : public QGraphicsLineItem
{
public:
    EdgeView(NodeView* from, NodeView* to, QGraphicsItem* parent = nullptr);

    void updatePosition();

    void setFrom(const QString& from);

    void setUseEuclideanDistance(const bool& useEuclideanDistance);

    void setIsValid(const bool& isValid);

    void setIsOriented(const bool& isOriented);

    void setDistance(const double distance);

    void setDistance();

    NodeView* from() const
    {
        return _from;
    }

    NodeView* to() const
    {
        return _to;
    }

    const bool& useEuclideanDistance() const
    {
        return _useEuclideanDistance;
    }

    const bool& isValid() const
    {
        return _isValid;
    }

    const bool& isOriented() const
    {
        return _isOriented;
    }

    const double& distance() const
    {
        return _distance;
    }

protected:
    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    NodeView* _from;
    NodeView* _to;
    bool      _useEuclideanDistance;
    bool      _isValid;
    bool      _isOriented;
    double    _distance;
};

#endif // EDGEVIEW_H