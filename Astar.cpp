

#include "Astar.h"
#include <queue>
//#include <thread>
//#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>

const int MAX = 10000; 
std::vector<std::vector<float>> fScore(rows, std::vector<float>(cols, MAX));

struct GreaterVector2i {
    bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const {
        return fScore[a.y][a.x] > fScore[b.y][b.x];
    }
};

std::vector<sf::Vector2i> astar(sf::RenderWindow& window, sf::Vector2i start, sf::Vector2i end, Grid& grid) {
    int rows = grid.getRows(); // Assuming grid provides getRows method
    int cols = grid.getCols(); // Assuming grid provides getCols method

    std::vector<std::vector<float>> gScore(rows, std::vector<float>(cols, MAX));
 // std::vector<std::vector<float>> fScore(rows, std::vector<float>(cols, MAX));
    std::vector<std::vector<sf::Vector2i>> parent(rows, std::vector<sf::Vector2i>(cols, { -1, -1 }));

    std::priority_queue<sf::Vector2i, std::vector<sf::Vector2i>, GreaterVector2i> pq;

    pq.push(start);
    gScore[start.y][start.x] = 0;
    fScore[start.y][start.x] = heuristic(start, end);

    std::vector<sf::Vector2i> directions = {
        {0, 1}, {1, 0}, {1, -1}, {1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {-1, 1}
    };

    while (!pq.empty()) {
        sf::Vector2i current = pq.top();
        pq.pop();

        if (current == end) {
            std::vector<sf::Vector2i> path = reconstructPath(parent, start, end);
            return path;
        }

        if (current != start && current != end) {
            grid.setState(current, State::VISITED);
        }

        window.clear();
        grid.draw(window);
        window.display();
       // std::this_thread::sleep_for(std::chrono::milliseconds(10));

        for (const sf::Vector2i& dir : directions) {
            sf::Vector2i neighbor(current.x + dir.x, current.y + dir.y);

            if (grid.isValidCell(neighbor.x, neighbor.y) ) {
                if (abs(dir.x) == 1 && abs(dir.y) == 1) {
                    if (!grid.canMoveDiagonally(current.x,current.y, dir.x, dir.y)) {
                        continue;
                    }
                }
               // int tentative_gScore = gScore[current.y][current.x] + 1;

              float moveCost = (abs(dir.x) == 1 && abs(dir.y) == 1) ? std::sqrt(2.0) : 1.0;
               // float moveCost = distance(current, neighbor);
                float tentative_gScore = gScore[current.y][current.x] + moveCost;

                if (tentative_gScore < gScore[neighbor.y][neighbor.x]) {
                    parent[neighbor.y][neighbor.x] = current;
                    gScore[neighbor.y][neighbor.x] = tentative_gScore;
                    fScore[neighbor.y][neighbor.x] = tentative_gScore + heuristic(neighbor, end);

                    pq.push(neighbor);
                }
            }
        }
    }
  //  reconstructPath(parent, start, end);

    return {  };
}

