#ifndef IMOVABLE_H
#define IMOVABLE_H

class IMovable
{
public:
    virtual ~IMovable() = default;

    virtual void move() = 0;
};

#endif // IMOVABLE_H
