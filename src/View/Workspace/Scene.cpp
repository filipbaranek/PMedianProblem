#include "Scene.h"


void Scene::clearNodes()
{
    clearSelectedNodes();
    _nodes.clear();
}

void Scene::handleSelection(const SelectionManager &selectionManager)
{
    //TODO
}
