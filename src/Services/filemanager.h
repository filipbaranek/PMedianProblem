#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "../Common/dtos.h"

class FileManager
{
public:
    void saveToFile(const std::vector<NodeData>& nodes, const std::vector<EdgeData>& edges);

    // void loadFromFile();
};

#endif // FILEMANAGER_H
