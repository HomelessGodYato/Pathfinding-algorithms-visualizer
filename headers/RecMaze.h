#ifndef RECURSIVE_MAZE_H
#define RECURSIVE_MAZE_H
#include <unordered_map>
#include "Algorithm.h"

/**
 * Klasa opisująca działanie recurenczyjnego generowania labiryntu
 *
 * Jest opisanie podobnie jak klasa Astar_
 */

class RecursiveMaze : public Algorithm_ {
public:

    RecursiveMaze(std::vector<Node*>* tiles_, unsigned int total_rows_);

    virtual ~RecursiveMaze() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

private:

    void maze_recursion(Node* current);

};

#endif // RECURSIVE_MAZE_H
