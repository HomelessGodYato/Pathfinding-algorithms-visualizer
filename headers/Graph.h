#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"
#include "ASTAR.h"
#include "Dijkstra.h"
#include "BFS.h"
#include "DFS.h"
#include "RecMaze.h"
#include <vector>
#include <utility>

/**
 * Klasa opisująca wszytkie działania z węzłami grafu
 */

///Przeliczenie algorytmów poszukiwania
enum Enum_Search { ASTAR, DIJKSTRA, BFS, DFS };

///Przeliczenie algorytmów generacji mapy
enum Maze_Algorithms { RM };

class Graph {
public:
    /// odległóść między wierszami siatki
    static constexpr float ratio_row = 0.1555555556f;

    /**
     *
     * @param rows liczba wierszy siatki
     * @param width liczba pikseli okna aplikacji
     */
    Graph(unsigned int rows, unsigned int width);

    /**
     * Funkcja budująca graf
     * @param rows liczba wierszy siatki
     * @param width liczba pikseli okna aplikacji
     */
    void construct_graph(unsigned int rows, unsigned int width);

    ///Funkcja wyczyszczająca graph
    void clear_graph();

    /**
     * Funkcja rysująca siatkę na ekranie
     * @param window wskaźnik do okna aplikacji
     * @param enable stan rysowania siatki true-false
     */
    void draw_grid(sf::RenderWindow* window, const bool& enable);

    /**
     * Funkcja rysująca poszczególne pola siatki na ekranie
     * @param window wskaźnik do okna aplikacji
     * @param visualize_visiting stan wizualizacji algorytmu
     */
    void draw_tiles(sf::RenderWindow* window, const bool& visualize_visiting);

    /**
     * Funkcja rysująca poszczególne pola siatki na ekranie
     * @param window wskaźnik do okna aplikacji
     * @param visualize_visiting stan wizualizacji algorytmu
     */

    /**
     * Funkcja inicjalizaji węzła początkowego
     * @param v__ wskaźnik na węzeł początkowy
     */
    void assign_start(Node* v__);

    ///Funkcja usuwająca węzeł początkowy
    void remove_start();

    ///Funkcja usuwająca węzeł docelowy
    void remove_end();

    /**
     * Funkcja inicjalizaji węzła docelowego
     * @param v__ wskaźnik na węzeł docelowy
     */
    void assign_end(Node* v__);
    /**
     * Funkcja inicjalizaji wybranego algorytmu
     * @param v__ Algorytm poszukiwania
     */
    void assign_curr_search_algo(Enum_Search v__);

    /**
     * Funkcja inicjalizaji algorytmu generowania mapy
     * @param v__ Algorytm generowania
     */
    void assign_curr_terr_algo(Maze_Algorithms v__);

    ///@return tablicę węzłów grafu
    std::vector<Node*>* get_board() const;

    ///@return liczbę wszystkich węzłów grafu
    unsigned int get_total_rows() const;

    /// @return parę węzłów początkowy - docelowy
    std::pair<Node*, Node*> STNodes() const;

    /// @return aktualny wybrany algorytm poszukiwania do @class Search_
    Search_* g_curr_search_algo() const;

    /// @return aktualny wybrany algorytm generowania do @class Search_
    Algorithm_* g_curr_terr_algo() const;

    ///@return pozycje kursora po kliknęciu
    sf::Vector2u rowcol_pos_click(sf::Vector2i pos);

private:

    ///Tablica wszystkich węzłów grafu
    std::vector<Node*>* board;

    std::vector<Algorithm_*> terrain_algorithms;
    std::vector<Search_*>    search_algorithms;

    Maze_Algorithms current_maze_algo;
    Algorithm_* current_terrain_algo;
    Search_* current_search_algo;

    ///Węzeł początkowy
    Node* start_node;
    ///Węzeł docelowy
    Node* end_node;

    unsigned int board_width;
    unsigned int total_rows;
    float    tile_gap;

    /// Obiekt z biblioteki SFML definiujący linię poziomą
    sf::RectangleShape horLine;

    /// Obiekt z biblioteki SFML definiujący linię pinową
    sf::RectangleShape vertLine;

    /// Obiekt z biblioteki SFML definiujący prostokąt (węzeł początkowy)
    sf::RectangleShape green_tile;

    /// Obiekt z biblioteki SFML definiujący prostokąt (węzeł docelowy)
    sf::RectangleShape red_tile;

};

#endif // GRAPH_H