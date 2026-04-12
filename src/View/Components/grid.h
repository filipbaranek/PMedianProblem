#ifndef GRID_H
#define GRID_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMenu>
#include <QCursor>
#include <QScrollBar>
#include "../Workspace/NodeView.h"
#include "../Workspace/CreateEdgeEvent.h"

class Grid : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Grid(QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;

    void contextMenuEvent(QContextMenuEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

private:
    NodeView* findNodeAt(const QPointF& pos);

    void addNodeAt(const QPointF& pos);

    void addEdgeBetween(NodeView* from, NodeView* to);

private:
    QPoint           _lastMousePos;
    CreateEdgeEvent* _edgeEvent;
    QGraphicsScene*  _scene;
    int              _nextNodeId;
};

#endif // GRID_H