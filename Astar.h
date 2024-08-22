#pragma once ASTAR

#include<vector>
#include <SFML/Graphics.hpp>
#include "grid.h"


std::vector<sf::Vector2i> astar(sf::RenderWindow& window, sf::Vector2i start, sf::Vector2i end, Grid& grid);

