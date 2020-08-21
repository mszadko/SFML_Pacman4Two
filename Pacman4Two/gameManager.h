#pragma once
#include "level.h"
#include "player.h"
#include "sharedEnumerations.h"
#include "ghost.h"



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
	void updateGhosts(sf::Time deltaTime);
	void updatePlayers(sf::Time deltaTime);
	void drawGhosts();
	void drawPlayers();
	void ProcessCollisionCheck();
	void StageCleared();
private:
	GameManager();
	GameState gameState;

public:
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
};
