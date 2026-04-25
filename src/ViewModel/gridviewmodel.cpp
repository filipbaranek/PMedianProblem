#include "gridviewmodel.h"
#include "../Services/filemanager.h"

GridViewModel::GridViewModel(std::shared_ptr<FileManager> fileManager)
    : _fileManager(std::move(fileManager))
{ }

void GridViewModel::saveItemsToFile(const std::vector<NodeData>& nodes, const std::vector<EdgeData>& edges)
{
    _fileManager->saveToFile(nodes, edges);
}
