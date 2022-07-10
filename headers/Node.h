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



struct Node {
    
    std::vector<Node*> neighbors;
    sf::RectangleShape tile_shape;
    sf::Color          color;

    unsigned int row, col;
    unsigned int total_rows;
    float    x, y;
    float    width;
    bool visited_maze;
    void draw_node(sf::RenderWindow* window);

    Node(unsigned int row, unsigned int col, float width, unsigned int total_rows);

    void update_neighbors(std::vector<Node*>* board);

    void set_start();
    
    void set_target();
    
    void set_obstacle();

    void set_visited();
    
    void set_open();
    
    void set_path();

    void reset();

    bool is_obstacle();

    sf::Vector2i get_coord();
};

#endif 