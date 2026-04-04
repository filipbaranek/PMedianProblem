#ifndef IMOVABLE_H
#define IMOVABLE_H

#include <QPointF>

class IMovable
{
public:
    virtual ~IMovable() = default;

    virtual void move(const QPointF& delta) = 0;
};

#endif // IMOVABLE_H
