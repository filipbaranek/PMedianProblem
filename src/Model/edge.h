#ifndef EDGE_H
#define EDGE_H

class Node;

class Edge
{
public:
    const int id() const
    {
        return _id;
    }

    const Node* from() const
    {
        return _from;
    }

    const Node* to() const
    {
        return _to;
    }

    const double distance() const
    {
        return _distance;
    }

    const bool isValid() const
    {
        return _isValid;
    }

    const bool isOriented() const
    {
        return _isOriented;
    }

    friend class EdgeBuilder;

private:
    int    _id;
    Node*  _from;
    Node*  _to;
    double _distance;
    bool   _isValid;
    bool   _isOriented;
};

#endif // EDGE_H
