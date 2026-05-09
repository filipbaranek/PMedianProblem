#include "distancematrix.h"
#include "../Services/dijkstra.h"
#include "../Model/node.h"

DistanceMatrix::DistanceMatrix(const std::map<int, Node*>& nodes)
{
    build(nodes);
}

void DistanceMatrix::build(const std::map<int, Node*>& nodes)
{
    for (const auto& [nodeId, node] : nodes)
    {
        if (node->type() == NodeType::CUSTOMER)
        {
            auto distances = Dijkstra::computeShortestPaths(node, nodes);

            for(const auto& [targetNodeId, distance] : distances)
            {
                Node* targetNode = nodes.at(targetNodeId);
                if (targetNode->type() == NodeType::STORAGE)
                {
                    _matrix[node->id()][targetNode->id()] = distance;
                }
            }
        }
    }
}
