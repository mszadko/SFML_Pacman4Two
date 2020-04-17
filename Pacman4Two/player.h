#pragma once
#include <SFML/Graphics.hpp>
#include "playerCollider.h"
#include "intersection.h"

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	IDLE
};

class Player : public sf::Transformable, public sf::Drawable
{
public:
	Player(float radius, sf::Vector2f startPosition,float speed = 100.0f);

	void processEvents(sf::Event event);
	void update(sf::Time deltaTime);
	sf::CircleShape playerSprite;
	Direction direction,nextDirection;
	Intersection* currentIntersection, *previousIntersection, *targetIntersection;
	sf::Vector2i playerPositionToMapIndex();
	Intersection* CanMove(sf::Vector2f direction);
	void MoveToIntersection(sf::Vector2f direction);
	void ChangePosition(Direction newDirection);
	void Move(sf::Time deltaTime);;
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	float speed;
	PlayerCollider collider;
	sf::Vector2f FloorPosition(sf::Vector2f position);
	sf::Vector2f DirectionToVector(Direction direction);
	float LengthFromPreviousNode(sf::Vector2f targetPosition);
	bool OvershotTarget();
	void SwapDirection();
};
