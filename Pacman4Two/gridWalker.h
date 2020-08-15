#pragma once
#include "sharedEnumerations.h"
#include <SFML/Graphics.hpp>
class Intersection;

class GridWalker : public sf::Transformable
{
public:
	GridWalker(Intersection* currentIntersection,float speed =100.0f);
	void Move(sf::Time deltaTime);
	void SetNextDirection(Direction newDirection);
	sf::Vector2i PositionToMapCoord();
protected:
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	Direction direction;
private:
	Intersection* FindIntersectionInDirection(Direction direction);
	void SwapDirection();
	bool OvershotTarget();
	float DistanceFromPreviousNode(sf::Vector2f targetPosition);
	
	sf::Vector2f DirectionToVector(Direction direction);

	float speed;
	Direction nextDirection;
	Intersection* currentIntersection, *previousIntersection, *targetIntersection;
};