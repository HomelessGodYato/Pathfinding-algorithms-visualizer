#include "../headers/Dijkstra.h"

Dijkstra_::Dijkstra_(std::vector<Node*>* tiles_, unsigned int total_rows_, Node* start, Node* end)
        : Search_(tiles_, total_rows_, start, end) {}

Dijkstra_::~Dijkstra_() {}

/// Funkcja która rozpoczyna działanie algorytmu
void Dijkstra_::run(Node* start, Node* end) {
    start_node = start;// ustawienie początkowego i docelowego węzłów
    end_node = end;

    updateTileNeighbors();// aktualizacja sąsiadów

    bool found_end = false;// na początku koniec nie jest znalieziony
    for (size_t i = 0; i < total_rows; ++i) {// dla każdego węzła obliczany jest g-score
        for (size_t k = 0; k < total_rows; ++k) {
            g_score[tiles[i][k]] = INT_MAX;//INT_MAX - maksymalna wartość typu int
            // na początku dla każdego węzła g-score jest maksymalny
        }
    }

    g_score[start_node] = 0;// dla początkowego węzła optymalna droga g-score jest 0
    priority_queue.insert(std::make_pair(g_score[start_node], start_node)); //wstawiamy parę do kolejki prioritetowej

    // sprawdzamy każdy element kolejki
    while (!priority_queue.empty()) {
        Node* current_node = (priority_queue.begin())->second; // aktualny węzeł
        //warunek przy znalezieniu węzła docelowego
        if (current_node == end_node)
            found_end = true;
        //jeśli nie znaleziony
        if (!found_end)
            visited_nodes.push_back(current_node); // wstawiamy aktualny węzeł na koniec odwiedzonych

        unsigned int current_dist = (priority_queue.begin())->first; // odległość od aktualnego
        priority_queue.erase(priority_queue.begin()); // usuwamy z kolejki początkowy element

        // sprawdzamy każdego sąsiada dla aktualnego węzła
        for (auto neighbor : current_node->neighbors) {
            if (current_dist + 1 < g_score[neighbor]) { // jeśli odległość od aktualnego mniejsza niż od sąsiada
                auto find_node = priority_queue.find(std::make_pair(g_score[neighbor], neighbor));
                //jeśli znaleziony nie jest na końcu kolejki to usuwamy go
                if (find_node != priority_queue.end())
                    priority_queue.erase(find_node);

                g_score[neighbor] = current_dist + 1; // obliczamy g-score dla sąsiada
                priority_queue.insert(std::make_pair(g_score[neighbor], neighbor)); // wstawiamy parę sąsiad-g_score do kolejki
                previous_node[neighbor] = current_node;//poprzednim węzłem dla sąsiedniego jest aktualny
            }
        }
    }
    //jeśli koniec nie znaleziony
    if (!found_end)
        visited_nodes.clear(); // usuwamy wszystkie odwiedzone

    //inaczej - tworzymy ścieżkę
    else
        reconstruct_path(end_node);
}
///Tak samo jak w Astar_
void Dijkstra_::reset_attributes() {
    previous_node.clear();
    priority_queue.clear();
    g_score.clear();
    path_nodes.clear();
    visited_nodes.clear();
}

