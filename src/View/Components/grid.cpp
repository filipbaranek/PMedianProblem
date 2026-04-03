#include "grid.h"

void Grid::drawGrid(QPainter& painter, const QRect& window)
{
    painter.translate(_offsetX, height() - _offsetY);
    painter.scale(1, -1);
    painter.scale(_scale, _scale);

    float invScale = 1.0f / _scale;

    int startCol = (window.left() - _offsetX) * invScale / CELL_SIZE;
    int endCol   = (window.right() - _offsetX) * invScale / CELL_SIZE;
    int startRow = (window.top() - _offsetY) * invScale / CELL_SIZE;
    int endRow   = (window.bottom() - _offsetY) * invScale / CELL_SIZE;

    painter.setPen(Qt::gray);
    for (int i = startRow; i <= endRow; ++i)
    {
        painter.drawLine(startCol * CELL_SIZE, i * CELL_SIZE, (endCol + 1) * CELL_SIZE, i * CELL_SIZE);
    }

    for (int j = startCol; j <= endCol; ++j)
    {
        painter.drawLine(j * CELL_SIZE, startRow * CELL_SIZE, j * CELL_SIZE, (endRow + 1) * CELL_SIZE);
    }

    painter.setPen(Qt::red);
    painter.drawLine(0, startRow * CELL_SIZE, 0, (endRow + 1) * CELL_SIZE);
    painter.drawLine(startCol * CELL_SIZE, 0, (endCol + 1) * CELL_SIZE, 0);
}

void Grid::drawScene(QPainter& painter)
{
    //TODO
}

void Grid::drawSelectionRectangle(QPainter& painter)
{
    if (_selectionManager.drawRectangle())
    {
        painter.save();
        painter.resetTransform();
        painter.setPen(Qt::NoPen);
        painter.setBrush(TRANSPARENT_ORANGE);

        QRectF rect(_selectionManager.rectStart(), _selectionManager.rectEnd());
        rect = rect.normalized();

        painter.drawRect(rect);

        painter.restore();
    }
}

void Grid::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawGrid(painter, event->rect());
    drawScene(painter);
    drawSelectionRectangle(painter);
}

void Grid::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _selectionManager.setDrawRectangle(true);
        _selectionManager.setRectStart(event->pos());
        _selectionManager.setRectEnd(event->pos());
    }
    else if (event->button() == Qt::MiddleButton)
    {
        _lastMousePos = event->pos();
    }
}

void Grid::mouseReleaseEvent(QMouseEvent *event)
{
    _selectionManager.setDrawRectangle(false);

    update();
}

void Grid::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        _selectionManager.setRectEnd(event->pos());
    }
    else if (event->buttons() & Qt::MiddleButton)
    {
        QPointF delta = event->pos() - _lastMousePos;
        _offsetX += delta.x();
        _offsetY -= delta.y();
        _lastMousePos = event->pos();
    }

    update();
}

void Grid::wheelEvent(QWheelEvent* event)
{
    float zoomStep = 1.1f;

    if (event->angleDelta().y() > 0)
    {
        _scale *= zoomStep;
    }
    else
    {
        _scale /= zoomStep;
    }

    if (_scale < 0.1f)
    {
        _scale = 0.1f;
    }
    if (_scale > 10.0f)
    {
        _scale = 10.0f;
    }

    update();
}

