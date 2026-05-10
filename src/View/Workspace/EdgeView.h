#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include <QGraphicsItem>
#include "../../Common/dtos.h"
#include "../../Common/idata.h"

class EdgeViewBuilder;
class NodeView;

class EdgeView : public QObject, public QGraphicsLineItem, public IData<EdgeData>
{
    Q_OBJECT

public:
    EdgeView(QGraphicsItem* parent = nullptr);

    void updatePosition();

    void setFrom(const QString& from);

    void setFrom(NodeView* from);

    void setTo(NodeView* to);

    void setUseEuclideanDistance(const bool& useEuclideanDistance);

    void setIsValid(const bool& isValid);

    void setIsOriented(const bool& isOriented);

    void setIsSolutionEdge(const bool& isSolutionEdge);

    void setDistance(const double distance);

    void setDistance();

    const int id() const;

    NodeView* from() const;

    NodeView* to() const;

    const bool useEuclideanDistance() const;

    const bool isValid() const;

    const bool isOriented() const;

    const bool isSolutionEdge() const;

    const double distance() const;

    EdgeData toDTO() override;

    friend class EdgeViewBuilder;

signals:
    void onUpdatePosition(const EdgeData& edge);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    int       _id;
    NodeView* _from;
    NodeView* _to;
    bool      _useEuclideanDistance;
    bool      _isValid;
    bool      _isOriented;
    bool      _isSolutionEdge;
    double    _distance;
};

#endif // EDGEVIEW_H