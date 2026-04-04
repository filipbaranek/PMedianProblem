#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include "NodeView.h"

class EdgeView
{
public:
    EdgeView(NodeView* from, NodeView* to, float length)
        : _from(from), _to(to), _length(length)
    { }

    inline const NodeView* from() const { return _from; }

    inline const NodeView* to() const { return _to; }

    inline const float& length() const { return _length; }

    inline void setLength(const float& length) { _length = length; }

    void move(const QPointF& delta);

private:
    NodeView* _from;
    NodeView* _to;
    float     _length;
};

#endif // EDGEVIEW_H
