#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QPainter>

class GridScene : public QGraphicsScene
{
public:
    explicit GridScene(QObject* parent = nullptr) : QGraphicsScene(parent) { }

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override
    {
        const int gridSize = 100;
        QPen pen(Qt::gray);
        pen.setWidth(1);
        painter->setPen(pen);

        int startX = std::floor(rect.left() / gridSize) * gridSize;
        int endX   = std::ceil(rect.right() / gridSize) * gridSize;
        for (int x = startX; x <= endX; x += gridSize)
        {
            painter->drawLine(x, rect.top(), x, rect.bottom());
        }

        int startY = std::floor(rect.top() / gridSize) * gridSize;
        int endY   = std::ceil(rect.bottom() / gridSize) * gridSize;
        for (int y = startY; y <= endY; y += gridSize)
        {
            painter->drawLine(rect.left(), y, rect.right(), y);
        }

        QPen axisPen(Qt::black);
        axisPen.setWidth(4);
        painter->setPen(axisPen);

        if (rect.left() <= 0 && rect.right() >= 0)
        {
            painter->drawLine(0, rect.top(), 0, rect.bottom());
        }

        if (rect.top() <= 0 && rect.bottom() >= 0)
        {
            painter->drawLine(rect.left(), 0, rect.right(), 0);
        }
    }
};

#endif // GRIDSCENE_H
