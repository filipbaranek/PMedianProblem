#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <QPoint>

class SelectionManager
{
public:
    inline const bool& drawRectangle() const { return _drawRectangle; }

    inline void setDrawRectangle(const bool& drawRectangle) { _drawRectangle = drawRectangle; }

    inline const QPointF& rectStart() const { return _rectStart; }

    inline void setRectStart(const QPoint& rectStart) { _rectStart = rectStart; }

    inline const QPointF& rectEnd() const { return _rectEnd; }

    inline void setRectEnd(const QPoint& rectEnd) { _rectEnd = rectEnd; }

private:
    QPointF _rectStart;
    QPointF _rectEnd;
    bool    _drawRectangle;
};

#endif // SELECTIONMANAGER_H
