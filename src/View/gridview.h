#ifndef GRID_H
#define GRID_H

#include <utility>
#include <QGraphicsView>
#include "../Common/dtos.h"

class NodeView;
class EdgeView;
class CreateEdgeEvent;

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
    std::pair<std::vector<NodeData>, std::vector<EdgeData>> itemsToDTO();

    void itemsFromDTO(const std::vector<NodeData>& nodes, const std::vector<EdgeData>& edges);

    void setEuclideanMode(bool toggled);

private:
    void addNodeAt(const QPointF& pos);

    void addEdgeBetween(NodeView* from, NodeView* to);

    void deleteNode(NodeView* node);

    void deleteEdge(EdgeView* edge);

private:
    QPoint           _lastMousePos;
    CreateEdgeEvent* _edgeEvent;
    QGraphicsScene*  _scene;
    bool             _useEuclideanDistance;
};

#endif // GRID_H