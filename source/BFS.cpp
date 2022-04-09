#include "../headers/BFS.h"

BFS_::BFS_(std::vector<Node*>* tiles_, unsigned int total_rows_, Node* start, Node* end)
        : Search_(tiles_, total_rows_, start, end) {}

BFS_::~BFS_() {}
/// funkcja zaczynająca działanie algorytmu

void BFS_::run(Node* start, Node* end) {
    start_node = start; // ustawienie początkowych węzłów
    end_node = end;

    updateTileNeighbors(); // aktualizacja sąsiadów

    _queue.push(start_node); // dodanie do kolejki początkowy węzeł
    visited[start_node] = true; // ustawianie stanu węzła na odwiedzony

    bool found_end = false; // stan znalezionego końca, na początku = false

    // sprawdzamy każdy węzeł w kolejce
    while (!_queue.empty()) {
        Node* current_node = _queue.front(); // aktualny węzel - wskaźnik na pierwszy węzeł w kolejce
        if (current_node == end_node)
            found_end = true;

        if (!found_end)
            visited_nodes.push_back(current_node); // wstawiamy aktualny węzeł na koniec odwiedzonych węzłów

        _queue.pop(); // usuwamy pierwszy elemnet z kolejki
        // sprawdzamy każdego sąsiada aktualnego węzła
        for (auto neighbor : current_node->neighbors) {
            if (!visited[neighbor]) { //jeśli nie jest odwiedzony to wstawimy do kolejki
                _queue.push(neighbor);
                visited[neighbor] = true; // zmieniamy stan na odwiedzony
                previous_node[neighbor] = current_node; // aktualny węzeł jest poprzednikiem jego sąsiada (następnego)
            }
        }
    }

    if (!found_end) // jeśli nie znalieziono węzła docelowego to usuwamy wszystkie odwiedzone węzły
        visited_nodes.clear();
    else
        reconstruct_path(end_node); // w innym przypadku tworzymy ścieżkę
}
/// To samo co w Astar_
void BFS_::reset_attributes() {
    previous_node.clear();
    std::queue<Node*> empty;
    std::swap(_queue, empty);
    visited.clear();
    path_nodes.clear();
    visited_nodes.clear();
}

