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
	GameManager::GetGameManager().level = &level;
	sf::RenderWindow window(sf::VideoMode(448, 496), "Pacman!");
	window.setVerticalSyncEnabled(true);

	Player player(sf::Vector2f(16.0f, 16.0f), level.GetIntersectionAt(1, 1), 90.0f);
	GameManager::GetGameManager().players.push_back(&player);

	std::array<Ghost*, 4> ghosts{ nullptr };
	ghosts[0] = new Ghost(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), RED, 80.0f);
	ghosts[0]->player = &player;
	GameManager::GetGameManager().ghosts[0] = ghosts[0];

	ghosts[1] = new Ghost(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), PINK, 80.0f);
	ghosts[1]->player = &player;
	GameManager::GetGameManager().ghosts[1] = ghosts[1];

	ghosts[2] = new Ghost(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), BLUE, 80.0f);
	ghosts[2]->player = &player;
	GameManager::GetGameManager().ghosts[2] = ghosts[2];

	ghosts[3] = new Ghost(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), ORANGE, 80.0f);
	ghosts[3]->player = &player;
	GameManager::GetGameManager().ghosts[3] = ghosts[3];

	GameManager::GetGameManager().window = &window;

	sf::Clock tickClock;

	while (window.isOpen())
	{
		sf::Time deltaTime = tickClock.restart();

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

		GameManager::GetGameManager().update(deltaTime);
		window.clear();
		GameManager::GetGameManager().draw();
		window.display();

	}
	return 0;
}