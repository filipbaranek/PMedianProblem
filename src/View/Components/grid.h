#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QtGui>
#include "../Workspace/SelectionManager.h"

class Grid : public QWidget
{
public:
    explicit Grid(QWidget* parrent = nullptr)
        : QWidget(parrent), _offsetX{}, _offsetY{}, _scale(1.0f)
    { }

private:
    void drawGrid(QPainter& painter, const QRect& window);

    void drawScene(QPainter& painter);

    void drawSelectionRectangle(QPainter& painter);

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

private:
    SelectionManager _selectionManager;
    QPoint           _lastMousePos;
    float            _offsetX;
    float            _offsetY;
    float            _scale;

    static constexpr const int CELL_SIZE = 100;

    static constexpr const QColor TRANSPARENT_ORANGE{255, 200, 0, 128};
};

#endif // GRID_H
