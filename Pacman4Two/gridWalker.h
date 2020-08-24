#pragma once
#include "sharedEnumerations.h"
#include <SFML/Graphics.hpp>
class Intersection;

class GridWalker : public sf::Transformable
{
public:
	GridWalker(sf::Vector2f startPosition,Intersection* currentIntersection,float speed = 100.0f);
	void Move(sf::Time deltaTime);
	void SetNextDirection(Direction newDirection);
	sf::Vector2i PositionToMapCoord();
	void CorrectPosition(sf::Vector2f correctedPosition, Direction newDir, Intersection* newTargetIntersection);
protected:
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	Direction direction;
	Intersection* currentIntersection, *previousIntersection, *targetIntersection;
	Direction nextDirection;
	void ResetMovement();
	virtual void OnTargetOvershot();
	sf::Vector2f respawnLocation;
	Intersection* respawnIntersection;
private:
	Intersection* FindIntersectionInDirection(Direction direction);
	void SwapDirection();
	bool OvershotTarget();
	float DistanceFromPreviousNode(sf::Vector2f targetPosition);
	sf::Vector2f DirectionToVector(Direction direction);

	float speed;	
};
