#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QtGui>

class Grid : public QWidget
{
public:
    explicit Grid(QWidget* parrent = nullptr) : QWidget(parrent) {};

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    static constexpr const int CELL_SIZE = 100;
};

#endif // GRID_H
