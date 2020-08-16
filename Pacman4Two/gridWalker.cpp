#include "gridWalker.h"
#include "intersection.h"
#include <iostream>

GridWalker::GridWalker(sf::Vector2f startPosition,Intersection* currentIntersection,float speed)
{
	setPosition(startPosition);
	this->currentIntersection = currentIntersection;
	this->speed = speed;
	direction = IDLE;
}

void GridWalker::Move(sf::Time deltaTime)
{
	if (targetIntersection != currentIntersection && targetIntersection != nullptr)
	{
		if (OvershotTarget())
		{
			currentIntersection = targetIntersection;

			setPosition(sf::Vector2f(currentIntersection->intersectionPosition.x*ftileSize, currentIntersection->intersectionPosition.y*ftileSize));

			Intersection* moveToIntersection = FindIntersectionInDirection(nextDirection);
			if (moveToIntersection != nullptr)
			{
				direction = nextDirection;
			}
			if (moveToIntersection == nullptr)
			{
				moveToIntersection = FindIntersectionInDirection(direction);
			}
			if (moveToIntersection != nullptr)
			{
				targetIntersection = moveToIntersection;
				previousIntersection = currentIntersection;
				currentIntersection = nullptr;
			}
			else
			{
				direction = IDLE;
			}
		}
		else
		{
			sf::Vector2i playerPositionOnTileMap = PositionToMapCoord();

			if (playerPositionOnTileMap.x > mapWidth)
			{
				setPosition(sf::Vector2f(-1.0f*ftileSize, playerPositionOnTileMap.y*ftileSize));
			}
			else if (playerPositionOnTileMap.x < 0)
			{
				setPosition(sf::Vector2f((mapWidth + 1)*ftileSize, playerPositionOnTileMap.y*ftileSize));
			}
			else
			{
				float elapsed = deltaTime.asSeconds();
				sf::Vector2f moveOffset = DirectionToVector(direction)*elapsed*speed;
				move(moveOffset);
			}
		}
	}
}

void GridWalker::SetNextDirection(Direction newDirection)
{
	if (newDirection != direction)
	{
		nextDirection = newDirection;;
	}
	if (currentIntersection != nullptr)
	{
		Intersection* moveToIntersection = FindIntersectionInDirection(newDirection);
		if (moveToIntersection != nullptr)
		{
			direction = nextDirection;
			targetIntersection = moveToIntersection;
			previousIntersection = currentIntersection;
			currentIntersection = nullptr;
		}
	}
	if (direction != nextDirection)
	{
		switch (direction)
		{
		case UP:
			if (nextDirection == DOWN)
				SwapDirection();
			break;
		case DOWN:
			if (nextDirection == UP)
				SwapDirection();
			break;
		case LEFT:
			if (nextDirection == RIGHT)
				SwapDirection();
			break;
		case RIGHT:
			if (nextDirection == LEFT)
				SwapDirection();
			break;
		default:
			break;
		}
	}
}

Intersection * GridWalker::FindIntersectionInDirection(Direction direction)
{
	Intersection* moveToNode = nullptr;
	for (size_t i = 0; i < currentIntersection->directions.size(); i++)
	{
		if (direction == currentIntersection->directions[i])
		{
			moveToNode = currentIntersection->neighbours[i];
			if (!IsIntersectionValid(moveToNode))
				moveToNode = nullptr;
			else
				break;
		}
	}
	return moveToNode;
}

void GridWalker::SwapDirection()
{
	direction = nextDirection;
	nextDirection = IDLE;
	Intersection* swap = targetIntersection;
	targetIntersection = previousIntersection;
	previousIntersection = swap;
}

bool GridWalker::IsIntersectionValid(Intersection * intersectionToCheck)
{
	if (intersectionToCheck)
	{	
		if ((intersectionToCheck->type & 16)==16)
		{
			return false;
		}
		else if ((intersectionToCheck->type & 32) == 32)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool GridWalker::OvershotTarget()
{
	float distanceFromPreviousToTarget = DistanceFromPreviousNode(sf::Vector2f(targetIntersection->intersectionPosition.x*ftileSize, targetIntersection->intersectionPosition.y*ftileSize));
	float distanceFromPreviousToPlayer = DistanceFromPreviousNode(getPosition());
	return distanceFromPreviousToPlayer > distanceFromPreviousToTarget;
}

float GridWalker::DistanceFromPreviousNode(sf::Vector2f targetPosition)
{
	sf::Vector2f difference = targetPosition - sf::Vector2f(previousIntersection->intersectionPosition.x*ftileSize, previousIntersection->intersectionPosition.y*ftileSize);
	return sqrt(pow(difference.x, 2) + pow(difference.y, 2));
}

sf::Vector2i GridWalker::PositionToMapCoord()
{
	sf::Vector2f playerPos = getPosition();
	return sf::Vector2i((int)roundf(playerPos.x / ftileSize), (int)roundf(playerPos.y / ftileSize));
}

sf::Vector2f GridWalker::DirectionToVector(Direction direction)
{
	switch (direction)
	{
	case UP:
		return sf::Vector2f(0.0f, -1.0f);
		break;
	case DOWN:
		return sf::Vector2f(0.0f, 1.0f);
		break;
	case LEFT:
		return sf::Vector2f(-1.0f, 0.0f);
		break;
	case RIGHT:
		return sf::Vector2f(1.0f, 0.0f);
		break;
	case IDLE:
	default:
		return sf::Vector2f(0.0f, 0.0f);
		break;
	}
}