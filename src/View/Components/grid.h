#ifndef GRID_H
#define GRID_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMenu>
#include <QCursor>
#include "../Workspace/NodeView.h"

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
    QPoint          _lastMousePos;
    QGraphicsScene* _scene;
    NodeView*       _nodeFrom;
    bool            _createEdgeEvent;
    int             _nextNodeId;
};

#endif // GRID_H