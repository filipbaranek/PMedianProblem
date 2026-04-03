#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QtGui>

class Grid : public QWidget
{
public:
    explicit Grid(QWidget* parrent = nullptr)
        : QWidget(parrent), _offsetX{}, _offsetY{}, _scale(1.0f)
    {
    }

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

private:
    int    _offsetX;
    int    _offsetY;
    float  _scale;
    QPoint _lastMousePos;

    static constexpr const int CELL_SIZE = 100;
};

#endif // GRID_H
