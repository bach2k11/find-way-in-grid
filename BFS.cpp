#include"BFS.h"
#include<queue>

std::vector<sf::Vector2i> bfs(sf::RenderWindow& window, sf::Vector2i start, sf::Vector2i end, Grid& grid) {
   

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<sf::Vector2i>> parent(rows, std::vector<sf::Vector2i>(cols, { -1, -1 }));
    std::queue<sf::Vector2i> q;
    q.push(start);
    visited[start.y][start.x] = true;

    std::vector<sf::Vector2i> directions = {
          {0, -1}, {-1, 0}, {1, 0}, {0, 1}, 
        {-1, -1}, {1, -1}, {-1, 1}, {1, 1} 
    };

    while (!q.empty()) {
        sf::Vector2i current = q.front();
        q.pop();
        if (current != start && current != end) {
            grid.setState(current, State::VISITED);
        }

       
        window.clear();

        grid.draw(window);

        window.display();

        for (const sf::Vector2i dir : directions) {
            sf::Vector2i neighbor(current.x + dir.x, current.y + dir.y);

            if (grid.isValidCell(neighbor.x, neighbor.y) && !visited[neighbor.y][neighbor.x]) {

                if (abs(dir.x) == 1 && abs(dir.y) == 1) {
                    if (!grid.canMoveDiagonally(current.x, current.y, dir.x, dir.y)) {
                        continue;
                    }
                }

                q.push(neighbor);
                visited[neighbor.y][neighbor.x] = true;
                parent[neighbor.y][neighbor.x] = current;
            }
        }

        if (current == end) {
           
           return reconstructPath(parent, start, end);
        }

    }
    return {};
}