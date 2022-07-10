#include "../headers/App.h"
#include <string>


App::App(unsigned int total_rows) : graph(total_rows, sf::VideoMode::getDesktopMode().height) {
    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pathfinding Visualizer", sf::Style::None);

    window->setFramerateLimit(120);
    visualize_visiting = false;
    size = 45;
    visualize_path = false;
    finished_visualizing = false;
    visualize_maze = false;
    app_in_focus = true;
    grid_status = true;
    visited_count = 0;
    path_count = 0;
    maze_count = 0;
    maze_path = new std::vector<Node *>[total_rows];
}


void App::updateSFMLEvents() {
    
    while (window->pollEvent(sfEvent)) {
        ImGui::SFML::ProcessEvent(sfEvent);
        switch (sfEvent.type) {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                if (sfEvent.key.code == sf::Keyboard::Escape) {
                    window->close();
                }
                break;
            case sf::Event::LostFocus:
                app_in_focus = false;
                break;
            case sf::Event::GainedFocus:
                app_in_focus = true;
                break;
            default:
                break;
        }
    }
}


void App::update() {
    updateSFMLEvents();

    if (app_in_focus) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { 
            sf::Vector2u rowcol = graph.rowcol_pos_click(mousePos.getPosition(*window));
            if (finished_visualizing) {
                for (size_t i = 0; i < graph.get_total_rows(); ++i) {
                    for (auto node: graph.get_board()[i]) {
                        if (node->color == sf::Color(PATH_COLOR) || node->color == sf::Color(VISITED_COLOR)
                            || node->color == sf::Color(OPEN_COLOR)) {
                            node->reset();
                        }
                    }
                    finished_visualizing = false;

                }
            }

            else if (rowcol.x < graph.get_total_rows() && rowcol.y < graph.get_total_rows()) {
                Node *clicked_node = graph.get_board()[rowcol.x][rowcol.y];
                if (!(graph.STNodes().first) && clicked_node != graph.STNodes().second) {
                    graph.assign_start(clicked_node);
                } else if (!(graph.STNodes().second) && clicked_node != graph.STNodes().first) {
                    graph.assign_end(clicked_node);
                } else if (clicked_node != graph.STNodes().second && clicked_node != graph.STNodes().first) {
                    clicked_node->set_obstacle();
                }
            }

        }
        
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2u rowcol = graph.rowcol_pos_click(mousePos.getPosition(*window));
            if (rowcol.x < graph.get_total_rows()) {
                Node *clicked_node = graph.get_board()[rowcol.x][rowcol.y];
                if (clicked_node == graph.STNodes().first && graph.STNodes().second != nullptr) {
                    clicked_node->reset();
                    graph.remove_start();
                } else if (clicked_node == graph.STNodes().second && graph.STNodes().first != nullptr) {
                    clicked_node->reset();
                    graph.remove_end();
                } else if (clicked_node != graph.STNodes().first && clicked_node != graph.STNodes().second) {
                    clicked_node->reset();

                }
            }

        }

    }
}

void App::imgui_update() {
    static bool AStar_checkbox = false;
    static bool Dijkstra_checkbox = false;
    static bool DFS_checkbox = false;
    static bool BFS_checkbox = false;

    static bool Recursive_check = false;

    ImGui::SFML::Update(*window, dtClock.restart());
    ImGui::Begin("User Interface");
    {
        ImGui::SetWindowFontScale(2.5);
        ImGui::SetWindowPos(ImVec2(sf::VideoMode().getDesktopMode().height, 0));
        ImGui::SetWindowSize(
                ImVec2((sf::VideoMode().getDesktopMode().width - sf::VideoMode().getDesktopMode().height) + 1, 0),
                sf::VideoMode::getDesktopMode().height);

        ImGui::BeginTabBar("Operations");
        if (ImGui::BeginTabItem("Pathfinding Algorithms")) {
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "Choose algorithm");
            for (int i = 0; i < 5; i++) {
                ImGui::Spacing();
            }
            ImGui::Checkbox("A*", &AStar_checkbox);
            ImGui::Spacing();
            ImGui::Spacing();

            ImGui::Checkbox("Dijkstra", &Dijkstra_checkbox);
            ImGui::Spacing();
            ImGui::Spacing();

            ImGui::Checkbox("BFS", &BFS_checkbox);
            ImGui::Spacing();
            ImGui::Spacing();

            ImGui::Checkbox("DFS", &DFS_checkbox);
            ImGui::Spacing();
            ImGui::Spacing();

            
            if (AStar_checkbox) {

                graph.assign_curr_search_algo(Enum_Search::ASTAR);

            } else if (Dijkstra_checkbox) {

                graph.assign_curr_search_algo(Enum_Search::DIJKSTRA);

            } else if (BFS_checkbox) {

                graph.assign_curr_search_algo(Enum_Search::BFS);

            } else if (DFS_checkbox) {

                graph.assign_curr_search_algo(Enum_Search::DFS);

            }

            
            if (ImGui::Button("Solve", ImVec2(200, 100))) {
                if (graph.STNodes().first != nullptr && graph.STNodes().second != nullptr) {
                    if (!visualize_visiting && !visualize_path) {
                        graph.g_curr_search_algo()->run(graph.STNodes().first, graph.STNodes().second);
                        visited_nodes = graph.g_curr_search_algo()->getVisitedNodes();
                        path_nodes = graph.g_curr_search_algo()->getPathNodes();
                        graph.g_curr_search_algo()->reset_attributes();

                        if (!visited_nodes.empty()) {
                            visualize_visiting = true;
                        }
                    }
                }
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Maze Algorithm")) {
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "Generate random recursive maze:");
            for (int i = 0; i < 5; i++) {
                ImGui::Spacing();
            }

            
            ImGui::Checkbox("Recursive Maze", &Recursive_check);
            if (Recursive_check) {

                graph.assign_curr_terr_algo(Maze_Algorithms::RM);

            }
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();

            
            if (ImGui::Button("Generate", ImVec2(200, 100))) {
                if (graph.STNodes().first != nullptr && graph.STNodes().second != nullptr) {
                    if (!visualize_visiting && !visualize_path && !visualize_maze) {
                        for (size_t i = 0; i < graph.get_total_rows(); ++i) {
                            for (auto node: graph.get_board()[i]) {
                                node->visited_maze = false;
                                if (node != graph.STNodes().first && node != graph.STNodes().second) {
                                    node->reset();
                                }
                            }
                        }


                        graph.g_curr_terr_algo()->run(graph.STNodes().first);
                        for (size_t i = 0; i < graph.get_total_rows(); ++i) {
                            for (size_t k = 0; k < graph.get_total_rows(); ++k) {
                                if (!graph.get_board()[i][k]->visited_maze) {
                                    maze_path[i].push_back(graph.get_board()[i][k]);
                                }
                            }
                        }

                        graph.STNodes().first->reset();
                        graph.STNodes().second->reset();
                        graph.assign_start(
                                graph.get_board()[(size_t) std::round(graph.get_total_rows() * Graph::ratio_row) -
                                                  1][
                                        graph.get_total_rows() / 2]);
                        graph.assign_end(graph.get_board()[graph.get_total_rows() - (size_t) std::round(
                                graph.get_total_rows() * Graph::ratio_row)][graph.get_total_rows() / 2]);

                        graph.STNodes().first->set_start();
                        graph.STNodes().second->set_target();
                        visualize_maze = true;


                    }

                }
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();


        for (int i = 0; i < 10; i++) {
            ImGui::Spacing();
        }

        
        if (ImGui::Button("Clear", ImVec2(200, 100))) {
            if (graph.STNodes().first != nullptr && graph.STNodes().second != nullptr) {
                if (!visualize_visiting && !visualize_path && !visualize_maze) {
                    for (size_t i = 0; i < graph.get_total_rows(); ++i) {
                        for (auto node: graph.get_board()[i]) {
                            node->visited_maze = false;
                            if (node != graph.STNodes().first && node != graph.STNodes().second) {
                                node->reset();
                            }
                        }
                    }
                }
            }
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Exit", ImVec2(200, 100))) {
            window->close();
        }

    }
    ImGui::End();
}

void App::render() {

    
    window->clear(sf::Color::White);
    graph.draw_tiles(window, visualize_visiting);
    if (visualize_visiting) {
        if (visited_count != visited_nodes.size())
            visited_count++;
        for (size_t i = 0; i < visited_count; ++i) {
            for (auto open_neighbor: visited_nodes[i]->neighbors) {
                if (open_neighbor != graph.STNodes().first && open_neighbor != graph.STNodes().second)
                    open_neighbor->set_open();
            }
            if (visited_nodes[i]->color != sf::Color(VISITED_COLOR)) {
                if (visited_nodes[i] != graph.STNodes().first && visited_nodes[i] != graph.STNodes().second)
                    visited_nodes[i]->set_visited();
            }
            visited_nodes[i]->draw_node(window);
            if (i == visited_nodes.size() - 1) {
                visualize_visiting = false;
                visualize_path = true;
                for (size_t i = 0; i < visited_nodes.size(); ++i) {
                    if (visited_nodes[i] != graph.STNodes().first && visited_nodes[i] != graph.STNodes().second)
                        visited_nodes[i]->set_visited();
                }
                visited_nodes.clear();
                visited_count = 0;
            }
        }

    }
    if (visualize_path) {
        if (path_count != path_nodes.size())
            path_count++;
        for (size_t i = 0; i < path_count; ++i) {
            path_nodes[i]->set_path();
            path_nodes[i]->draw_node(window);
            if (i == path_nodes.size() - 1) {
                visualize_path = false;
                finished_visualizing = true;
                path_nodes.clear();
                path_count = 0;
            }
        }
    }

    
    
    if (visualize_maze) {
        if (maze_count != graph.get_total_rows())
            maze_count++;
        for (size_t i = 0; i < maze_count; ++i) {
            for (size_t k = 0; k < maze_path[i].size(); ++k) {
                if (maze_path[i][k]->color != sf::Color(OBSTACLE_COLOR))
                    maze_path[i][k]->set_obstacle();
            }
            if (i == graph.get_total_rows() - 1) {
                visualize_maze = false;
                maze_count = 0;
                for (size_t i = 0; i < graph.get_total_rows(); ++i) {
                    maze_path[i].clear();
                }
            }
        }

    }
    
    graph.draw_grid(window, grid_status);
    ImGui::SFML::Render(*window);
    
    window->display();
}


void App::run() {
    ImGui::SFML::Init(*window);
    while (window->isOpen()) {
        update();
        imgui_update();
        render();
    }
    ImGui::SFML::Shutdown();
    if (!window) {
        App::~App();
    }
}


App::~App() {
    graph.clear_graph();
    delete[] maze_path;
    delete window;
}