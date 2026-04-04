#include "NodeView.h"


void NodeView::move(const QPointF& delta)
{
    _posX += delta.x();
    _posY -= delta.y();
}
