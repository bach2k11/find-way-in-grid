

#include <SFML/Graphics.hpp>
//#include <queue>
#include <vector>
#include <iostream>
//#include <thread>
#include <chrono>
//#include <limits>
//#include <algorithm>
#include "grid.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "Astar.h"

//
//float distance(const sf::Vector2i& a, const sf::Vector2i& b) {
//    return (a.x != b.x && a.y != b.y) ? std::sqrt(2.0) : 1.0;
//}
//
//float calculateTotalDistance(const std::vector<sf::Vector2i> path) {
//    float totalDistances = 0.0;
//
//    for (int i = 1; i < path.size(); ++i) {
//        totalDistances += distance(path[i - 1], path[i]);
//    }
//
//    return totalDistances;
//}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight -180), "Pathfinding Visualization");
    sf::RenderWindow instructionsWindow(sf::VideoMode(1500, 150), "Instructions");

    sf::Vector2i mainWindowPosition = window.getPosition();
    instructionsWindow.setPosition(sf::Vector2i(mainWindowPosition.x, mainWindowPosition.y - 185));

    Grid grid((windowHeight ) / cellSize, windowWidth / cellSize, cellSize, windowHeight);

    sf::Vector2i start(-1, -1), end(-1, -1);
    bool isStartSet = false, isEndSet = false;
    bool isRightMouseButtonPressed = false;
    sf::Vector2i previousMousePosition(-1, -1);
    std::vector<sf::Vector2i> path;
    float totalDistance;
    

    sf::Font font;
    if (!font.loadFromFile("times-new-roman-14.ttf")) {
        return -1;
    }
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString(
        "instructions:\n"
        "left-click on the square to select Start (green color), End (red color)\n"
        "hold the right mouse button and drag to draw obstacles (black color)\n"
        " 1. run bfs                               "
        " 2. run dijkstra                          "
        " 3. run a* \n"
        " 4. clear the path                         "
        " 5. start over"
    );
    instructions.setCharacterSize(20);
    instructions.setFillColor(sf::Color::Green);
    instructions.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (mousePosition.y > 0) {
                        sf::Vector2i cellPosition = grid.getCellPosition(mousePosition);

                        if (!isStartSet) {
                            start = cellPosition;
                            grid.setState(start, State::START);
                            isStartSet = true;
                        }
                        else if (!isEndSet) {
                            end = cellPosition;
                            grid.setState(end, State::END);
                            isEndSet = true;
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    isRightMouseButtonPressed = true;
                    previousMousePosition = sf::Mouse::getPosition(window);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    isRightMouseButtonPressed = false;
                    previousMousePosition = sf::Vector2i(-1, -1);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    if (isStartSet && isEndSet) {
                        // Bắt đầu đo thời gian
                        auto start_time = std::chrono::high_resolution_clock::now();

                        path = bfs(window, start, end, grid);
                        totalDistance = calculateTotalDistance(path);

                        // Kết thúc đo thời gian
                        auto end_time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<float> duration = end_time - start_time;

                        if (!path.empty()) {
                            std::cout << "Path BFS found with " << path.size() - 1 << " steps.\n";
                            std::cout << "Total distance: " << totalDistance << " units.\n";
                            std::cout << "BFS execution time: " << duration.count() << " seconds.\n";
                            std::cout << "\n";
                        }
                        else {
                            std::cout << "No path found.\n";
                        }

                        for (const sf::Vector2i& cell : path) {
                            if (grid.getState(cell) != State::START && grid.getState(cell) != State::END) {
                                grid.setState(cell, State::PATH);
                            }
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Num2) {
                    if (isStartSet && isEndSet) {
                        // Bắt đầu đo thời gian
                        auto start_time = std::chrono::high_resolution_clock::now();

                        path = dijkstra(window, start, end, grid);
                         totalDistance = calculateTotalDistance(path);

                         // Kết thúc đo thời gian
                         auto end_time = std::chrono::high_resolution_clock::now();
                         std::chrono::duration<float> duration = end_time - start_time;

                        if (!path.empty()) {
                            std::cout << "Path Dijkstra found with " << path.size() - 1 << " steps.\n";
                            std::cout << "Total distance: " << totalDistance << " units.\n";
                            std::cout << "Dijkstra execution time: " << duration.count() << " seconds.\n";
                            std::cout << "\n";

                        }
                        else {
                            std::cout << "No path found.\n";
                        }

                        for (const sf::Vector2i& cell : path) {
                            if (grid.getState(cell) != State::START && grid.getState(cell) != State::END) {
                                grid.setState(cell, State::PATH);
                            }
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Num3) {
                    if (isStartSet && isEndSet) {
                        // Bắt đầu đo thời gian
                        auto start_time = std::chrono::high_resolution_clock::now();

                        path = astar(window, start, end, grid);
                         totalDistance = calculateTotalDistance(path);

                         // Kết thúc đo thời gian
                         auto end_time = std::chrono::high_resolution_clock::now();
                         std::chrono::duration<float> duration = end_time - start_time;
                       
                        if (!path.empty()) {
                            std::cout << "Path A* found with " << path.size() - 1 << " steps.\n";
                            std::cout << "Total distance: " << totalDistance << " units.\n";
                            std::cout << "A* execution time: " << duration.count() << " seconds.\n";
                            std::cout << "\n";

                        }
                        else {
                            std::cout << "No path found.\n";
                        }

                        for (const sf::Vector2i& cell : path) {
                            if (grid.getState(cell) != State::START && grid.getState(cell) != State::END) {
                                grid.setState(cell, State::PATH);
                            }
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Num4) {
                    for (int i = 0; i < grid.getRows(); ++i) {
                        for (int j = 0; j < grid.getCols(); ++j) {
                            if (grid.getState({ j, i }) == State::PATH || grid.getState({ j, i }) == State::VISITED) {
                                grid.setState({ j, i }, State::EMPTY);
                            }
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Num5) {
                    for (int i = 0; i < grid.getRows(); ++i) {
                        for (int j = 0; j < grid.getCols(); ++j) {
                            grid.setState({ j, i }, State::EMPTY);
                        }
                    }
                    isStartSet = false;
                    isEndSet = false;
                }
            }
        }

        while (instructionsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                instructionsWindow.close();
        }


        if (isRightMouseButtonPressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            if (mousePosition.y > 0) {
                sf::Vector2i currentCellPosition = grid.getCellPosition(mousePosition);

                if (currentCellPosition.y >= 0 && currentCellPosition.y < grid.getRows() && currentCellPosition.x >= 0 && currentCellPosition.x < grid.getCols()) {
                    if (previousMousePosition.x != -1 && previousMousePosition.y != -1) {
                        sf::Vector2i previousCellPosition = grid.getCellPosition(previousMousePosition);
                        std::vector<sf::Vector2i> linePoints = bresenhamLine(previousCellPosition, currentCellPosition);

                        for (const sf::Vector2i& point : linePoints) {
                            if (grid.getState(point) == State::EMPTY) {
                                grid.setState(point, State::WALL);
                            }
                        }
                    }
                    previousMousePosition = mousePosition;
                }
            }
        }

        window.clear();
        grid.draw(window);
        window.display();

        instructionsWindow.clear();
        instructionsWindow.draw(instructions);
        instructionsWindow.display();
    }

    return 0;
}

