#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <QRectF>
#include "NodeView.h"
#include "EdgeView.h"
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

    inline void addEdge(std::unique_ptr<EdgeView> edge) { _edges.emplace_back(std::move(edge)); }

    inline const std::vector<std::unique_ptr<NodeView>>& nodes() const { return _nodes; }

    inline const std::vector<std::unique_ptr<EdgeView>>& edges() const { return _edges; }

    inline const std::vector<NodeView*>& selectedItems() const { return _selectedItems; }

    inline void clearNodes() { _nodes.clear(); }

    inline void clearEdges() { _edges.clear(); }

    void clearScene();

    SelectionRectangle handleSelection(const SelectionRectangle& selectionRectangle, const SceneOffsets& sceneOffsets);


private:
    std::vector<std::unique_ptr<NodeView>> _nodes;
    std::vector<std::unique_ptr<EdgeView>> _edges;
    std::vector<NodeView*>                 _selectedItems;
};

#endif // SCENE_H
