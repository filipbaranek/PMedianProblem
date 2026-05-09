#include "dijkstra.h"
#include "../Model/node.h"
#include "../Model/edge.h"
#include <queue>
#include <limits>
#include <vector>

std::map<int, double> Dijkstra::computeShortestPaths(Node* startNode, const std::map<int, Node*>& nodes)
{
    using Pair = std::pair<double, int>;

    std::map<int, double> distances;
    for (const auto& pair : nodes)
    {
        distances[pair.first] = std::numeric_limits<double>::infinity();
    }
    distances[startNode->id()] = 0.0;

    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({0.0, startNode->id()});

    while (!pq.empty())
    {
        auto [currentDist, currentId] = pq.top();
        pq.pop();

        if (currentDist > distances[currentId])
        {
            continue;
        }

        Node* currNode = nodes.at(currentId);

        for (const auto& [edge, neighbor] : currNode->connectedNodes())
        {
            if (!edge->isValid())
            {
                continue;
            }
            if (edge->isOriented() && edge->from() != currNode)
            {
                continue;
            }

            double newDist = currentDist + edge->distance();
            if (newDist < distances[neighbor->id()])
            {
                distances[neighbor->id()] = newDist;
                pq.push({ newDist, neighbor->id() });
            }
        }
    }
    return distances;
}