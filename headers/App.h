#ifndef APP_H
#define APP_H
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <unordered_map>

/**
 * Klasa okna aplikacji
 */

class App
{
public:
    /**
     * funkcja która jest wywoływana w main.cpp
     *
     */
    void run();

    /**
     * Kostruktor klasy App
     * @param total_rows rozmiar siatki
     */
    App(unsigned int total_rows);

    /**
     * destruktor klasy
     */
    ~App();

    /**
     * wskaźnik na okno aplikacji
     * jest obiektem klasy RenderWindow biblioteki SFML
     */
    sf::RenderWindow* window;
    /**
     * definicja zdarzenia
     * jest obiektem klasy Event biblioteki SFML
     */
    sf::Event sfEvent;

    /**
     * obiekt klasy Mouse biblioteki SFML
     * opisuje położenie kursora na w oknie programu
     */
    sf::Mouse mousePos;
    ///zegar dla odświeżania
    sf::Clock dtClock;
    ///rozmiar generowanej siatki
    int size;

private:
    ///wektor w którym są wszystkie odzwiedzone węzły grafu
    std::vector<Node*> visited_nodes;
    ///wektor w którym są węzły najkrótszej ścieżki w siatce
    std::vector<Node*> path_nodes;
    ///wektor w którym są węzły najkrótszej ścieżki w labiryncie
    std::vector<Node*>* maze_path;
    ///liczba odwiedzonych węzłów
    unsigned int visited_count;
    ///liczba węzłów ścieżki
    unsigned int path_count;
    ///liczba odwiedzonych węzłów w labiryncie
    unsigned int maze_count;

    ///obiekt klasy Graph
    Graph graph;

    /// zmienna ustawiaja stan wizualizacji true -false
    bool visualize_visiting;
    /// zmienna ustawiaja stan wizualizacji true -false
    bool visualize_path;
    /// zmienna ustawiaja stan wizualizacji true -false
    bool finished_visualizing;
    /// zmienna ustawiaja stan wizualizacji true -false
    bool visualize_maze;
    /// zmienna ustawia stan okna
    bool app_in_focus;
    /// zmienna ustawia stan siatki czy jest rysowana czy nie
    bool grid_status;

    ///funkcja jest odpowiedzialna za rysowanie wszystkich obiektów w oknie
    void render();
    ///funkcja sprawdza zdażenia które obsługuje biblioteka SFML (naciśnięcie klawiszy, zmiana pozycji kursora itd.)
    void updateSFMLEvents();
    ///funckja odpowiada za wszystkie zdarzenia w GUI, obsługiwane za pomocą biblioteki ImGui
    void imgui_update();
    ///funkcja zmienia algorytm poszukiwania i generacji mapy, obsługuje zdarzenia SFML
    void update();

};

#endif