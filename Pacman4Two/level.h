#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "sharedEnumerations.h"
class Intersection;

class Level : public sf::Drawable
{
public:
	~Level();
	bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);
	void processIntersectionArray();
	void recalculateSum();
	Intersection*  GetIntersectionAt(int x, int y);
	Intersection* GetIntersectionAt(sf::Vector2i location);
	FoodType ConsumeFood(sf::Vector2i location);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture m_tileset;
	sf::VertexArray m_vertices;

	std::array<int, mapWidth*mapHeight> levelArray =
	{
		 7,16,16,16,16,16,16,16,16,16,16,16,16, 4, 5,16,16,16,16,16,16,16,16,16,16,16,16, 6,
		17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,
		17, 0,20,25,25,23, 0,20,25,25,25,23, 0,24,27, 0,20,25,25,25,23, 0,20,25,25,23, 0,19,
		17, 0,24, 0, 0,27, 0,24, 0, 0, 0,27, 0,24,27, 0,24, 0, 0, 0,27, 0,24, 0, 0,27, 0,19,
		17, 0,21,26,26,22, 0,21,26,26,26,22, 0,21,22, 0,21,26,26,26,22, 0,21,26,26,22, 0,19,
		17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,
		17, 0,20,25,25,23, 0,20,23, 0,20,25,25,25,25,25,25,23, 0,20,23, 0,20,25,25,23, 0,19,
		17, 0,21,26,26,22, 0,24,27, 0,21,26,26,23,20,26,26,22, 0,24,27, 0,21,26,26,22, 0,19,
		17, 0, 0, 0, 0, 0, 0,24,27, 0, 0, 0, 0,24,27, 0, 0, 0, 0,24,27, 0, 0, 0, 0, 0, 0,19,
		28,18,18,18,18,23, 0,24,21,25,25,23, 0,24,27, 0,20,25,25,22,27, 0,20,18,18,18,18,31,
		 0, 0, 0, 0, 0,17, 0,24,20,26,26,22, 0,21,22, 0,21,26,26,23,27, 0,19, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0,17, 0,24,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,27, 0,19, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0,17, 0,24,27, 0,10,18,13,15,15,12,18,11, 0,24,27, 0,19, 0, 0, 0, 0, 0,
		16,16,16,16,16,22, 0,21,22, 0,19, 0, 0, 0, 0, 0, 0,17, 0,21,22, 0,21,16,16,16,16,16,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19, 0, 0, 0, 0, 0, 0,17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		18,18,18,18,18,23, 0,20,23, 0,19, 0, 0, 0, 0, 0, 0,17, 0,20,23, 0,20,18,18,18,18,18,
		 0, 0, 0, 0, 0,17, 0,24,27, 0, 8,16,16,16,16,16,16, 9, 0,24,27, 0,19, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0,17, 0,24,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,27, 0,19, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0,17, 0,24,27, 0,20,25,25,25,25,25,25,23, 0,24,27, 0,19, 0, 0, 0, 0, 0,
		 7,16,16,16,16,22, 0,21,22, 0,21,26,26,23,20,26,26,22, 0,21,22, 0,21,16,16,16,16, 6,
		17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,
		17, 0,20,25,25,23, 0,20,25,25,25,23, 0,24,27, 0,20,25,25,25,23, 0,20,25,25,23, 0,19,
		17, 0,21,26,23,27, 0,21,26,26,26,22, 0,21,22, 0,21,26,26,26,22, 0,24,20,26,22, 0,19,
		17, 0, 0, 0,24,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,27, 0, 0, 0,19,
		32,25,23, 0,24,27, 0,20,23, 0,20,25,25,25,25,25,25,23, 0,20,23, 0,24,27, 0,20,25,34,
		33,26,22, 0,21,22, 0,24,27, 0,21,26,26,23,20,26,26,22, 0,24,27, 0,21,22, 0,21,26,35,
		17, 0, 0, 0, 0, 0, 0,24,27, 0, 0, 0, 0,24,27, 0, 0, 0, 0,24,27, 0, 0, 0, 0, 0, 0,19,
		17, 0,20,25,25,25,25,22,21,25,25,23, 0,24,27, 0,20,25,25,22,21,25,25,25,25,23, 0,19,
		17, 0,21,26,26,26,26,26,26,26,26,22, 0,21,22, 0,21,26,26,26,26,26,26,26,26,22, 0,19,
		17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,
		28,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,31,
	};
	/*
	INTERSECTION COMMENT
	bitmask like int value that will allow to generate intersections
	1 - means I can go UP    from that place
	2 - means I can go DOWN
 	4 - means I can go LEFT
	8 - means I can go RIGHT 
	16 - means that only player can use that intersection
	32 - means that only ghost that returns to base after being eaten can use it
	e.g. 5  - means we can go up and left
		 15 - means we can go in every direction
	*/
	std::array<int, mapWidth*mapHeight> intersectionsArray =
	{
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0,10, 0, 0, 0, 0,14, 0, 0, 0, 0, 0, 6, 0, 0,10, 0, 0, 0, 0, 0,14, 0, 0, 0, 0, 6, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0,11, 0, 0, 0, 0,15, 0, 0,14, 0, 0,13, 0, 0,13, 0, 0,14, 0, 0,15, 0, 0, 0, 0, 7, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 9, 0, 0, 0, 0, 7, 0, 0, 9, 0, 0, 6, 0, 0,10, 0, 0, 5, 0, 0,11, 0, 0, 0, 0, 5, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0,13,14,12,13, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,36, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		28, 0, 0, 0, 0, 0,15, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,15, 0, 0, 0, 0, 0,28,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0,10, 0, 0, 0, 0,15, 0, 0,13, 0, 0, 6, 0, 0,10, 0, 0,13, 0, 0,15, 0, 0, 0, 0, 6, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 9, 0, 6, 0, 0,11, 0, 0,14, 0, 0,13, 0, 0,13, 0, 0,14, 0, 0, 7, 0, 0,10, 0, 5, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0,10, 0,13, 0, 0, 5, 0, 0, 9, 0, 0, 6, 0, 0,10, 0, 0, 5, 0, 0, 9, 0, 0,13, 0, 6, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	std::array<int, mapWidth*mapHeight> foodArray =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
		 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
		 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 0,
		 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
		 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
		 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0,
		 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0,
		 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
		 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
		 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
		 0, 2, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 2, 0,
		 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0,
		 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0,
		 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0,
		 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
		 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
		 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	Intersection* intersections[mapWidth*mapHeight];

	std::array<int, mapWidth*mapHeight> sumArray;

};