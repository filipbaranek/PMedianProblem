#include "grid.h"
#include "../Workspace/EdgeView.h"
#include "../Workspace/GridScene.h"
#include <QScrollBar>

Grid::Grid(QWidget* parent)
    : QGraphicsView(parent), _scene(new GridScene(this)),
      _nodeFrom{}, _createEdgeEvent{}, _nextNodeId{}
{
    setScene(_scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    horizontalScrollBar()->hide();
    verticalScrollBar()->hide();

    _scene->setSceneRect(-5000, -5000, 10000, 10000);
}

void Grid::wheelEvent(QWheelEvent* event)
{
    const double scaleFactor = 1.1;
    if (event->angleDelta().y() > 0)
    {
        scale(scaleFactor, scaleFactor);
    }
    else
    {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void Grid::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu;

    menu.addAction("Add Node", [this, &event]() {
        addNodeAt(mapToScene(event->pos()));
    });

    menu.addAction("Add Edge", [this]() {
        _createEdgeEvent = true;
        setCursor(Qt::CrossCursor);
        setDragMode(QGraphicsView::NoDrag);
    });

    menu.addAction("Clear", [this]() {
        _scene->clear();
        _nextNodeId = 0;
    });

    menu.exec(event->globalPos());
}

void Grid::mousePressEvent(QMouseEvent* event)
{
    if (_createEdgeEvent)
    {
        if (event->button() == Qt::LeftButton && _createEdgeEvent)
        {
            _nodeFrom = findNodeAt(mapToScene(event->pos()));
        }
        return;
    }
    if (event->button() == Qt::MiddleButton)
    {
        _lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

void Grid::mouseReleaseEvent(QMouseEvent* event)
{
    if (_createEdgeEvent)
    {
        if (event->button() == Qt::LeftButton && _nodeFrom)
        {
            NodeView* nodeTo = findNodeAt(mapToScene(event->pos()));
            if (nodeTo)
            {
                addEdgeBetween(_nodeFrom, nodeTo);
            }
        }
    }

    _createEdgeEvent = false;
    unsetCursor();
    setDragMode(QGraphicsView::RubberBandDrag);

    QGraphicsView::mouseReleaseEvent(event);
}

void Grid::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::MiddleButton)
    {
        if (!_lastMousePos.isNull())
        {
            QPoint delta = event->pos() - _lastMousePos;
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        }
        _lastMousePos = event->pos();
        return;
    }

    QGraphicsView::mouseMoveEvent(event);
}

NodeView* Grid::findNodeAt(const QPointF &pos)
{
    NodeView* foundNode{};
    for (auto& node : _scene->items(pos))
    {
        foundNode = dynamic_cast<NodeView*>(node);
        if (foundNode)
        {
            break;
        }
    }
    return foundNode;
}

void Grid::addNodeAt(const QPointF& pos)
{
    NodeView* node = new NodeView(++_nextNodeId, pos.x(), pos.y());
    _scene->addItem(node);
}

void Grid::addEdgeBetween(NodeView* from, NodeView* to)
{
    if (!from || !to || from == to || from->isConnectedTo(to))
    {
        return;
    }

    EdgeView* edge = new EdgeView(from, to);

    _scene->addItem(edge);

    from->connectNode(to);
    to->connectNode(from);
}

