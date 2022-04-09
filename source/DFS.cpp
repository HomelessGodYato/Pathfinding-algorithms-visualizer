#include "../headers/DFS.h"

DFS_::DFS_(std::vector<Node*>* tiles_, unsigned int total_rows_, Node* start, Node* end)
        : Search_(tiles_, total_rows_, start, end) {}

DFS_::~DFS_() {}

/// Funkcja która rozpoczyna działanie algorytmu
void DFS_::run(Node* start, Node* end) {
    start_node = start; // ustawienie początkowego i docelowego węzłów
    end_node = end;
    updateTileNeighbors(); // aktualizacja sąsiadów

    std::unordered_map<Node*, bool> visited; // tworzenie kontenera par węzeł-stan
    bool found_end = false; // na początku koniec nie jest znalieziony
    DFS_recursion(visited, start_node, found_end); // funkcja rekurencyjna
    if (!found_end)
        visited_nodes.clear(); // jeśli koniec nie znaleziony to usuwamy wszystkie odwiedzone węzły
    else
        reconstruct_path(end_node); //inaczej tworzymy ścieżkę
}

void DFS_::DFS_recursion(std::unordered_map<Node*, bool>& visited, Node* current, bool& found_end) {
    visited[current] = true; //aktualny węzeł odwiedzony
    if (current == end_node) // jeśli aktualny węzeł jest końcowym
        found_end = true; // ustawiamy stan znalezionego końca na true
    if (!found_end) // inaczej ustawiamy aktualny węzeł na koniec wektora odwiedzonych
        visited_nodes.push_back(current);
    // sprawdzamy każdego sąsiada dla aktualnego węzła
    for (auto neighbor : current->neighbors) {
        if (!visited[neighbor]) { //jeśli sąsiad nie jest odwiedony
            previous_node[neighbor] = current; // aktualny węzeł jest poprzedim węzłem sąsiada
            DFS_recursion(visited, neighbor, found_end); // rekurencja
        }
    }
}

///To samo co w Astar_
void DFS_::reset_attributes() {
    previous_node.clear();
    path_nodes.clear();
    visited_nodes.clear();
}