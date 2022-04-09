#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <cmath>
#include <climits>
#include <vector>
#include "Node.h"

///Klasa Algorytm jest jedną z najważniejszych klas aplikacji
///
///Za pomocą tej klasy odbywa się aktualizacja wektora sąsiednich węzłów grafu

class Algorithm_ {
public:
    ///@param tiles_ obiekt przypisywany do wektora wypełnionego obiektami klasy Node
    ///@param total_rows_ rozmiar grafu
    Algorithm_(std::vector<Node*>* tiles_, unsigned int total_rows_);

    virtual ~Algorithm_() = 0;

    /**
     * Wirtualna funkcja która jest wywoływana w innych klasach
     * \param start wskaźnik do początkowego węzła grafu
     * \param end wskażnik do docelowego węzła grafu
     */
    virtual void run(Node* start = nullptr, Node* end = nullptr) = 0;

    ///Funkcja zwraca węzły najkrótszej ścieżki
    std::vector<Node*> getPathNodes();

    ///Funkcja wraca wszystkie odwiedzone węzły w grafie
    std::vector<Node*> getVisitedNodes();

protected:

    /// wektor ten zapisuje węzły grafu
    std::vector<Node*>* tiles;

    /// wskaźnik na nowy wektor który będzie wypełniony obiektami klasy Node
    std::vector<Node*> path_nodes;


    /// wektor ten zapisuje odwiedzone węzły grafu
    std::vector<Node*> visited_nodes;

    /// zmienna definiuje rozmiar grafu
    unsigned int total_rows;

    ///funkcja aktualizuje wektor w który znajdują się sąsiednie węzły grafu
    void updateTileNeighbors();

};

#endif // ALGORITHM_H