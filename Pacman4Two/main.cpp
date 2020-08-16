#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "ghost.h"
#include "level.h"
#include <vector>
#include "intersection.h"
#include <math.h>
#include "gameManager.h"



int main()
{
	Level level;
	level.load("Textures/mapspritesheet.png", sf::Vector2u(8, 8), 28, 31);
	GameManager::GetGameManager().level = &level;
	sf::RenderWindow window(sf::VideoMode(448, 496), "Pacman!");
	window.setFramerateLimit(144);
	//Player player(sf::Vector2f(13*16.0f,11*16.0f),level.GetIntersectionAt(13,11),90.0f);
	Player player(sf::Vector2f(16.0f,16.0f), level.GetIntersectionAt(1, 1), 90.0f);
	GameManager::GetGameManager().player = &player;
	std::array<Ghost*, 4> ghosts{ nullptr };

	sf::Clock tickClock;
	sf::Clock gameClock;
	sf::Time gameTime = gameClock.restart();
	bool red, pink, blue, orange;
	red = pink = blue = orange = false;
	while (window.isOpen())
	{
		sf::Time deltaTime = tickClock.restart();
		gameTime = gameClock.getElapsedTime();
		if (!red&&gameTime.asSeconds()>=0)
		{
			red = true;
			ghosts[0] = new Ghost(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), RED, 80.0f);
			ghosts[0]->player = &player;
			GameManager::GetGameManager().ghosts[0] = ghosts[0];
		}
		if (!pink&&gameTime.asSeconds() >= 2)
		{
			pink = true;
			ghosts[1] = new Ghost(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), PINK, 80.0f);
			ghosts[1]->player = &player;
			GameManager::GetGameManager().ghosts[1] = ghosts[1];
		}
		if (!blue&&gameTime.asSeconds() >= 4)
		{
			blue = true;
			ghosts[2] = new Ghost(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), BLUE, 80.0f);
			ghosts[2]->player = &player;
			GameManager::GetGameManager().ghosts[2] = ghosts[2];
		}
		if (!orange&&gameTime.asSeconds() >= 6)
		{
			orange = true;
			ghosts[3] = new Ghost(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), ORANGE, 80.0f);
			ghosts[3]->player = &player;
			GameManager::GetGameManager().ghosts[3] = ghosts[3];
		}

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
		
		if (level.ConsumeFood(player.PositionToMapCoord())==POWERUP)
		{
			GameManager::GetGameManager().FrightenAllGhosts();
		}
		

		for (size_t i = 0; i < ghosts.size(); i++)
		{
			if (ghosts[i])
			{
				ghosts[i]->update(deltaTime);
			}
		}
		GameManager::GetGameManager().update(deltaTime);
		window.clear();
		window.draw(level);
		window.draw(player);
		for (size_t i = 0; i < ghosts.size(); i++)
		{
			if (ghosts[i])
			{
				window.draw(*ghosts[i]);
			}
		}
		window.display();
		level.load("Textures/mapspritesheet.png", sf::Vector2u(8, 8), 28, 31);

	}
	return 0;
}