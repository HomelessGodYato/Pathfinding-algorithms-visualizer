#ifndef BFS_H
#define BFS_H
#include <queue>
#include "Search.h"

/**
 * Klasa opisująca działanie algorytmu BFS
 *
 * Klasa jest podobna do Astar_
 */
class BFS_ : public Search_ {
public:

    BFS_(std::vector<Node*>* tiles_, unsigned int total_rows_, Node* start, Node* end);

    virtual ~BFS_() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

    virtual void reset_attributes() override;

private:

    /**
     * kontener kóry chroni w sobie pary węzeł-stan
     * stan węzła jest 0-1
     * 0-nie odwiedzony
     * 1-odwiedzony
     */

    std::unordered_map<Node*, bool> visited;

    // implementowanie kolejki
    std::queue<Node*> _queue;

};


#endif // BFS_H
