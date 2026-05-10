#ifndef GRID_H
#define GRID_H

#include <QGraphicsView>
#include "../Common/dtos.h"

class IdManager;
class NodeView;
class EdgeView;
class CreateEdgeEvent;
class PMedianSolutionView;

class Grid : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Grid(QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;

    void contextMenuEvent(QContextMenuEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void insertItemsFromFile(const std::map<int, NodeData>& nodes, const std::map<int, EdgeData>& edges);

    void drawSolution(const PMedianSolutionView& solution);

    void clearSolution(const PMedianSolutionView& solution);

    void setEuclideanMode(bool toggled);

signals:
    void onAddNode(const NodeData& node);

    void onAddEdge(const EdgeData& edge);

    void onUpdateNode(const NodeData& node);

    void onUpdateEdge(const EdgeData& edge);

    void onDeleteNode(int id);

    void onDeleteEdge(int id);

    void onClear();

    void onClearSolution();

private:
    void clearLayout();

    void initConnections();

    void initNodeConnections(NodeView* node);

    void initEdgeConnections(EdgeView* edge);

    void addNodeAt(const QPointF& pos);

    void addEdgeBetween(NodeView* from, NodeView* to, bool isSolutionEdge = false);

    void deleteNode(NodeView* node);

    void deleteEdge(EdgeView* edge);

private:
    IdManager&       _idManager;
    QPoint           _lastMousePos;
    CreateEdgeEvent* _edgeEvent;
    QGraphicsScene*  _scene;
    bool             _useEuclideanDistance;
};

#endif // GRID_H