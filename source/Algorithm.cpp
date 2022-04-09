#include "../headers/Algorithm.h"

Algorithm_::Algorithm_(std::vector<Node*>* tiles_, unsigned int total_rows_) :
        tiles(tiles_), total_rows(total_rows_) {}

Algorithm_::~Algorithm_() {}

void Algorithm_::updateTileNeighbors() {
    //dla każdego węzła aktualizujemy sąsiadów
    for (size_t i = 0; i < total_rows; ++i) {
        for (auto node : tiles[i])
            node->update_neighbors(tiles);// funkcja z klasy Node
    }
}
///@return  wektor węzłów ścieżki
std::vector<Node*> Algorithm_::getPathNodes() { return path_nodes; }

///@return wektor odwiedzonych węzłów
std::vector<Node*> Algorithm_::getVisitedNodes() { return visited_nodes; }

