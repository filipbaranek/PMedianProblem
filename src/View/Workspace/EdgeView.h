#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include <QGraphicsItem>

class EdgeViewBuilder;
class NodeView;

class EdgeView : public QGraphicsLineItem
{
public:
    EdgeView(QGraphicsItem* parent = nullptr);

    void updatePosition();

    void setFrom(const QString& from);

    void setFrom(NodeView* from);

    void setTo(NodeView* to);

    void setUseEuclideanDistance(const bool& useEuclideanDistance);

    void setIsValid(const bool& isValid);

    void setIsOriented(const bool& isOriented);

    void setDistance(const double distance);

    void setDistance();

    NodeView* from() const;

    NodeView* to() const;

    const bool& useEuclideanDistance() const;

    const bool& isValid() const;

    const bool& isOriented() const;

    const double& distance() const;

    friend class EdgeViewBuilder;

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