#pragma once BFS

#include<vector>
#include <SFML/Graphics.hpp>
#include "grid.h"


std::vector<sf::Vector2i> bfs(sf::RenderWindow& window, sf::Vector2i start, sf::Vector2i end,Grid& grid);//BFS
