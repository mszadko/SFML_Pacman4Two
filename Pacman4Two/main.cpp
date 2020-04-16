#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
#include "collisionManager.h"
#include "collider.h";
#include <vector>;



int main()
{

	const int level[] =
	{
		 7,16,16,16,16,16,16,16,16,16,16,16,16, 4, 5,16,16,16,16,16,16,16,16,16,16,16,16, 6,
		17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,
		17, 0,20,25,25,23, 0,20,25,25,25,23, 0,24,27, 0,20,25,25,23, 0,20,25,25,25,23, 0,19,
		17, 0,24, 1, 1,27, 0,24, 1, 1, 1,27, 0,24,27, 0,24, 1, 1,27, 0,24, 1, 1, 1,27, 0,19,
		17, 0,21,26,26,22, 0,21,26,26,26,22, 0,21,22, 0,21,26,26,22, 0,21,26,26,26,22, 0,19,
		17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,
		17, 0,20,25,25,23, 0,20,23, 0,20,25,25,25,25,25,25,23, 0,20,23, 0,20,25,25,23, 0,19,
		17, 0,21,26,26,22, 0,24,27, 0,21,26,26,23,20,26,26,22, 0,24,27, 0,21,26,26,22, 0,19,
		17, 0, 0, 0, 0, 0, 0,24,27, 0, 0, 0, 0,24,27, 0, 0, 0, 0,24,27, 0, 0, 0, 0, 0, 0,19,
		28,18,18,18,18,23, 0,24,21,25,25,23, 0,24,27, 0,20,25,25,22,27, 0,20,18,18,18,18,31,
		 1, 1, 1, 1, 1,17, 0,24,20,26,26,22, 0,21,22, 0,21,26,26,23,27, 0,19, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1,17, 0,24,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,27, 0,19, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1,17, 0,24,27, 0,10,18,13,15,15,12,18,11, 0,24,27, 0,19, 1, 1, 1, 1, 1,
		16,16,16,16,16,22, 0,21,22, 0,19, 1, 1, 1, 1, 1, 1,17, 0,21,22, 0,21,16,16,16,16,16,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19, 1, 1, 1, 1, 1, 1,17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		18,18,18,18,18,23, 0,20,23, 0,19, 1, 1, 1, 1, 1, 1,17, 0,20,23, 0,20,18,18,18,18,18,
		 1, 1, 1, 1, 1,17, 0,24,27, 0, 8,16,16,16,16,16,16, 9, 0,24,27, 0,19, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1,17, 0,24,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,27, 0,19, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1,17, 0,24,27, 0,20,25,25,25,25,25,25,23, 0,24,27, 0,19, 1, 1, 1, 1, 1,
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
	const int intersections[] =
	{
		 7,16,16,16,16,16,16,16,16,16,16,16,16, 4, 5,16,16,16,16,16,16,16,16,16,16,16,16, 6,
		17,36, 0, 0, 0, 0,38, 0, 0, 0, 0, 0,38,24,27,36, 0, 0, 0, 0, 0,37, 0, 0, 0, 0,38,19,
		17, 0,20,25,25,23, 0,20,25,25,25,23, 0,24,27, 0,20,25,25,25,23, 0,20,25,25,23, 0,19,
		17, 0,24, 1, 1,27, 0,24, 1, 1, 1,27, 0,24,27, 0,24, 1, 1, 1,27, 0,24, 1, 1,27, 0,19,
		17, 0,21,26,26,22, 0,21,26,26,26,22, 0,21,22, 0,21,26,26,26,22, 0,21,26,26,22, 0,19,
		17,39, 0, 0, 0, 0,40, 0, 0,37, 0, 0,43, 0, 0,43, 0, 0,37, 0, 0,40, 0, 0, 0, 0,41,19,
		17, 0,20,25,25,23, 0,20,23, 0,20,25,25,25,25,25,25,23, 0,20,23, 0,20,25,25,23, 0,19,
		17, 0,21,26,26,22, 0,24,27, 0,21,26,26,23,20,26,26,22, 0,24,27, 0,21,26,26,22, 0,19,
		17,42, 0, 0, 0, 0,41,24,27,42, 0, 0,38,24,27,36, 0, 0,44,24,27,39, 0, 0, 0, 0,44,19,
		28,18,18,18,18,23, 0,24,21,25,25,23, 0,24,27, 0,20,25,25,22,27, 0,20,18,18,18,18,31,
		 1, 1, 1, 1, 1,17, 0,24,20,26,26,22, 0,21,22, 0,21,26,26,23,27, 0,19, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1,17, 0,24,27,36, 0, 0,43,47,47,43, 0, 0,38,24,27, 0,19, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1,17, 0,24,27, 0,10,18,13,15,15,12,18,11, 0,24,27, 0,19, 1, 1, 1, 1, 1,
		16,16,16,16,16,22, 0,21,22, 0,19,48, 1,45,45, 1,46,17, 0,21,22, 0,21,16,16,16,16,16,
		 0, 0, 0, 0, 0, 0,40, 0, 0,41,19, 1, 1, 1, 1, 1, 1,17,39, 0, 0,40, 0, 0, 0, 0, 0, 0,
		18,18,18,18,18,23, 0,20,23, 0,19,45, 1, 1, 1, 1,45,17, 0,20,23, 0,20,18,18,18,18,18,
		 1, 1, 1, 1, 1,17, 0,24,27, 0, 8,16,16,16,16,16,16, 9, 0,24,27, 0,19, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1,17, 0,24,27,39, 0, 0, 0, 0, 0, 0, 0, 0,41,24,27, 0,19, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1,17, 0,24,27, 0,20,25,25,25,25,25,25,23, 0,24,27, 0,19, 1, 1, 1, 1, 1,
		 7,16,16,16,16,22, 0,21,22, 0,21,26,26,23,20,26,26,22, 0,21,22, 0,21,16,16,16,16, 6,
		17,36, 0, 0, 0, 0,40, 0, 0,43, 0, 0,38,24,27,36, 0, 0,43, 0, 0,40, 0, 0, 0, 0,38,19,
		17, 0,20,25,25,23, 0,20,25,25,25,23, 0,24,27, 0,20,25,25,25,23, 0,20,25,25,23, 0,19,
		17, 0,21,26,23,27, 0,21,26,26,26,22, 0,21,22, 0,21,26,26,26,22, 0,24,20,26,22, 0,19,
		17,42, 0,38,24,27,39, 0, 0,37, 0, 0,43, 0, 0,43, 0, 0,37, 0, 0,41,24,27,36, 0,44,19,
		32,25,23, 0,24,27, 0,20,23, 0,20,25,25,25,25,25,25,23, 0,20,23, 0,24,27, 0,20,25,34,
		33,26,22, 0,21,22, 0,24,27, 0,21,26,26,23,20,26,26,22, 0,24,27, 0,21,22, 0,21,26,35,
		17,36, 0,43, 0, 0,44,24,27,42, 0, 0,44,24,27,36, 0, 0,44,24,27,42, 0, 0,43, 0,38,19,
		17, 0,20,25,25,25,25,22,21,25,25,23, 0,24,27, 0,20,25,25,22,21,25,25,25,25,23, 0,19,
		17, 0,21,26,26,26,26,26,26,26,26,22, 0,21,22, 0,21,26,26,26,26,26,26,26,26,22, 0,19,
		17,42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43, 0, 0,43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,44,19,
		28,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,31,
	};

	Map map;
	map.load("Textures/mapspritesheet.png", sf::Vector2u(8, 8), intersections, 28, 31);
	
	sf::RenderWindow window(sf::VideoMode(448, 496), "Pacman!");
	window.setFramerateLimit(144);
	Player player(15.0f, sf::Vector2f(348.0f, 150.0f),30.0f);
	Player player1(15.0f, sf::Vector2f(248.0f, 150.0f),0.0f);
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		std::cout << deltaTime.asMilliseconds() << std::endl;
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
		player1.update(deltaTime);
		CollisionManager::GetCollisionManager().Tick();
		window.clear();
		window.draw(map);
		window.draw(player);
		window.draw(player1);
		window.display();
	}
	return 0;
}