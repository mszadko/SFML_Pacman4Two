#include "gameManager.h"
GameManager::GameManager()
{
}

GameManager& GameManager::GetGameManager()
{
	static GameManager instance;
	return instance;
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
	size_t size = ghosts.size();
	sf::Vector2i playerPosition;
	if (player)
	{
		playerPosition = player->PositionToMapCoord();
	}
	for (size_t i = 0; i < size; i++)
	{
		if (ghosts[i])
		{
			sf::Vector2i ghostPosition = ghosts[i]->PositionToMapCoord();
			if (ghostPosition==playerPosition)
			{
				if (ghosts[i]->IsDead())
				{
					continue;
				}
				else if (ghosts[i]->IsFrightened())
				{
					ghosts[i]->Die();
				}
				else
				{
					player->Die();
				}
				
			}
		}
	}
}


