#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
#include "collisionManager.h"
#include "collider.h"
#include <vector>
#include "intersection.h"
#include <math.h>
const int mapWidth = 28;
const int mapHeight = 31;

Intersection* GetIntersectionAt(Intersection** intersections, int x, int y);
Intersection* GetIntersectionAt(Intersection** intersections, sf::Vector2i location);


int main()
{

	const int level[] =
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
	I don't want to hardcode intersection becouse that's a lot for every map(we got one but what if...)
	So I will create bitmask like int value that will allow to generate intersections
	1 - means i can go UP    from that place
	2 - means i can go DOWN
 	4 - means I can go LEFT
	8 - means I can go RIGHT 
	e.g. 5  - means we can go up and left
		 15 - means we can go i every direction
	*/
	const int intersectionsArray[] =
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
		 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0,13,12,12,13, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 1, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0,15, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,15, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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
	Intersection* intersections[mapWidth*mapHeight];
	for (size_t i = 0; i < mapWidth*mapHeight; i++)
	{
		if (intersectionsArray[i])
		{
			Intersection* inter = new Intersection();
			intersections[i] = inter;
			inter->type = intersectionsArray[i];
			inter->intersectionPosition = sf::Vector2i(i % mapWidth, i / mapWidth);
		}
		else
		{
			intersections[i] = nullptr;
		}
	}
	for (size_t i = 0; i < mapWidth*mapHeight; i++)
	{
		if (intersections[i]!=nullptr)
		{
			int type = intersections[i]->type;
			int column = i % mapWidth;
			int row = i / mapWidth;


			if ((type&1)==1)
			{
				for (size_t r = row - 1; r > 0; r--)
				{
					if (intersections[r*mapWidth+column]!=nullptr)
					{
						intersections[i]->neighbours.push_back(intersections[r*mapWidth + column]);
						intersections[i]->directions.push_back(sf::Vector2f(0.0f, -1.0f));
						break;
					}
				}
			}
			if ((type & 2) == 2)
			{
				for (size_t r = row + 1; r < mapHeight; r++)
				{
					if (intersections[r*mapWidth + column] != nullptr)
					{
						intersections[i]->neighbours.push_back(intersections[r*mapWidth + column]);
						intersections[i]->directions.push_back(sf::Vector2f(0.0f, 1.0f));
						break;
					}
				}
			}
			if ((type & 4) == 4)
			{
				for (size_t c = column - 1; c > 0; c--)
				{
					if (intersections[row*mapWidth + c] != nullptr)
					{
						intersections[i]->neighbours.push_back(intersections[row*mapWidth + c]);
						intersections[i]->directions.push_back(sf::Vector2f(-1.0f, 0.0f));
						break;
					}
				}
			}
			if ((type & 8) == 8)
			{
				for (size_t c = column + 1; c < mapWidth; c++)
				{
					if (intersections[row*mapWidth + c] != nullptr)
					{
						intersections[i]->neighbours.push_back(intersections[row*mapWidth + c]);
						intersections[i]->directions.push_back(sf::Vector2f(1.0f, 0.0f));
						break;
					}
				}
			}
		}
	}

	Map map;
	map.load("Textures/mapspritesheet.png", sf::Vector2u(8, 8), level, 28, 31);
	
	sf::RenderWindow window(sf::VideoMode(448, 496), "Pacman!");
	window.setFramerateLimit(144);
	Player player(10.0f, sf::Vector2f(10.0f, 10.0f),30.0f);
	player.currentIntersection = GetIntersectionAt(intersections, player.playerPositionToMapIndex());
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		//std::cout << deltaTime.asMilliseconds() << std::endl;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				player.processEvents(event);
			}
		}
		player.update(deltaTime);
		CollisionManager::GetCollisionManager().Tick();
		window.clear();
		window.draw(map);
		window.draw(player);
		window.display();
	}
	return 0;
}


Intersection* GetIntersectionAt(Intersection** intersections, int x, int y)
{
	if (x>mapWidth||y>mapHeight)
		return nullptr;
	int index = x + y * mapWidth;
	return intersections[index];
}

Intersection* GetIntersectionAt(Intersection** intersections, sf::Vector2i location)
{
	return GetIntersectionAt(intersections, location.x, location.y);
}