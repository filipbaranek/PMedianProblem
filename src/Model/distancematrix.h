#ifndef DISTANCEMATRIX_H
#define DISTANCEMATRIX_H

#include <map>

class Node;

class DistanceMatrix {
public:
    DistanceMatrix(const std::map<int, Node>& nodes);

    double distance(int customerId, int storageId) const
    {
        return _matrix.at(customerId).at(storageId);
    }

private:
    void build(const std::map<int, Node>& nodes);

private:
    std::map<int, std::map<int, double>> _matrix;
};

#endif // DISTANCEMATRIX_H
