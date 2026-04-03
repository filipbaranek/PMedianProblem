#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "NodeView.h"
#include "SelectionManager.h"

class Scene
{
public:
    inline void addNode(std::unique_ptr<NodeView> node) { _nodes.emplace_back(std::move(node)); }

    inline const std::vector<std::unique_ptr<NodeView>>& nodes() const { return _nodes; }

    inline const std::vector<NodeView*>& selectedNodes() const { return _selectedNodes; }

    inline void clearSelectedNodes() { _selectedNodes.clear(); }

    void clearNodes();

    void handleSelection(const SelectionManager& selectionManager);


private:
    std::vector<std::unique_ptr<NodeView>> _nodes;
    std::vector<NodeView*>                 _selectedNodes;
};

#endif // SCENE_H
