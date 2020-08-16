#include "gameManager.h"
GameManager::GameManager()
{
	gameState = RUNNING;
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
	//gameState = STOPPED;
	level->reinit();
	size_t numberOfGhosts = ghosts.size();
	for (size_t ghostIndex = 0; ghostIndex < numberOfGhosts; ghostIndex++)
	{
		if (ghosts[ghostIndex])
		{
			ghosts[ghostIndex]->Restart();
		}
	}
}


