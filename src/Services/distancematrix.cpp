#include "distancematrix.h"
#include "dijkstra.h"
#include "../Model/Node.h"

void DistanceMatrix::build(const std::map<int, Node*>& allNodes)
{
    for (const auto& [nodeId, node] : allNodes)
    {
        if (node->type() == NodeType::CUSTOMER)
        {
            auto distances = Dijkstra::computeShortestPaths(node, allNodes);

            for(const auto& [targetNodeId, distance] : distances)
            {
                Node* targetNode = allNodes.at(targetNodeId);
                if (targetNode->type() == NodeType::STORAGE)
                {
                    _matrix[node->id()][targetNode->id()] = distance;
                }
            }
        }
    }
}
