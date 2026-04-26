#include "filemanager.h"
#include <QFileDialog>

namespace
{
    static constexpr const char* NODES_FILE_NAME = "nodes.txt";
    static constexpr const char* EDGES_FILE_NAME = "edges.txt";
} // namespace

void FileManager::saveToFile(const std::map<int, NodeData>& nodes, const std::map<int, EdgeData>& edges)
{
    QString dirPath = QFileDialog::getExistingDirectory(
        nullptr,
        "Select Folder",
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (dirPath.isEmpty())
    {
        return;
    }

    QDir dir(dirPath);
    QString nodesPath = dir.filePath(NODES_FILE_NAME);
    QString edgesPath = dir.filePath(EDGES_FILE_NAME);

    // Nodes
    QFile nodesFile(nodesPath);
    if (!nodesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream outNode(&nodesFile);
    outNode << "# id name type posX posY variableParameter\n";

    for (const auto& [id, node] : nodes)
    {
        outNode << node._id << ";"
                << node._name << ";"
                << node._type << ";"
                << node._posX << ";"
                << node._posY << ";"
                << node._variableParameter << "\n";
    }

    nodesFile.close();

    // Edges
    QFile edgesFile(edgesPath);
    if (!edgesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream outEdge(&edgesFile);
    outEdge << "# id from to useEuclideanDistance isValid isOriented distance\n";

    for (const auto& [id, edge] : edges)
    {
        outEdge << edge._id << ";"
                << edge._from << ";"
                << edge._to << ";"
                << (edge._useEuclideanDistance ? 1 : 0) << ";"
                << (edge._isValid ? 1 : 0) << ";"
                << (edge._isOriented ? 1 : 0) << ";"
                << edge._distance << "\n";
    }

    edgesFile.close();
}

std::pair<std::map<int, NodeData>, std::map<int, EdgeData>> FileManager::loadFromFile()
{
    std::map<int, NodeData> nodes;
    std::map<int, EdgeData> edges;

    QString dirPath = QFileDialog::getExistingDirectory(
        nullptr,
        "Select Folder",
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (dirPath.isEmpty())
    {
        return { nodes, edges };
    }

    QDir dir(dirPath);

    QString nodesPath = dir.filePath(NODES_FILE_NAME);
    QString edgesPath = dir.filePath(EDGES_FILE_NAME);

    // Nodes
    QFile nodesFile(nodesPath);
    if (nodesFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&nodesFile);

        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();

            if (line.isEmpty() || line.startsWith("#"))
            {
                continue;
            }

            QStringList parts = line.split(';');
            if (parts.size() < 6)
            {
                continue;
            }

            NodeData node;

            node._id = parts[0].toInt();
            node._name = parts[1];
            node._type = parts[2].toInt();
            node._posX = parts[3].toDouble();
            node._posY = parts[4].toDouble();
            node._variableParameter = parts[5].toDouble();

            nodes[node._id] = node;
        }

        nodesFile.close();
    }

    // Edges
    QFile edgesFile(edgesPath);
    if (edgesFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&edgesFile);

        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();
            if (line.isEmpty() || line.startsWith("#"))
            {
                continue;
            }

            QStringList parts = line.split(';');
            if (parts.size() < 7)
            {
                continue;
            }

            EdgeData edge;

            edge._id                   = parts[0].toInt();
            edge._from                 = parts[1].toInt();
            edge._to                   = parts[2].toInt();
            edge._useEuclideanDistance = parts[3].toInt();
            edge._isValid              = parts[4].toInt();
            edge._isOriented           = parts[5].toInt();
            edge._distance             = parts[6].toDouble();

            edges[edge._id] = edge;
        }

        edgesFile.close();
    }

    return { nodes, edges };
}
