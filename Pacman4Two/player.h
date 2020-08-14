#pragma once
#include <SFML/Graphics.hpp>
#include "intersection.h"
#include "animationStateMachine.h"
#include "sharedEnumerations.h"

class Player : public sf::Transformable, public sf::Drawable
{
public:
	Player(sf::Vector2f startPosition,float speed = 100.0f);
	void processEvents(sf::Event event);
	void update(sf::Time deltaTime);
	sf::Sprite playerSprite;
	sf::Texture tileset;
	AnimationStateMachine animStateMachine;
	Direction direction,nextDirection;
	Intersection* currentIntersection, *previousIntersection, *targetIntersection;
	sf::Vector2i playerPositionToMapIndex();
	Intersection* FindIntersectionInDirection(Direction direction);
	void SetNextDirection(Direction newDirection);
	void Move(sf::Time deltaTime);
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	float speed;
	sf::Vector2f CalculateSpritePosition(sf::Vector2f position);
	sf::Vector2f DirectionToVector(Direction direction);
	float LengthFromPreviousNode(sf::Vector2f targetPosition);
	bool OvershotTarget();
	void SwapDirection();
	void UpdateAnimation(sf::Time deltaTime);
	void Die();
	bool bIsDead;
};
