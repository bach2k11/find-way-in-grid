
#include "Dijkstra.h"
#include <queue>
//#include <thread>
#include <cmath>


std::vector<sf::Vector2i> dijkstra(sf::RenderWindow& window, sf::Vector2i start, sf::Vector2i end, Grid& grid) {
    
   // std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    std::vector<std::vector<float>> cost(rows, std::vector<float>(cols, std::numeric_limits<float>::max()));
    std::vector<std::vector<sf::Vector2i>> parent(rows, std::vector<sf::Vector2i>(cols, { -1, -1 }));
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    cost[start.y][start.x] = 0;
    //visited[start.y][start.x] = true;

    pq.push({ start,0 });

    std::vector<sf::Vector2i> directions = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1},
       // 4 diagonal directions 
    {0, -1}, {-1, 0}, {1, 0}, {0, 1} // 4 cardinal directions
        
    };
    const float diagonalCost = std::sqrt(2.0f);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        sf::Vector2i pos = current.position;

       /* if (visited[pos.y][pos.x]) continue;
        visited[pos.y][pos.x] = true;*/

            

        if (pos != start && pos != end) {
            grid.setState(pos, State::VISITED);
        }
        window.clear();
        grid.draw(window);
        window.display();
       // std::this_thread::sleep_for(std::chrono::milliseconds(0));
        for (const sf::Vector2i& dir : directions) {
            sf::Vector2i neighbor(pos.x + dir.x, pos.y + dir.y);
           /* if (!grid.isValidCell(neighbor.x, neighbor.y) || visited[neighbor.y][neighbor.x]) {
                continue;
            }*/

            if (grid.isValidCell(neighbor.x, neighbor.y)) {
                float newCost = cost[pos.y][pos.x] + (abs(dir.x) == 1 && abs(dir.y) == 1 ? diagonalCost : 1.0f);

                if (abs(dir.x) == 1 && abs(dir.y) == 1) {
                    if (!grid.canMoveDiagonally(pos.x, pos.y, dir.x, dir.y)) {
                        continue;
                    }
                }

                
               // double newCost = cost[pos.y][pos.x] + std::hypot((dir.x), (dir.y));
                if (newCost < cost[neighbor.y][neighbor.x]) {
                    cost[neighbor.y][neighbor.x] = newCost;
                    pq.push({ neighbor, newCost });
                   // visited[neighbor.y][neighbor.x] = true;

                    parent[neighbor.y][neighbor.x] = pos;
                }
            }
        }

        if (pos==end) {
            std::vector<sf::Vector2i> path = reconstructPath(parent,start,end);
           
            //for (sf::Vector2i& po : path) {
            //    if (po != start && po != end) {  // Check if po is neither start nor end
            //        grid.setState(po, State::PATH);
            //    }
            //}
            return path;
        }

       

        

        
    }

    return {}; // If no path found
}




