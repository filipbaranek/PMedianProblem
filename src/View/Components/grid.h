#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QtGui>
#include <QMenu>
#include "../Workspace/SelectionManager.h"
#include "../Workspace/Scene.h"

class Grid : public QWidget
{
public:
    explicit Grid(QWidget* parrent = nullptr)
        : QWidget(parrent), _offsetX{}, _offsetY{}, _scale(1.0f), _moveItemsEvent{}
    { }

private:
    void drawGrid(QPainter& painter, const QRectF& window);

    void drawScene(QPainter& painter);

    void drawSelectionRectangle(QPainter& painter);

    void showContextMenu(const QPoint& pos);

    QPointF screenToScenePos(const QPointF& point) const;

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

private:
    SelectionRectangle _selectionRectangle;
    SelectionRectangle _selectedItems;
    Scene              _scene;
    QPoint             _lastMousePos;
    float              _offsetX;
    float              _offsetY;
    float              _scale;
    bool               _moveItemsEvent;

    static constexpr const int CELL_SIZE = 100;
};

#endif // GRID_H
