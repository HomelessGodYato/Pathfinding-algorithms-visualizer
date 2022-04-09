#include "../headers/RecMaze.h"

RecursiveMaze::RecursiveMaze(std::vector<Node*>* tiles_, unsigned int total_rows_)
        : Algorithm_(tiles_, total_rows_) {}

RecursiveMaze::~RecursiveMaze() {}

///Funkcja zaczynająca działanie algorytmu
void RecursiveMaze::run(Node* start, Node* end) {
    updateTileNeighbors(); // aktualizacja sąsiadów
    std::unordered_map<Node*, bool> visited; // dodanie do kontenera pary węzeł-stan
    Node* current = tiles[0][0]; // węzeł początkowy na pozycji 0 0
    maze_recursion(current); // rekurencja z aktualnym węzłem
}
///Funkcja generowania labiryntu
void RecursiveMaze::maze_recursion(Node* current) {
    current->visited_maze = true; // aktualny węzeł jest odwiedzony
    std::vector<Node*> randomized_neighbors = current->neighbors; // wektor losowo wybranych sąsiadów
    std::random_shuffle(randomized_neighbors.begin(), randomized_neighbors.end()); // tasowanie

    for (auto neighbor : randomized_neighbors) {
        Node* next_neighbor = nullptr; // następny węzłem wskazuje na nic

        if (neighbor->row > current->row) {
            if (!(tiles[neighbor->row + 1][neighbor->col])->visited_maze) {
                next_neighbor = tiles[neighbor->row + 1][neighbor->col];
            }
        }
        else if (neighbor->row < current->row) {
            if (!neighbor->row == 0) {
                if (!(tiles[neighbor->row - 1][neighbor->col])->visited_maze) {
                    next_neighbor = tiles[neighbor->row - 1][neighbor->col];
                }
            }
        }
        else if (neighbor->col > current->col) {
            if (!(tiles[neighbor->row][neighbor->col + 1])->visited_maze) {
                next_neighbor = tiles[neighbor->row][neighbor->col + 1];
            }
        }
        else if (neighbor->col < current->col) {
            if (!(tiles[neighbor->row][neighbor->col - 1])->visited_maze) {
                next_neighbor = tiles[neighbor->row][neighbor->col - 1];
            }
        }
        if (next_neighbor != nullptr) {
            neighbor->visited_maze = true;
            maze_recursion(next_neighbor);
        }
    }
}
