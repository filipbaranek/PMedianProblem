#include "grid.h"
#include "../Workspace/EdgeView.h"
#include "../Workspace/GridScene.h"

Grid::Grid(QWidget* parent)
    : QGraphicsView(parent), _edgeEvent(new CreateEdgeEvent()),
      _scene(new GridScene(this)), _nextNodeId{}
{
    setScene(_scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    horizontalScrollBar()->hide();
    verticalScrollBar()->hide();

    _scene->setSceneRect(-5000, -5000, 10000, 10000);
    _scene->addItem(_edgeEvent);
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
        _edgeEvent->reset();
        _edgeEvent->setActive(true);
        _edgeEvent->setVisible(true);
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
    if (_edgeEvent->isActive())
    {
        if (event->button() == Qt::LeftButton)
        {
            _edgeEvent->setPosFrom(mapToScene(event->pos()));
            _edgeEvent->setPosTo(mapToScene(event->pos()));
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
    if (_edgeEvent->isActive() && event->button() == Qt::LeftButton)
    {
        NodeView* nodeFrom = findNodeAt(_edgeEvent->posFrom());
        if (nodeFrom)
        {
            NodeView* nodeTo = findNodeAt(mapToScene(event->pos()));
            if (nodeTo)
            {
                addEdgeBetween(nodeFrom, nodeTo);
            }
        }
        _edgeEvent->setActive(false);
        _edgeEvent->setVisible(false);
    }

    unsetCursor();
    setDragMode(QGraphicsView::RubberBandDrag);

    QGraphicsView::mouseReleaseEvent(event);
}

void Grid::mouseMoveEvent(QMouseEvent* event)
{
    if (_edgeEvent->isActive() && event->buttons() & Qt::LeftButton)
    {
        _edgeEvent->setPosTo(mapToScene(event->pos()));
        _edgeEvent->updatePos();
        return;
    }
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

