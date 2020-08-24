#include "gameManager.h"
#include <iostream>

GameManager::GameManager()
{
	gameState = GameState::STOPPED;
	connectionType = ConnectionType::NONE;
	
	clientOneSocket.setBlocking(false);
	clientTwoSocket.setBlocking(false);
	serverSocket.setBlocking(false);
}

GameManager& GameManager::GetGameManager()
{
	static GameManager instance;
	return instance;
}

void GameManager::StartGame()
{
	gameState = GameState::RUNNING;
}

void GameManager::SetupNetworking(int argc, char* argv[])
{	
	for (int i = 0; i < argc; i++)
	{	
		if (argv[i]==std::string("clientone"))
		{
			GameManager::GetGameManager().SetConnectionType(ConnectionType::CLIENTONE);
			break;
		}
		if (argv[i]==std::string("clienttwo"))
		{
			GameManager::GetGameManager().SetConnectionType(ConnectionType::CLIENTTWO);
			break;
		}
		if (argv[i]==std::string("server"))
		{	
			GameManager::GetGameManager().SetConnectionType(ConnectionType::SERVER);
			break;
		}
	}
}

void GameManager::SendKeyPressToServer(sf::Event event)
{
	sf::Packet packet;
	sf::Int8 packetFlag = (sf::Int8) PacketTag::ToServerClientPressedButton;
	sf::Int32 keyToSend = event.key.code;
	
	packet<<packetFlag;
	packet<<keyToSend;
	
	SendClientToServerPacket(packet);
}

void GameManager::SendKeyPressToAnotherClient(sf::Event event, ConnectionType clientToSendTo)
{
	sf::Packet packet;
	sf::Int8 packetFlag = (sf::Int8) PacketTag::ToClientPlayerNewWalkInfo;
	sf::Int32 keyToSend = event.key.code;
	
	packet << packetFlag;
	packet << keyToSend;
	
	SendServerToClientPacket(packet,clientToSendTo);
}

void GameManager::SendPositionCorrectionToAnotherClients(Direction newDir,sf::Vector2f correctedPosition,WalkableID id)
{
	sf::Packet packet;
	sf::Int8 packetFlag = (sf::Int8) PacketTag::ToClientPositionCorrection;
	
	packet << packetFlag;
	
	packet << correctedPosition.x;
	packet << correctedPosition.y;
	
	sf::Int8 directionId = (sf::Int8)newDir;
	
	packet << directionId;
	
	sf::Int8 walkableId = (sf::Int8)id;
	
	packet << walkableId;
	
	SendServerToClientPacket(packet,ConnectionType::CLIENTONE);
	SendServerToClientPacket(packet,ConnectionType::CLIENTTWO);
}

void GameManager::ProcessServerPacketListening()
{
	sf::Packet packet;
	sf::IpAddress senderAddress;
	unsigned short senderPort;
	
	if(serverSocket.receive(packet,senderAddress,senderPort)==sf::Socket::Done)
	{
		ConnectionType packetFrom;
		switch (senderPort)
		{
			case serverPort:
				packetFrom = ConnectionType::SERVER;
				break;
			case clientOnePort:
				packetFrom = ConnectionType::CLIENTONE;
				break;
			case clientTwoPort:
				packetFrom = ConnectionType::CLIENTTWO;
				break;
			default:
				packetFrom = ConnectionType::NONE;
				break;
		}
		
		PacketTag receivedPacketTag;
		sf::Int8 packetFlag;
		packet >> packetFlag;
		receivedPacketTag = (PacketTag) packetFlag;
		
		switch (receivedPacketTag)
		{
			case ToServerClientPressedButton:
				{
					sf::Int32 receivedKeyCode;
					packet >> receivedKeyCode;  
					sf::Event receivedEvent;
					receivedEvent.type = sf::Event::KeyPressed;
					receivedEvent.key.code = (sf::Keyboard::Key)receivedKeyCode;
					players[packetFrom == ConnectionType::CLIENTONE ? 0 : 1]->processEvents(receivedEvent);
					SendKeyPressToAnotherClient(receivedEvent,packetFrom == ConnectionType::CLIENTONE ? CLIENTTWO : CLIENTONE);
				}
				break;
				
			case ToClientPlayerNewWalkInfo:
			case ToClientPositionCorrection:
			default:
				break;
		}
	}
}

void GameManager::ProcessClientPacketListening()
{
	sf::Packet packet;
	sf::IpAddress senderAddress;
	unsigned short senderPort;
	sf::UdpSocket* socketToListen = GetConnectionType() == ConnectionType::CLIENTONE ? &clientOneSocket : &clientTwoSocket;
	if(socketToListen->receive(packet,senderAddress,senderPort)==sf::Socket::Done)
	{
		PacketTag receivedPacketTag;
		sf::Int8 packetFlag;
		packet >> packetFlag;
		receivedPacketTag = (PacketTag) packetFlag;
		
		switch (receivedPacketTag)
		{
			case ToClientPlayerNewWalkInfo:
				{
					sf::Int32 receivedKeyCode;
					packet >> receivedKeyCode;
				
					sf::Event receivedEvent;
					receivedEvent.type = sf::Event::KeyPressed;
					receivedEvent.key.code = (sf::Keyboard::Key)receivedKeyCode;
				
					players[GetConnectionType() == ConnectionType::CLIENTONE ? 1 : 0]->processEvents(receivedEvent);
				}
				break;
			case ToClientPositionCorrection:
				{
					sf::Vector2f correctedPosition;
					packet >> correctedPosition.x;
					packet >> correctedPosition.y;
					
					sf::Int8 directionId;
	
					packet >> directionId;
					
					Direction newDir = (Direction) directionId;

					sf::Int8 walkableId;
	
					packet >> walkableId;
					
					WalkableID walkable = (WalkableID) walkableId;
					switch (walkable)
					{
						case GHOSTONE:
						case GHOSTTWO:
						case GHOSTTHREE:
						case GHOSTFOUR:
							ghosts[walkable]->CorrectPosition(correctedPosition,newDir,level->GetIntersectionAt(correctedPosition));
							break;
						case PLAYERONE:
							players[0]->CorrectPosition(correctedPosition,newDir,level->GetIntersectionAt(correctedPosition));
							break;
						case PLAYERTWO:
							players[1]->CorrectPosition(correctedPosition,newDir,level->GetIntersectionAt(correctedPosition));
							break;
						default:
							break;
					}
				}
				break;
			case ToServerClientPressedButton:
			default:
				break;
		}		
	}
}

sf::Socket::Status GameManager::SendClientToServerPacket(sf::Packet &packet)
{
	sf::IpAddress recipient = sf::IpAddress::Broadcast;
	
	if (GetConnectionType() == ConnectionType::CLIENTONE)
	{
		return clientOneSocket.send(packet, recipient, serverPort);
	}
	else if (GetConnectionType() == ConnectionType::CLIENTTWO)
	{
		return clientTwoSocket.send(packet, recipient, serverPort);
	}
}	

sf::Socket::Status GameManager::SendServerToClientPacket(sf::Packet &packet, ConnectionType clientToSendTo)
{
	sf::IpAddress recipient = sf::IpAddress::Broadcast;
	serverSocket.send(packet,recipient, ConnectionType::CLIENTONE==clientToSendTo? clientOnePort : clientTwoPort);
}

void GameManager::SetConnectionType(ConnectionType newConnectionType)
{
	switch (connectionType)
	{
		case CLIENTONE:
			clientOneSocket.unbind();
			break;
		case CLIENTTWO:
			clientTwoSocket.unbind();
			break;
		case SERVER:
			serverSocket.unbind();
			break;
		case NONE:
		default:
			break;
	}
	
	connectionType = newConnectionType;
	
	switch (connectionType)
	{
		case CLIENTONE:
			std::cout<<"Connected as a client one.\n";
			clientOneSocket.bind(clientOnePort);
			break;
		case CLIENTTWO:
			std::cout<<"Connected as a client two.\n";
			clientTwoSocket.bind(clientTwoPort);
			break;
		case SERVER:
			std::cout<<"Connected as a server.\n";
			serverSocket.bind(serverPort);
			break;
		case NONE:
		default:
			break;	
	}
}

ConnectionType GameManager::GetConnectionType()
{
	return connectionType;
}

bool GameManager::IsServer()
{
	return connectionType==ConnectionType::SERVER;
}

bool GameManager::IsClient()
{
	return connectionType == ConnectionType::CLIENTONE || connectionType == ConnectionType::CLIENTTWO;
}

bool GameManager::IsStandalone()
{
	return connectionType == ConnectionType::NONE;
}

bool GameManager::IsAuthority()
{
	return connectionType == ConnectionType::NONE || connectionType == ConnectionType::SERVER;
}

void GameManager::SetGameState(GameState newGameState)
{
	gameState = newGameState;
}

void GameManager::FrightenAllGhosts()
{
	size_t size = ghosts.size();
	for (size_t i = 0; i < size; i++)
	{
		if (ghosts[i])
		{
			ghosts[i]->SwitchFrightenedMode(FRIGHTENED);
		}
	}
}

void GameManager::update(sf::Time deltaTime)
{
	ProcessCollisionCheck();
	if (level)
	{
		if (gameState)
		{
			updatePlayers(deltaTime);
			updateGhosts(deltaTime);
			level->update(deltaTime);
		}
	}
}

void GameManager::draw()
{
	if (!window)
		return;
	window->draw(*level);
	drawGhosts();
	drawPlayers();
}

void GameManager::updateGhosts(sf::Time deltaTime)
{
	size_t numberOfGhosts = ghosts.size();
	for (size_t ghostIndex = 0; ghostIndex < numberOfGhosts; ghostIndex++)
	{
		if (ghosts[ghostIndex])
		{
			ghosts[ghostIndex]->update(deltaTime);
		}
	}
}

void GameManager::updatePlayers(sf::Time deltaTime)
{
	size_t numberOfPlayers = players.size();
	for (size_t playerIndex = 0; playerIndex < numberOfPlayers; playerIndex++)
	{
		if (players[playerIndex])
		{
			players[playerIndex]->update(deltaTime);
			FoodType eatenFood = level->ConsumeFood(players[playerIndex]->PositionToMapCoord());
			if (eatenFood)
			{
				if (eatenFood == POWERUP)
				{
					GameManager::GetGameManager().FrightenAllGhosts();
				}
				if (!level->GetFoodLeft())
				{
					StageCleared();
				}
			}	
		}
	}
}

void GameManager::drawGhosts()
{
	size_t numberOfGhosts = ghosts.size();
	for (size_t ghostIndex = 0; ghostIndex < numberOfGhosts; ghostIndex++)
	{
		if (ghosts[ghostIndex])
		{
			window->draw(*ghosts[ghostIndex]);
		}
	}
}

void GameManager::drawPlayers()
{

	size_t numberOfPlayers = players.size();
	for (size_t playerIndex = 0; playerIndex < numberOfPlayers; playerIndex++)
	{
		if (players[playerIndex])
		{
			window->draw(*players[playerIndex]);
		}
	}
}

void GameManager::ProcessCollisionCheck()
{
	return;
	size_t numberOfGhosts = ghosts.size();
	size_t numberOfPlayers = players.size();
	

	for (size_t playerIndex = 0; playerIndex < numberOfPlayers; playerIndex++)
	{
		sf::Vector2i playerPosition;
		if (players[playerIndex])
		{
			playerPosition = players[playerIndex]->PositionToMapCoord();
		}

		for (size_t ghostIndex = 0; ghostIndex < numberOfGhosts; ghostIndex++)
		{
			if (ghosts[ghostIndex])
			{
				sf::Vector2i ghostPosition = ghosts[ghostIndex]->PositionToMapCoord();
				if (ghostPosition == playerPosition)
				{
					if (ghosts[ghostIndex]->IsDead())
					{
						continue;
					}
					else if (ghosts[ghostIndex]->IsFrightened())
					{
						ghosts[ghostIndex]->Die();
					}
					else
					{
						players[playerIndex]->Die();
					}
				}
			}
		}
	}
}

void GameManager::StageCleared()
{
	level->reinit();
	size_t numberOfGhosts = ghosts.size();
	for (size_t ghostIndex = 0; ghostIndex < numberOfGhosts; ghostIndex++)
	{
		if (ghosts[ghostIndex])
		{
			ghosts[ghostIndex]->Restart();
		}
	}
	size_t numberOfPlayers = players.size();
	for (size_t playerIndex = 0; playerIndex < numberOfPlayers ; playerIndex++)
	{
		players[playerIndex]->Restart();
	}
	
}
