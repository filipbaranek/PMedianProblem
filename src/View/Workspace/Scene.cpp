#include "Scene.h"
#include "../../Common/Colors.h"

SelectionRectangle Scene::handleSelection(const SelectionRectangle& selectionRectangle, const SceneOffsets& sceneOffsets)
{
    if (!selectionRectangle._drawRectangle)
    {
        return{};
    }

    float x1 = (selectionRectangle._rectStart.x() - sceneOffsets._offsetX) / sceneOffsets._scale;
    float y1 = (sceneOffsets._height - selectionRectangle._rectStart.y() - sceneOffsets._offsetY) / sceneOffsets._scale;

    float x2 = (selectionRectangle._rectEnd.x() - sceneOffsets._offsetX) / sceneOffsets._scale;
    float y2 = (sceneOffsets._height - selectionRectangle._rectEnd.y() - sceneOffsets._offsetY) / sceneOffsets._scale;

    QRectF selectionRect(QPointF(x1, y1), QPointF(x2, y2));
    selectionRect = selectionRect.normalized();

    QRectF selectionBounds{};
    bool firstSelected{true};

    _selectedItems.clear();

    for (auto& node : _nodes) {
        float nx = node->posX();
        float ny = node->posY();
        float r  = node->radius();

        QRectF nodeRect(nx - r, ny - r, r*2, r*2);

        if (selectionRect.intersects(nodeRect))
        {
            node->setColor(Colors::TRANSPARENT_YELLOW);
            _selectedItems.push_back(node.get());

            float r = node->radius();
            QRectF nodeRect(node->posX() - r, node->posY() - r, 2*r, 2*r);

            if (firstSelected)
            {
                selectionBounds = nodeRect;
                firstSelected = false;
            }
            else
            {
                selectionBounds = selectionBounds.united(nodeRect);
            }
        }
        else
        {
            node->setColor(Colors::LIGHT_BLUE);
        }
    }

    return { QPointF(selectionBounds.topLeft()), QPointF(selectionBounds.bottomRight()), !_selectedItems.empty() };
}
