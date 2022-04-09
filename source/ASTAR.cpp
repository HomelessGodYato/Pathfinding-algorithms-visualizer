#include "../headers/ASTAR.h"

Astar_::Astar_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end)
        : Search_(tiles_, total_rows_, start, end) {}

Astar_::~Astar_() {}

///@return odleglość między dwoma punktami
double Astar_::calc_heuristic(sf::Vector2i p1, sf::Vector2i p2) {
    return (std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y));
}

void Astar_::run(Node* start, Node* end) {
    start_node = start; // incjalizaja początkowych węzłów
    end_node = end;

    updateTileNeighbors(); // aktualizacja wektora sąsiadów
    unsigned int precedence = 0;
    priority_queue.insert(std::make_pair(std::make_pair(0, precedence), start_node)); // wstawiamy pierwszy element do kolejki
    for (size_t i = 0; i < total_rows; ++i) { // dla każdego węzła obliczany jest g-score
        for (size_t k = 0; k < total_rows; ++k) {
            g_score[tiles[i][k]] = INT_MAX; // INT_MAX - maksymalna wartość typu int
            // na początku dla każdego węzła g-score jest maksymalny
        }
    }
    g_score[start_node] = 0; // dla początkowego węzła optymalna droga g-score jest 0

    // to samo dla f-score
    for (size_t i = 0; i < total_rows; ++i) {
        for (size_t k = 0; k < total_rows; ++k) {
            f_score[tiles[i][k]] = INT_MAX;
        }
    }
    // obliczanie odleglości pomiędzy startowym a końcowym węzłem
    f_score[start_node] = calc_heuristic(start_node->get_coord(), end_node->get_coord());

    std::vector<Node*> priority_queue_tracker = { start_node }; // za pomocą tego można śledzić gdzie jesteśmy w kolejce prioritetowej

    // sprawdzamy każdy element w kolejce
    while (!priority_queue.empty()) {
        auto current_queue = *(priority_queue.begin());
        Node* current = current_queue.second; // aktualny węzeł

        visited_nodes.push_back(current); // dodajemy aktualny węzeł do wektora odwiedzonych

        // iteracje zaczyją się od numeru aktualnego węzła w kolejce
        auto it1 = std::find(priority_queue_tracker.begin(), priority_queue_tracker.end(), current);
        priority_queue.erase(priority_queue.begin()); // usuwamy pierwszy węzeł z kolejki
        if (it1 != priority_queue_tracker.end())
            priority_queue_tracker.erase(it1);

        // jeśli aktualny węzeł jest docelowym to budujemy ścieżkę
        if (current == end_node) {
            reconstruct_path(current);
            return;
        }

        // dla każdego sąsiada aktualnego węzła obliczamy g-score
        for (auto neighbor : current->neighbors) {
            unsigned int temp_g_score = g_score[current] + 1;

            // jeśli g-score dla sąsiada jest większy niż dla aktualnego
            if (temp_g_score < g_score[neighbor]) {
                previous_node[neighbor] = current; // w miejsce poprzedniego sąsiada wstawiamy aktualny węzeł
                g_score[neighbor] = temp_g_score;
                f_score[neighbor] = temp_g_score + calc_heuristic(neighbor->get_coord(), end_node->get_coord());

                // jeśli sąsiad jest ostatnim
                if (std::find(priority_queue_tracker.begin(), priority_queue_tracker.end(), neighbor) == priority_queue_tracker.end()) {
                    precedence += 1; // zwiększamy jego prioritet
                    priority_queue.insert(std::make_pair(std::make_pair(f_score[neighbor], precedence), neighbor)); // wstawiamy do kolejki
                    priority_queue_tracker.push_back(neighbor);// dodajemy sąsiada na koniec treckera

                }
            }
        }
    }
    visited_nodes.clear(); // usuwamy wszystkie odwiedzone węzły

}

// ususwamy wszystkie wykorzystane elementy
void Astar_::reset_attributes() {
    previous_node.clear();
    priority_queue.clear();
    g_score.clear();
    f_score.clear();
    path_nodes.clear();
    visited_nodes.clear();
}