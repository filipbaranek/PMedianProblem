#ifndef DTOS_H
#define DTOS_H

#include <QString>

struct NodeData
{
    int         _id;
    QStringView _name;
    int32_t     _type;
    double      _posX;
    double      _posY;
    double      _variableParameter;
};

struct EdgeData
{
    int    _from;
    int    _to;
    bool   _useEuclideanDistance;
    bool   _isValid;
    bool   _isOriented;
    double _distance;
};

#endif // DTOS_H
