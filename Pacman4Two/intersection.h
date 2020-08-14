#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "sharedEnumerations.h"

class Intersection
{
public:
	std::vector<Intersection*> neighbours;
	std::vector<Direction> directions;
	sf::Vector2i intersectionPosition;
	int type = 0;
};