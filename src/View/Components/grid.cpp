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
    painter.setPen(Qt::NoPen);

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
}

void Grid::drawSelectionRectangle(QPainter& painter)
{
    if (_selectionRectangle._drawRectangle)
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
    QMenu menu(this);

    menu.addAction("Add node", this, [this, &pos]() {
        float posX = (pos.x() - _offsetX) / _scale;
        float posY = (height() - pos.y() - _offsetY) / _scale;

        _scene.addNode(std::make_unique<NodeView>(posX, posY, Colors::LIGHT_BLUE));
    });
    menu.addAction("Add edge", this, [](){  });

    menu.addAction("Clear nodes", this, [this]() {
        _scene.clearNodes();
    });

    menu.addAction("Clear edges", this, [](){  });

    menu.addAction("Clear", this, [](){  });

    menu.exec(mapToGlobal(pos));

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
        if (_selectedItems._drawRectangle)
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
        if (!_moveItemsEvent)
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

