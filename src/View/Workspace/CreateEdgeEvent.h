#ifndef CREATEEDGEEVENT_H
#define CREATEEDGEEVENT_H

#include <QGraphicsLineItem>

class CreateEdgeEvent : public QGraphicsLineItem
{
public:
    CreateEdgeEvent(QGraphicsItem* parent = nullptr);

    void updatePos();

    void reset();

    void setPosFrom(const QPointF& from) { _posFrom = from; }

    const QPointF& posFrom() const { return _posFrom; }

    void setPosTo(const QPointF& to) { _posTo = to; }

    const QPointF& posTo() const { return _posTo; }

private:
    QPointF _posFrom;
    QPointF _posTo;
};

#endif // CREATEEDGEEVENT_H
