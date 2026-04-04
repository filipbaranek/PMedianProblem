#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <set>
#include <QColor>
#include <QPointF>

class NodeView
{
public:
    NodeView(int id, float posX, float posY, const QColor& color)
        : _id(id), _posX(posX), _posY(posY), _color(color)
    { }

    inline const int& id() const { return _id; }

    inline const float& posX() const { return _posX; }

    inline void setPosX(const float& posX) { _posX = posX; }

    inline const float& posY() const { return _posY; }

    inline void setPosY(const float& posY) { _posY = posY; }

    inline const QColor& color() const { return _color; }

    inline void setColor(const QColor& color) { _color = color; }

    inline const bool& selected() const { return _selected; }

    inline void setSelected(const bool& selected) { _selected = selected; }

    inline void connectNode(const int& node) { _connectedNodes.insert(node); }

    inline bool isNodeConnectedTo(const int& node) { return _connectedNodes.contains(node); }

    inline constexpr const int radius() { return 30; }

    void move(const QPointF& delta);

private:
    int           _id;
    float         _posX;
    float         _posY;
    bool          _selected;
    QColor        _color;
    std::set<int> _connectedNodes;
};

#endif // NODEVIEW_H
