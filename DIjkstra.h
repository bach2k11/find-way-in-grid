#pragma once DIJKSTRA

#include<vector>
#include <SFML/Graphics.hpp>
#include "grid.h"

std::vector<sf::Vector2i> dijkstra(sf::RenderWindow& window, sf::Vector2i start, sf::Vector2i end, Grid& grid);

