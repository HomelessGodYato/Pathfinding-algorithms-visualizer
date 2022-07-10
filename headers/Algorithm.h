#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <cmath>
#include <climits>
#include <vector>
#include "Node.h"

class Algorithm_ {
public:
    Algorithm_(std::vector<Node*>* tiles_, unsigned int total_rows_);

    virtual ~Algorithm_() = 0;
    virtual void run(Node* start = nullptr, Node* end = nullptr) = 0;

    std::vector<Node*> getPathNodes();

    std::vector<Node*> getVisitedNodes();

protected:

    std::vector<Node*>* tiles;
    std::vector<Node*> path_nodes;
    std::vector<Node*> visited_nodes;

    unsigned int total_rows;

    void updateTileNeighbors();

};

#endif // ALGORITHM_H