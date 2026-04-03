#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <QRectF>
#include "NodeView.h"
#include "SelectionManager.h"

struct SceneOffsets
{
    float _offsetX;
    float _offsetY;
    float _scale;
    float _height;
};

class Scene
{
public:
    inline void addNode(std::unique_ptr<NodeView> node) { _nodes.emplace_back(std::move(node)); }

    inline const std::vector<std::unique_ptr<NodeView>>& nodes() const { return _nodes; }

    inline void clearNodes() { _nodes.clear(); }

    void handleSelection(const SelectionManager& selectionManager, const SceneOffsets& sceneOffsets);


private:
    std::vector<std::unique_ptr<NodeView>> _nodes;
};

#endif // SCENE_H
