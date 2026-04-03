#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QColor>
#include "IMovable.h"

class NodeView : public IMovable
{
public:
    NodeView(float posX, float posY, const QColor& color)
        : _selected{}, _posX(posX), _posY(posY), _color(color)
    { }

    inline const float& posX() const { return _posX; }

    inline void setPosX(const float& posX) { _posX = posX; }

    inline const float& posY() const { return _posY; }

    inline void setPosY(const float& posY) { _posY = posY; }

    inline const QColor& color() const { return _color; }

    inline void setColor(const QColor& color) { _color = color; }

    inline const bool& selected() const { return _selected; }

    inline void setSelected(const bool& selected) { _selected = selected; }

    inline constexpr const int radius() { return 30; }

    void move() override;

private:
    bool   _selected;
    float  _posX;
    float  _posY;
    QColor _color;
};

#endif // NODEVIEW_H
