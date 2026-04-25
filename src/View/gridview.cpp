#include "gridview.h"
#include "Workspace/EdgeView.h"
#include "Workspace/GridScene.h"
#include "Workspace/NodeView.h"
#include "Workspace/CreateEdgeEvent.h"
#include "editnodeview.h"
#include "editedgeview.h"
#include <functional>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMenu>
#include <QCursor>
#include <QScrollBar>

namespace
{
    template<typename T>
    void removeItems(QGraphicsScene* scene, std::function<void(T*)> removeCallback)
    {
        for (auto* item : scene->selectedItems())
        {
            auto* derived = dynamic_cast<T*>(item);
            if (!derived)
            {
                continue;
            }
            removeCallback(derived);
        }
    }

    template<typename T>
    T* findItemAt(QGraphicsScene* scene, const QPointF& pos)
    {
        T* foundItem{};
        for (auto& item : scene->items(pos))
        {
            foundItem = dynamic_cast<T*>(item);
            if (foundItem)
            {
                break;
            }
        }
        return foundItem;
    }
} // namespace

Grid::Grid(QWidget* parent)
    : QGraphicsView(parent), _edgeEvent(new CreateEdgeEvent()),
      _scene(new GridScene(this)), _nextNodeId{}, _useEuclideanDistance(true)
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
    if (_edgeEvent->isVisible())
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
    if (event->button() == Qt::RightButton)
    {
        auto* foundNode = findItemAt<NodeView>(_scene, mapToScene(event->pos()));
        if (foundNode != nullptr)
        {
            QMenu nodeMenu;

            nodeMenu.addAction("Edit node", [this, &foundNode]() {
                NodeEditDialog dialog(foundNode, this);
                dialog.exec();
            });

            nodeMenu.addAction("Remove node", [this, &foundNode]() {
                deleteNode(foundNode);
            });

            nodeMenu.exec(event->globalPosition().toPoint());

            event->accept();
            return;
        }
        auto* foundEdge = findItemAt<EdgeView>(_scene, mapToScene(event->pos()));
        if (foundEdge != nullptr)
        {
            QMenu edgeMenu;

            edgeMenu.addAction("Edit edge", [this, &foundEdge]() {
                EdgeEditDialog dialog(foundEdge, this);
                dialog.exec();
            });

            edgeMenu.addAction("Remove edge", [this, &foundEdge]() {
                deleteEdge(foundEdge);
            });

            edgeMenu.exec(event->globalPosition().toPoint());

            event->accept();
            return;
        }
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

void Grid::mouseReleaseEvent(QMouseEvent* event)
{
    if (_edgeEvent->isVisible() && event->button() == Qt::LeftButton)
    {
        NodeView* nodeFrom = findItemAt<NodeView>(_scene, _edgeEvent->posFrom());
        if (nodeFrom)
        {
            NodeView* nodeTo = findItemAt<NodeView>(_scene, mapToScene(event->pos()));
            if (nodeTo)
            {
                addEdgeBetween(nodeFrom, nodeTo);
            }
        }
        _edgeEvent->setVisible(false);
        setDragMode(QGraphicsView::RubberBandDrag);
    }

    unsetCursor();

    QGraphicsView::mouseReleaseEvent(event);
}

void Grid::mouseMoveEvent(QMouseEvent* event)
{
    if (_edgeEvent->isVisible() && event->buttons() & Qt::LeftButton)
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

void Grid::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete)
    {
        if (_scene->selectedItems().empty())
        {
            return;
        }
        removeItems<EdgeView>(_scene, [this](EdgeView* edge) {
            deleteEdge(edge);
        });
        removeItems<NodeView>(_scene, [this](NodeView* node) {
            deleteNode(node);
        });
        return;
    }

    QGraphicsView::keyPressEvent(event);
}

void Grid::open()
{
    //TODO
}

void Grid::saveAs()
{
    //TODO
}

void Grid::setEuclideanMode(bool toggled)
{
    _useEuclideanDistance = toggled;

    for (auto& item : _scene->items())
    {
        auto* edge = dynamic_cast<EdgeView*>(item);
        if (edge)
        {
            edge->setUseEuclideanDistance(toggled);
        }
    }
}

void Grid::deleteNode(NodeView* node)
{
    for (auto* edge : node->edges())
    {
        _scene->removeItem(edge);

        auto* connectedNode = edge->from() != node ? edge->from() : edge->to();
        connectedNode->disconnectNode(node);
        connectedNode->removeEdge(edge);

        delete edge;
    }
    _scene->removeItem(node);
    delete node;
}

void Grid::deleteEdge(EdgeView* edge)
{
    edge->to()->disconnectNode(edge->from());
    edge->from()->disconnectNode(edge->to());
    edge->to()->removeEdge(edge);
    edge->from()->removeEdge(edge);

    _scene->removeItem(edge);
    delete edge;
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

    EdgeView* edge = new EdgeView(from, to, _useEuclideanDistance);

    _scene->addItem(edge);

    from->connectNode(to);
    to->connectNode(from);
}

