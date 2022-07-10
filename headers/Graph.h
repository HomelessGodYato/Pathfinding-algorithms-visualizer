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


enum Enum_Search { ASTAR, DIJKSTRA, BFS, DFS };

enum Maze_Algorithms { RM };

class Graph {
public:
    
    static constexpr float ratio_row = 0.1555555556f;
    Graph(unsigned int rows, unsigned int width);
    void construct_graph(unsigned int rows, unsigned int width);
    void clear_graph();
    void draw_grid(sf::RenderWindow* window, const bool& enable);
    void draw_tiles(sf::RenderWindow* window, const bool& visualize_visiting);
    void assign_start(Node* v__);
    void remove_start();
    void remove_end();
    void assign_end(Node* v__);
    void assign_curr_search_algo(Enum_Search v__);
    void assign_curr_terr_algo(Maze_Algorithms v__);
    std::vector<Node*>* get_board() const;
    unsigned int get_total_rows() const;
    std::pair<Node*, Node*> STNodes() const;
    Search_* g_curr_search_algo() const;
    Algorithm_* g_curr_terr_algo() const;
    sf::Vector2u rowcol_pos_click(sf::Vector2i pos);

private:
    std::vector<Node*>* board;
    std::vector<Algorithm_*> terrain_algorithms;
    std::vector<Search_*>    search_algorithms;
    Maze_Algorithms current_maze_algo;
    Algorithm_* current_terrain_algo;
    Search_* current_search_algo;
    Node* start_node;
    Node* end_node;
    unsigned int board_width;
    unsigned int total_rows;
    float    tile_gap;
    sf::RectangleShape horLine;
    sf::RectangleShape vertLine;
    sf::RectangleShape green_tile;
    sf::RectangleShape red_tile;
};
#endif 