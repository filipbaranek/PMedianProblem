#ifndef CREATEEDGEEVENT_H
#define CREATEEDGEEVENT_H

#include <QGraphicsLineItem>

class CreateEdgeEvent : public QGraphicsLineItem
{
public:
    CreateEdgeEvent(QGraphicsItem* parent = nullptr);

    void updatePos();

    void reset();

    void setPosFrom(const QPointF& from);

    void setPosTo(const QPointF& to);

    const QPointF& posFrom() const;

    const QPointF& posTo() const;

private:
    QPointF _posFrom;
    QPointF _posTo;
};

#endif // CREATEEDGEEVENT_H
