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
	Player*player = nullptr;
	std::array<Ghost*, 4> ghosts{ nullptr };
	void update(sf::Time deltaTime);
private:
	GameManager();


public:
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
};