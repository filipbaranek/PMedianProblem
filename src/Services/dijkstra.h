#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <map>

class Node;

class Dijkstra {
public:
    Dijkstra() = delete;

    static std::map<int, double> computeShortestPaths(const Node& startNode, const std::map<int, Node>& nodes);
};

#endif // DIJKSTRA_H
