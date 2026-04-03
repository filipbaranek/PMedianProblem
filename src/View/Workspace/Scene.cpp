#include "Scene.h"
#include "../../Common/Colors.h"

void Scene::handleSelection(const SelectionManager& selectionManager, const SceneOffsets& sceneOffsets)
{
    if (!selectionManager.drawRectangle())
    {
        return;
    }

    float x1 = (selectionManager.rectStart().x() - sceneOffsets._offsetX) / sceneOffsets._scale;
    float y1 = (sceneOffsets._height - selectionManager.rectStart().y() - sceneOffsets._offsetY) / sceneOffsets._scale;

    float x2 = (selectionManager.rectEnd().x() - sceneOffsets._offsetX) / sceneOffsets._scale;
    float y2 = (sceneOffsets._height - selectionManager.rectEnd().y() - sceneOffsets._offsetY) / sceneOffsets._scale;

    QRectF selectionRect(QPointF(x1, y1), QPointF(x2, y2));
    selectionRect = selectionRect.normalized();

    for (auto& node : _nodes) {
        float nx = node->posX();
        float ny = node->posY();
        float r  = node->radius();

        QRectF nodeRect(nx - r, ny - r, r*2, r*2);

        if (selectionRect.intersects(nodeRect))
        {
            node->setSelected(true);
            node->setColor(Colors::TRANSPARENT_YELLOW);
        }
        else
        {
            node->setSelected(false);
            node->setColor(Colors::LIGHT_BLUE);
        }
    }
}
