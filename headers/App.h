#ifndef APP_H
#define APP_H
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"
#include <unordered_map>

class App
{
public:
    void run();
    App(unsigned int total_rows);
    ~App();

    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Mouse mousePos;
    sf::Clock dtClock;
    int size;

private:
    std::vector<Node*> visited_nodes;
    std::vector<Node*> path_nodes;
    std::vector<Node*>* maze_path;
    unsigned int visited_count;
    unsigned int path_count;
    unsigned int maze_count;
    Graph graph;

    
    bool visualize_visiting;
    
    bool visualize_path;
    
    bool finished_visualizing;
    
    bool visualize_maze;
    
    bool app_in_focus;
    
    bool grid_status;

    
    void render();
    
    void updateSFMLEvents();
    
    void imgui_update();
    
    void update();

};

#endif