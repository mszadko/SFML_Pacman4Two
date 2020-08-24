#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "player.h"
#include "ghost.h"
#include "level.h"
#include "intersection.h"
#include "gameManager.h"


int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(448, 496), "Pacman!");
	window.setVerticalSyncEnabled(true);

	Level level;
	
	Player playerOne(sf::Vector2f(14*16.0f, 17*16.0f), level.GetIntersectionAt(14, 17),PlayerNumer::FIRST, 90.0f);
	Player playerTwo(sf::Vector2f(13*16.0f, 17*16.0f), level.GetIntersectionAt(13, 17),PlayerNumer::SECOND, 90.0f);

	std::array<Ghost*, 4> ghosts{{ nullptr }};
	Ghost ghosts0(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), RED, 80.0f);
	Ghost ghosts1(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), PINK, 80.0f);
	Ghost ghosts2(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), BLUE, 80.0f);
	Ghost ghosts3(sf::Vector2f(11 * 16.0f, 13 * 16.0f), level.GetIntersectionAt(11, 13), ORANGE, 80.0f);
	ghosts[0]=&ghosts0;
	ghosts[1]=&ghosts1;
	ghosts[2]=&ghosts2;
	ghosts[3]=&ghosts3;
	
	GameManager::GetGameManager().window = &window;
	GameManager::GetGameManager().level = &level;
	GameManager::GetGameManager().players.push_back(&playerOne);
	GameManager::GetGameManager().players.push_back(&playerTwo);
	GameManager::GetGameManager().ghosts=ghosts;
	GameManager::GetGameManager().SetupNetworking(argc,argv);
	
	ghosts[0]->players=GameManager::GetGameManager().players;
	ghosts[1]->players=GameManager::GetGameManager().players;
	ghosts[2]->players=GameManager::GetGameManager().players;
	ghosts[3]->players=GameManager::GetGameManager().players;


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
				if (GameManager::GetGameManager().IsClient())
				{
					GameManager::GetGameManager().SendKeyPressToServer(event);
					if(GameManager::GetGameManager().GetConnectionType() == ConnectionType::CLIENTONE)
					{
						playerOne.processEvents(event);
					}
					else
					{
						playerTwo.processEvents(event);
					}
				}
				
				if (GameManager::GetGameManager().IsStandalone())
				{
					playerOne.processEvents(event);
					playerTwo.processEvents(event);
				}
			}
		}
		
		if (GameManager::GetGameManager().GetConnectionType() == ConnectionType::SERVER)
		{
			GameManager::GetGameManager().ProcessServerPacketListening();	
		}
		else if(GameManager::GetGameManager().IsClient())
		{
			GameManager::GetGameManager().ProcessClientPacketListening();
		}
		
		GameManager::GetGameManager().update(deltaTime);
		
		window.clear();
		GameManager::GetGameManager().draw();
		window.display();

	}
	
	
	return 0;
}
