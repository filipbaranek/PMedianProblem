#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <QPoint>

struct SelectionRectangle
{
    QPointF _rectStart;
    QPointF _rectEnd;
    bool    _drawRectangle;
};

#endif // SELECTIONMANAGER_H
