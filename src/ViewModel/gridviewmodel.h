#ifndef GRIDVIEWMODEL_H
#define GRIDVIEWMODEL_H

#include <map>
#include <QObject>
#include "../Common/dtos.h"
#include "../Services/pmedianevaluator.h"
#include "../Services/simulatedannealing.h"

class Edge;
class FileManager;

class GridViewModel : public QObject
{
    Q_OBJECT

public:
    GridViewModel(std::shared_ptr<FileManager> fileManager, QObject* parent = nullptr);

public slots:
    void saveItemsToFile();

    void loadItemsFromFile();

    void checkGraphConnection();

    void solvePMedianProblem();

    void showLastSolutionOutput();

    void setNode(const NodeData& node);

    void setEdge(const EdgeData& edge);

    void removeNode(int id);

    void removeEdge(int id);

    void updateConfigs();

    void clear();

signals:
    void onCheckGraphConnection(const QString& message);

    void onUpdateConfigs(PMedianConfig& pMedianConfig, SimulatedAnnealingConfig& simAnnealCOnfig);

    void onShowOutput(const PMedianSolutionView& solution);

    void onLoadFromFile(const std::map<int, NodeData>& nodes, const std::map<int, EdgeData>& edges);

private:
    std::map<int, NodeData> _nodes;
    std::map<int, EdgeData> _edges;

    PMedianSolution _lastSol;

    PMedianConfig            _pMedianConfig;
    SimulatedAnnealingConfig _simAnnealConfig;

    std::shared_ptr<FileManager> _fileManager;
};

#endif // GRIDVIEWMODEL_H
