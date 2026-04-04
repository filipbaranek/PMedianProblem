#include "grid.h"
#include "../../Common/Colors.h"

void Grid::drawGrid(QPainter& painter, const QRectF& window)
{
    painter.translate(_offsetX, height() - _offsetY);
    painter.scale(1, -1);
    painter.scale(_scale, _scale);

    float invScale = 1.0f / _scale;

    int startCol = (window.left() - _offsetX) * invScale / CELL_SIZE;
    int endCol   = (window.right() - _offsetX) * invScale / CELL_SIZE;
    int startRow = (window.top() - _offsetY) * invScale / CELL_SIZE;
    int endRow   = (window.bottom() - _offsetY) * invScale / CELL_SIZE;

    painter.setPen(Qt::gray);
    for (int i = startRow; i <= endRow; ++i)
    {
        painter.drawLine(startCol * CELL_SIZE, i * CELL_SIZE, (endCol + 1) * CELL_SIZE, i * CELL_SIZE);
    }

    for (int j = startCol; j <= endCol; ++j)
    {
        painter.drawLine(j * CELL_SIZE, startRow * CELL_SIZE, j * CELL_SIZE, (endRow + 1) * CELL_SIZE);
    }

    painter.setPen(Qt::red);
    painter.drawLine(0, startRow * CELL_SIZE, 0, (endRow + 1) * CELL_SIZE);
    painter.drawLine(startCol * CELL_SIZE, 0, (endCol + 1) * CELL_SIZE, 0);
}

void Grid::drawScene(QPainter& painter)
{
    painter.setPen(Qt::blue);

    for (auto& node : _scene.nodes())
    {
        painter.setBrush(node->color());
        painter.drawEllipse(QPointF(node->posX(), node->posY()), node->radius(), node->radius());

        if (_selectedItems._drawRectangle)
        {
            painter.save();
            QPen pen(Qt::gray);
            pen.setStyle(Qt::DashLine);
            pen.setWidthF(3.0f);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            QRectF rect{_selectedItems._rectStart, _selectedItems._rectEnd};
            painter.drawRect(rect);
            painter.restore();
        }
    }

    for (auto& edge : _scene.edges())
    {
        QPointF from{ edge->from()->posX(), edge->from()->posY() };
        QPointF to{ edge->to()->posX(), edge->to()->posY() };

        painter.setPen(Colors::LIGHT_BLUE);
        painter.drawLine(from, to);
    }

    if (_createEdgeEvent && _edgeEventActive)
    {
        QPoint currentMousePos = mapFromGlobal(QCursor::pos());
        QPointF from = QPointF(
            _lastMousePos.x() * _scale + _offsetX,
            height() - (_lastMousePos.y() * _scale + _offsetY)
        );

        painter.save();
        painter.resetTransform();
        painter.setPen(Colors::LIGHT_BLUE);
        painter.drawLine(from, currentMousePos);
        painter.restore();
    }
}

void Grid::drawSelectionRectangle(QPainter& painter)
{
    if (_selectionRectangle._drawRectangle && !_createEdgeEvent)
    {
        painter.save();
        painter.resetTransform();
        painter.setPen(Qt::NoPen);
        painter.setBrush(Colors::TRANSPARENT_ORANGE);

        QRectF rect(_selectionRectangle._rectStart, _selectionRectangle._rectEnd);
        rect = rect.normalized();

        painter.drawRect(rect);

        painter.restore();
    }
}

void Grid::showContextMenu(const QPoint& pos)
{
    static int nodeId{};    //TODO match last id

    QMenu menu(this);

    menu.addAction("Add node", this, [this, &pos]() {
        float posX = (pos.x() - _offsetX) / _scale;
        float posY = (height() - pos.y() - _offsetY) / _scale;

        _scene.addNode(std::make_unique<NodeView>(nodeId, posX, posY, Colors::LIGHT_BLUE));
    });

    menu.addAction("Add edge", this, [this](){
        _createEdgeEvent = true;
        _selectionRectangle._drawRectangle = false;
        _moveItemsEvent = false;
    });

    menu.addAction("Clear nodes", this, [this]() {
        _scene.clearNodes();
    });

    menu.addAction("Clear edges", this, [this](){
        _scene.clearEdges();
    });

    menu.addAction("Clear", this, [this](){
        _scene.clearScene();
    });

    menu.exec(mapToGlobal(pos));

    ++nodeId;

    update();
}

QPointF Grid::screenToScenePos(const QPointF& point) const
{
    float x = (point.x() - _offsetX) / _scale;
    float y = (height() - point.y() - _offsetY) / _scale;

    return QPointF(x, y);
}

void Grid::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawGrid(painter, event->rect());
    drawScene(painter);
    drawSelectionRectangle(painter);
}

void Grid::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (_createEdgeEvent)
        {
            _lastMousePos = screenToScenePos(event->pos());
            _edgeEventActive = true;
        }
        else if (_selectedItems._drawRectangle)
        {
            QPointF scenePos = screenToScenePos(event->pos());
            QRectF selectedItemsRect{_selectedItems._rectStart, _selectedItems._rectEnd};
            selectedItemsRect = selectedItemsRect.normalized();

            if (selectedItemsRect.contains(scenePos))
            {
                _moveItemsEvent = true;
                _lastMousePos   = event->pos();

                setCursor(Qt::ClosedHandCursor);
            }
            else
            {
                _selectedItems._drawRectangle      = false;
                _selectionRectangle._drawRectangle = true;
                _selectionRectangle._rectStart     = event->pos();
                _selectionRectangle._rectEnd       = event->pos();
            }
        }
        else
        {
            _selectionRectangle._drawRectangle = true;
            _selectionRectangle._rectStart     = event->pos();
            _selectionRectangle._rectEnd       = event->pos();
        }
    }
    else if (event->button() == Qt::MiddleButton)
    {
        _lastMousePos = event->pos();
    }
    else if (event->button() == Qt::RightButton)
    {
        showContextMenu(event->pos());
    }
}

void Grid::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (_createEdgeEvent)
        {
            float length;
            QPointF posFrom  = _lastMousePos;
            QPointF posTo    = screenToScenePos(event->pos());
            NodeView* from{};
            NodeView* to{};

            if (_euclideanDistance)
            {
                length = std::sqrt(std::pow(posFrom.x(), posTo.x()) + std::pow(posFrom.y(), posTo.y()));
                //TODO - CHECK
            }
            else
            {
                //TODO - pop up window
            }

            for (auto& node : _scene.nodes())
            {
                QRectF nodePos{
                    QPointF(node->posX() - node->radius(), node->posY() - node->radius()),
                    QPointF(node->posX() + node->radius(), node->posY() + node->radius())
                };

                if (nodePos.contains(posFrom))
                {
                    from = node.get();
                }
                if (nodePos.contains(posTo))
                {
                    to = node.get();
                }
            }

            if (from && to && from != to)
            {
                _scene.addEdge(std::make_unique<EdgeView>(from, to, length));
            }

            _createEdgeEvent = false;
            _edgeEventActive = false;
        }
        else if (!_moveItemsEvent)
        {
            const SceneOffsets sceneOffsets{
                _offsetX,
                _offsetY,
                _scale,
                static_cast<float>(height())
            };

            _selectedItems                     = _scene.handleSelection(_selectionRectangle, sceneOffsets);
            _selectionRectangle._drawRectangle = false;
        }
        else
        {
            _moveItemsEvent = false;
            unsetCursor();
        }
    }

    update();
}

void Grid::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (_moveItemsEvent)
        {
            const QPointF delta       = (event->pos() - _lastMousePos) / _scale;
            _selectedItems._rectStart += QPointF(delta.x(), -delta.y());
            _selectedItems._rectEnd   += QPointF(delta.x(), -delta.y());

            for (auto& item : _scene.selectedItems())
            {
                item->move(delta);
            }

            _lastMousePos = event->pos();
        }
        else
        {
            _selectionRectangle._rectEnd = event->pos();
        }
    }
    else if (event->buttons() & Qt::MiddleButton)
    {
        QPointF delta = event->pos() - _lastMousePos;
        _offsetX += delta.x();
        _offsetY -= delta.y();
        _lastMousePos = event->pos();
    }

    update();
}

void Grid::wheelEvent(QWheelEvent* event)
{
    float zoomStep = 1.1f;

    if (event->angleDelta().y() > 0)
    {
        _scale *= zoomStep;
    }
    else
    {
        _scale /= zoomStep;
    }

    _scale = std::clamp(_scale, 0.1f, 10.0f);

    update();
}

