#ifndef NODE_H
#define NODE_H
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>

#define PATH_COLOR 204,0,0

#define OBSTACLE_COLOR sf::Color::Black

#define VISITED_COLOR 255,255,0

#define OPEN_COLOR 102,204,0

#define START_COLOR 0,153,0

#define TARGET_COLOR 56,17,253

#define BLANK_COLOR sf::Color::White

/**
 * Klasa podstawowa na której obiektach działa większość innych klas
 */

struct Node {
    ///wektor sąsiednich węzłów grafu
    std::vector<Node*> neighbors;
    sf::RectangleShape tile_shape;
    sf::Color          color;

    unsigned int row, col;
    unsigned int total_rows;
    float    x, y;
    float    width;

    /// stan odwiedzenia labiryntu true - false
    bool visited_maze;

    void draw_node(sf::RenderWindow* window);
    /**
     * Konstruktor klasy Node
     *
     * \param row liczba wierszy siatki
     * \param col liczba kolum siatki
     * \param width liczba pikseli na ekranie
     * \param total_rows ustawia rozmiar siatki
     */

    Node(unsigned int row, unsigned int col, float width, unsigned int total_rows);

    /**
     * Funkcja która która aktualizuje sąsiednie węzły grafu
     *
     * \param board jest przekazywany wektor wypełniony siąsiednimi węzłami
     */

    ///Funkcja aktualizuje wektór sąsiednich węzłów
    void update_neighbors(std::vector<Node*>* board);

    ///Funkcja ustawiająca węzeł początkowy
    void set_start();

    ///Funkcja ustawiająca węzeł docelowy
    void set_target();

    ///Funkcja ustawia węzeł przeszkodą
    void set_obstacle();

    ///Funkcja ustawia węzeł odwiedzonym
    void set_visited();

    ///Funkcja ustawia węzeł otwrtym (możliwym do sprawdzenia)
    void set_open();

    ///Funkcja ustawia węzeł węzłem ścieżki
    void set_path();

    ///Funkcja usuwa wszystkie atrybuty
    void reset();

    ///Funkcja sprawdza czy węzeł jest przeszkodą
    bool is_obstacle();

    ///@return polożenie węzła
    sf::Vector2i get_coord();
};

#endif // NODE_H