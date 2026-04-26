#ifndef GRIDVIEWMODEL_H
#define GRIDVIEWMODEL_H

#include <map>
#include <QObject>
#include "../Common/dtos.h"

class FileManager;

class GridViewModel : public QObject
{
    Q_OBJECT

public:
    GridViewModel(std::shared_ptr<FileManager> fileManager, QObject* parent = nullptr);

    void saveItemsToFile();

    void loadItemsFromFile();

public slots:
    void setNode(const NodeData& node);

    void setEdge(const EdgeData& edge);

    void removeNode(int id);

    void removeEdge(int id);

signals:
    void onLoadFromFile(const std::map<int, NodeData>& nodes, const std::map<int, EdgeData>& edges);

private:
    std::map<int, NodeData> _nodes;
    std::map<int, EdgeData> _edges;

    std::shared_ptr<FileManager> _fileManager;
};

#endif // GRIDVIEWMODEL_H
