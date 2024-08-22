#include "grid.h"
#include <queue>
//#include <thread>
//#include <limits>
//#include <algorithm>


	


float heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}




    Grid::Grid(int rows, int cols, int cellSize, int windowHeight)
        : rows(rows), cols(cols), cellSize(cellSize), windowHeight(windowHeight),
        grid(rows, std::vector<State>(cols, State::EMPTY)) {}

    State Grid::getState(const sf::Vector2i& position) const {
        return grid[position.y][position.x];
    }

    void Grid::setState(const sf::Vector2i& position, State state) {
        grid[position.y][position.x] = state;
    }

    void Grid::draw(sf::RenderWindow& window) const {
        for (int i = 0; i < cols * cellSize; i += cellSize) {
            for (int j = 0; j < rows * cellSize +0 ; j += cellSize) {
                sf::RectangleShape rectangle(sf::Vector2f(cellSize, cellSize));
                rectangle.setPosition(i, j);
                State cellState = grid[(j - 0) / cellSize][i / cellSize];

                if (cellState == State::START) {
                    rectangle.setFillColor(sf::Color::Green);
                }
                else if (cellState == State::END) {
                    rectangle.setFillColor(sf::Color::Red);
                }
                else if (cellState == State::WALL) {
                    rectangle.setFillColor(sf::Color::Black);
                }
                else if (cellState == State::PATH) {
                    rectangle.setFillColor(sf::Color::Blue);
                }
                else if (cellState == State::VISITED) {
                    rectangle.setFillColor(sf::Color(192, 192, 192));
                }
                else {
                    rectangle.setFillColor(sf::Color::White);
                }

                rectangle.setOutlineThickness(1);
                rectangle.setOutlineColor(sf::Color::Black);
                window.draw(rectangle);
            }
        }
    }

    sf::Vector2i Grid::getCellPosition(const sf::Vector2i& mousePosition) const {
        return sf::Vector2i(mousePosition.x / cellSize, (mousePosition.y - 0) / cellSize);
    }

    bool Grid::isValidCell(int x, int y) const {
        return x >= 0 && x < cols && y >= 0 && y < rows && grid[y][x] != State::WALL;
    }

    bool Grid::canMoveDiagonally(int x, int y, int dx, int dy) const {
        return  (isValidCell(x + dx, y) || isValidCell(x, y + dy));
    }


    int Grid::getRows() const { return rows; }
    int Grid::getCols() const { return cols; }
    bool Grid::isTraversable(int x, int y) const {
        return grid[y][x] != State::WALL;
    }

    std::vector<sf::Vector2i> reconstructPath(const std::vector<std::vector<sf::Vector2i>>& parent, sf::Vector2i start, sf::Vector2i end) {
        std::vector<sf::Vector2i> path;
        sf::Vector2i current = end;


       
        while (current != start) {
            path.push_back(current);
            current = parent[current.y][current.x];
        }

        path.push_back(start);
      
        std::reverse(path.begin(), path.end());

        return path;
    }

    // Hàm sử dụng thuật toán Bresenham's Line để tính toán các điểm trên đường thẳng
    std::vector<sf::Vector2i> bresenhamLine(sf::Vector2i start, sf::Vector2i end) {
        std::vector<sf::Vector2i> points;
        int dx = std::abs(end.x - start.x);
        int dy = std::abs(end.y - start.y);
        int sx = start.x < end.x ? 1 : -1;
        int sy = start.y < end.y ? 1 : -1;
        int err = dx - dy;

        while (true) {
            points.push_back(start);
            if (start == end) break;
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                start.x += sx;
            }
            if (e2 < dx) {
                err += dx;
                start.y += sy;
            }
        }

        return points;
    }

    
    //float cost(const sf::Vector2i& a, sf::Vector2i& b) {
    //    return std::sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    //}

    float distance(const sf::Vector2i& a, const sf::Vector2i& b) {
        return (a.x != b.x && a.y != b.y) ? std::sqrt(2.0) : 1.0;
    }

    float calculateTotalDistance(const std::vector<sf::Vector2i> path) {
        float totalDistances = 0.0;

        for (int i = 1; i < path.size(); ++i) {
            totalDistances += distance(path[i - 1], path[i]);
        }

        return totalDistances;
    }
