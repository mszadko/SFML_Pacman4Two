#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Intersection
{
public:
	std::vector<Intersection*> neighbours;
	std::vector<sf::Vector2f> directions;
	sf::Vector2i intersectionPosition;
	int type = 0;
};