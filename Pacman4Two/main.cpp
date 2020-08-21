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



enum ConnectionType
{
	NONE,
	SERVER,
	CLIENT
};

const unsigned short clientOneListenSocketPort = 54001;
const unsigned short serverListenSocketPort = 54000;


int main(int argc, char *argv[])
{
	ConnectionType connectionType;
	sf::UdpSocket clientListenSocket;
	clientListenSocket.setBlocking(false);
	sf::UdpSocket serverListenSocket;
	serverListenSocket.setBlocking(false);
	
	for (int i = 0; i < argc; i++)
	{
		
		if (argv[i]==std::string("client"))
		{
			connectionType=ConnectionType::CLIENT;
			std::cout<<"Connected as a client\n";
			clientListenSocket.bind(clientOneListenSocketPort);
			break;
		}
		if (argv[i]==std::string("server"))
		{
			connectionType=ConnectionType::SERVER;
			std::cout<<"Connected as a server\n";
			serverListenSocket.bind(serverListenSocketPort);
			break;
		}
	}
	
	
	Level level;
	GameManager::GetGameManager().level = &level;
	sf::RenderWindow window(sf::VideoMode(448, 496), "Pacman!");
	window.setVerticalSyncEnabled(true);

	Player player(sf::Vector2f(13*16.0f, 17*16.0f), level.GetIntersectionAt(13, 17), 90.0f);
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
				if (ConnectionType::CLIENT==connectionType)
				{
					sf::Packet packet;
					sf::Int32 keyToSend= event.key.code;
					packet<<keyToSend;
					sf::IpAddress recipient = sf::IpAddress::Broadcast;
					clientListenSocket.send(packet, recipient, serverListenSocketPort);
					
					std::cout<<"Client pressed "<<keyToSend<<std::endl;
				}
				else if (ConnectionType::NONE==connectionType)
				{
					player.processEvents(event);
				}
			}
		}
		
		if (ConnectionType::SERVER==connectionType)
		{
			sf::Packet packet;
			sf::IpAddress senderAddress;
			unsigned short senderPort;
			if(serverListenSocket.receive(packet,senderAddress,senderPort)==sf::Socket::Done)
			{
				sf::Int32 receivedKeyCode;
				packet>>receivedKeyCode;  
				
				std::cout << "New Message - "<<receivedKeyCode << " bytes from " << senderAddress << " on port " << senderPort << std::endl;
				sf::Event receivedEvent;
				receivedEvent.type = sf::Event::KeyPressed;
				receivedEvent.key.code = (sf::Keyboard::Key)receivedKeyCode;
				
				player.processEvents(receivedEvent);
			}
		}
		
		
		
		GameManager::GetGameManager().update(deltaTime);
		window.clear();
		GameManager::GetGameManager().draw();
		window.display();

	}
	return 0;
}
