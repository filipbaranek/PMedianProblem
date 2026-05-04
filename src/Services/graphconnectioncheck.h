#ifndef GRAPHCONNECTIONCHECK_H
#define GRAPHCONNECTIONCHECK_H

#include <map>

class Node;
class Edge;

class GraphConnectionCheck
{
public:
    GraphConnectionCheck() = delete;

    GraphConnectionCheck(const GraphConnectionCheck&) = delete;

    ~GraphConnectionCheck() = delete;

    GraphConnectionCheck& operator=(const GraphConnectionCheck&) = delete;

    static bool checkGraphConnection(std::map<int, Node>& nodes);
};

#endif // GRAPHCONNECTIONCHECK_H
