#pragma once
#include "level.h"
#include "player.h"
#include "sharedEnumerations.h"
#include "ghost.h"
#include <SFML/Network.hpp>


class GameManager
{
public:
	static GameManager& GetGameManager();
	void FrightenAllGhosts();
	Level* level = nullptr;
	sf::RenderWindow* window=nullptr;
	std::vector<Player*> players;
	std::array<Ghost*, 4> ghosts{{ nullptr }};
	void update(sf::Time deltaTime);
	void draw();
	void ProcessCollisionCheck();
	void StageCleared();
	void SetConnectionType(ConnectionType newConnectionType);
	ConnectionType GetConnectionType();
	bool IsServer();
	bool IsClient();
	bool IsStandalone();
	void SetGameState(GameState newGameState);
	void SetupNetworking(int argc, char* argv[]);
	void SendKeyPressToServer(sf::Event event);
	void SendKeyPressToAnotherClient(sf::Event event, ConnectionType clientToSendTo);
	void ProcessServerPacketListening();
	void ProcessClientPacketListening();
	void StartGame();
private:
	void updateGhosts(sf::Time deltaTime);
	void updatePlayers(sf::Time deltaTime);
	void drawGhosts();
	void drawPlayers();
	sf::Socket::Status SendClientToServerPacket(sf::Packet &packet);
	sf::Socket::Status SendServerToClientPacket(sf::Packet &packet, ConnectionType clientToSendTo);
	
	sf::UdpSocket clientOneSocket;
	sf::UdpSocket clientTwoSocket;
	sf::UdpSocket serverSocket;
	
	GameManager();
	GameState gameState;
	ConnectionType connectionType;

public:
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
};
