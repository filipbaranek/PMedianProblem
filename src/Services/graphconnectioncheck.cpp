#include "graphconnectioncheck.h"
#include "../Model/Node.h"
#include "../Model/Edge.h"
#include <vector>

bool GraphConnectionCheck::checkGraphConnection(std::map<int, Node>& nodes)
{
    std::vector<Node*> visitedNodes;

    auto* firstNode = &nodes.begin()->second;
    firstNode->setIsMarked(true);

    visitedNodes.push_back(firstNode);

    while (!visitedNodes.empty())
    {
        auto* currentNode    = visitedNodes.back();
        auto& connectedNodes = currentNode->connectedNodes();

        for (auto& [edge, connectedNode] : connectedNodes)
        {
            if (edge->isValid() && !connectedNode->isMarked())
            {
                connectedNode->setIsMarked(true);
                visitedNodes.push_back(connectedNode);
            }
        }

        visitedNodes.pop_back();
    }

    for (auto& [id, node] : nodes)
    {
        if (!node.isMarked())
        {
            return false;
        }
    }
    return true;
}
