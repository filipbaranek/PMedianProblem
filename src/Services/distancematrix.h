#ifndef DISTANCEMATRIX_H
#define DISTANCEMATRIX_H

#include <map>

class Node;

class DistanceMatrix {
public:
    void build(const std::map<int, Node*>& allNodes);

    double getDistance(int customerId, int storageId) const
    {
        return _matrix.at(customerId).at(storageId);
    }

private:
    std::map<int, std::map<int, double>> _matrix;
};

#endif // DISTANCEMATRIX_H
