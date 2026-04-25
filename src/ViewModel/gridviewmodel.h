#ifndef GRIDVIEWMODEL_H
#define GRIDVIEWMODEL_H

#include <vector>
#include "../Common/dtos.h"

class FileManager;

class GridViewModel
{
public:
    GridViewModel(std::shared_ptr<FileManager> fileManager);

    void saveItemsToFile(const std::vector<NodeData>& nodes, const std::vector<EdgeData>& edges);

    // loadFromFile

private:
    std::shared_ptr<FileManager> _fileManager;
};

#endif // GRIDVIEWMODEL_H
