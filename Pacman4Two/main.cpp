#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "level.h"
#include <vector>
#include "intersection.h"
#include <math.h>


int main()
{
	Level level;
	level.load("Textures/mapspritesheet.png", sf::Vector2u(8, 8), 28, 31);
	
	sf::RenderWindow window(sf::VideoMode(448, 496), "Pacman!");
	window.setFramerateLimit(144);
	Player player(sf::Vector2f(16.0f, 16.0f),90.0f);
	player.currentIntersection = level.GetIntersectionAt(player.playerPositionToMapIndex());
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
		
		level.ConsumeFood(player.playerPositionToMapIndex());

		
		window.clear();
		window.draw(level);
		window.draw(player);
		window.display();
		level.load("Textures/mapspritesheet.png", sf::Vector2u(8, 8), 28, 31);

	}
	return 0;
}