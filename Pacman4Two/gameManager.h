#pragma once
#include "level.h"
#include "player.h"
#include "sharedEnumerations.h"
#include "ghost.h"
#include <SFML/Network.hpp>

/**Singleton class used to manage all ingame behaviours.
 * It is used for update ghosts,players and level. It also makes drawing all game easier by combining draw functions in one place.
 * It handles networking events like sending, receiving and processing packets between clients and server.
 */
class GameManager
{
public:
	/**Call to get GameManager singleton instance. 
	 */
	static GameManager& GetGameManager();
	/**Sets frighten state on all ghosts on the level.
	 */
	void FrightenAllGhosts();
	/**Level pointer that is used in later computations.
	 */
	Level* level = nullptr;
	/**Render window in which ghosts,players and level will be drawn to.
	 */
	sf::RenderWindow* window=nullptr;
	/**Vector with all players in the game.
	 */
	std::vector<Player*> players;
	/**Array with ghosts in the game.
	 */
	std::array<Ghost*, 4> ghosts{{ nullptr }};
	/** Core function of all game objects.
	*  It is called every frame to update state of the object.
	*  deltaTime parameter is time elapsed from previous update.
	*/
	void update(sf::Time deltaTime);
	/**Draws ghosts,players and level.
	 */
	void draw();
	/**Process simple collision checking. Responsible for killing ghost and players.
	 */
	void ProcessCollisionCheck();
	/**Resets game after all food disappear from the level.
	 */
	void StageCleared();
	/**Sets connection type as server,client1 or client2.
	 */
	void SetConnectionType(ConnectionType newConnectionType);
	/**Returns connection type on current machine.
	 */
	ConnectionType GetConnectionType();
	/**Returns whether this machine is a sever.
	 */
	bool IsServer();
	/**Returns whether this machine is a client.
	 */
	bool IsClient();
	/**Returns whether this machine is non networked game.
	 */
	bool IsStandalone();
	/**Returns whether this machine has network authority (Is server or non networked game).
	 */	
	bool IsAuthority();
	/** Setter of game state/
	 */
	void SetGameState(GameState newGameState);
	/**Called before game stars. Sets networking state.
	 */	
	void SetupNetworking(int argc, char* argv[]);
	/**Sends player key press to server machine.
	 * It is later send from server to 2nd client.
	 */	
	void SendKeyPressToServer(sf::Event event);
	/**Sends key press that one client send onto the server to another client.
	 */	
	void SendKeyPressToAnotherClient(sf::Event event, ConnectionType clientToSendTo);
	/**Sends position correction of grid walkers into the clients machines.
	 */	
	void SendPositionCorrectionToAnotherClients(Direction newDir,sf::Vector2f correctedPosition,WalkableID id);
	/**Listening and processing of incoming packets on server side.
	 */	
	void ProcessServerPacketListening();
	/**Listening and processing of incoming packets on client side.
	 */	
	void ProcessClientPacketListening();
	/**Starts the game.
	 */
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
