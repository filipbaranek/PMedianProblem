#include "grid.h"

void Grid::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect = event->rect();

    int startCol = rect.left() / CELL_SIZE;
    int endCol   = rect.right() / CELL_SIZE;
    int startRow = rect.top() / CELL_SIZE;
    int endRow   = rect.bottom() / CELL_SIZE;

    painter.setPen(Qt::gray);

    for (int i = startRow; i <= endRow; ++i)
    {
        painter.drawLine(startCol * CELL_SIZE, i * CELL_SIZE, (endCol + 1) * CELL_SIZE, i * CELL_SIZE);
    }

    for (int j = startCol; j <= endCol; ++j)
    {
        painter.drawLine(j * CELL_SIZE, startRow * CELL_SIZE, j * CELL_SIZE, (endRow + 1) * CELL_SIZE);
    }
}
