#include "../headers/Node.h"



Node::Node(unsigned int row, unsigned int col, float width, unsigned int total_rows) {
    this->row = row;
    this->col = col;
    this->width = width;
    this->x = row * (float)width;
    this->y = col * (float)width;
    this->color = sf::Color::White;
    
    this->total_rows = total_rows;
    tile_shape.setSize(sf::Vector2f(width, width));
    tile_shape.setPosition(x, y);
    tile_shape.setFillColor(color);
    visited_maze = false; 

}


void Node::update_neighbors(std::vector<Node*>* board) {
    neighbors.clear();
    if (row < total_rows - 1 && !(board[row + 1][col]->is_obstacle()))
        neighbors.push_back(board[row + 1][col]);

    if (row > 0 && !(board[row - 1][col]->is_obstacle()))
        neighbors.push_back(board[row - 1][col]);

    if (col < total_rows - 1 && !(board[row][col + 1]->is_obstacle()))
        neighbors.push_back(board[row][col + 1]);

    if (col > 0 && !(board[row][col - 1]->is_obstacle()))
        neighbors.push_back(board[row][col - 1]);
}

sf::Vector2i Node::get_coord() {
    return sf::Vector2i(row, col);
}

bool Node::is_obstacle() { return color == sf::Color(OBSTACLE_COLOR); }

void Node::set_start() {
    color = sf::Color(START_COLOR);
    tile_shape.setFillColor(color);
}

void Node::set_target() {
    color = sf::Color(TARGET_COLOR);
    tile_shape.setFillColor(color);
}

void Node::set_obstacle() {
    color = sf::Color(OBSTACLE_COLOR);
    tile_shape.setFillColor(color);
}

void Node::set_visited() {
    color = sf::Color(VISITED_COLOR);
    tile_shape.setFillColor(color);
}

void Node::set_open() {
    color = sf::Color(OPEN_COLOR);
    tile_shape.setFillColor(color);
}

void Node::set_path() {
    color = sf::Color(PATH_COLOR);
    tile_shape.setFillColor(color);
}

void Node::reset() {
    color = sf::Color(BLANK_COLOR);
    tile_shape.setFillColor(color);
}

void Node::draw_node(sf::RenderWindow* window) {
    window->draw(tile_shape);
}
