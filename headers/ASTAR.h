#ifndef ASTAR_H
#define ASTAR_H
#include "Search.h"

/**
 * Klasa opisująca działanie A*
 *
 */

class Astar_: public Search_{
public:
    /**
     *
     * @param tiles_ wskaźnik do tablicy węzłów grafu
     * @param total_rows_ rozmiar grafu
     * @param start wskaźnik na początkowy węzeł grafu
     * @param end wskaźnik na docelowy węzeł grafu
     */
    Astar_(std::vector<Node*>* tiles_, unsigned int total_rows_, Node* start, Node* end);


    virtual ~Astar_() override;
    ///funkcja rozpoczynająca działanie algorytmu
    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

    ///funkcja usuwa wszytkie wykorzystane elementy
    virtual void reset_attributes() override;

private:

    ///implementowanie kolejki prioritetowej wykorzystywanej w algorytmie
    std::set<std::pair<std::pair<double, uint32_t>, Node*>> priority_queue;

    ///tablica do której zapisują się obliczone wartości g-score
    std::unordered_map<Node*, unsigned int> g_score;

    ///tablica do której zapisują się obliczone wartości f-score
    std::unordered_map<Node*, double> f_score;

    ///funkcja obliczająca heurysykę (w tym przypadku odległość między dwoma punktami)
    double calc_heuristic(sf::Vector2i p1, sf::Vector2i p2);
};


#endif // ASTAR_H