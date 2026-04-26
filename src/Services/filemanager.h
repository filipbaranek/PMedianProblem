#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <map>
#include <utility>
#include "../Common/dtos.h"

class FileManager
{
public:
    void saveToFile(const std::map<int, NodeData>& nodes, const std::map<int, EdgeData>& edges);

    std::pair<std::map<int, NodeData>, std::map<int, EdgeData>> loadFromFile();
};

#endif // FILEMANAGER_H
