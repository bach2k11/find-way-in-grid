#pragma once HEADER_H
#include <SFML/Graphics.hpp>
#include <vector>

const int windowWidth = 1500;
const int windowHeight = 900;
const int cellSize = 25;
const int rows = (windowHeight ) / cellSize;
const int cols = windowWidth / cellSize;

enum class State { EMPTY, START, END, WALL, PATH, VISITED };
struct Node {
    sf::Vector2i position;
    double cost;

    bool operator>(const Node& other) const {
        return cost  > other.cost  ;
    }
};



class Grid {
public:
    Grid(int rows, int cols, int cellSize, int windowHeight);

    State getState(const sf::Vector2i& position) const;
    void setState(const sf::Vector2i& position, State state);

    void draw(sf::RenderWindow& window) const;
    sf::Vector2i getCellPosition(const sf::Vector2i& mousePosition) const;
    bool isValidCell(int x, int y) const;
    bool canMoveDiagonally(int x, int y, int dx, int dy) const;
    int getRows() const;

    int getCols() const;

    bool isTraversable (int x, int y) const;

private:
    int rows;
    int cols;
    int cellSize;
    int windowHeight;
    std::vector<std::vector<State>> grid;
};







std::vector<sf::Vector2i> reconstructPath(const std::vector<std::vector<sf::Vector2i>>& parent, sf::Vector2i start, sf::Vector2i end);


float heuristic(const sf::Vector2i& a, const sf::Vector2i& b);

float calculateTotalDistance(const std::vector<sf::Vector2i> path);

float distance(const sf::Vector2i& a, const sf::Vector2i& b);


std::vector<sf::Vector2i> bresenhamLine(sf::Vector2i start, sf::Vector2i end);