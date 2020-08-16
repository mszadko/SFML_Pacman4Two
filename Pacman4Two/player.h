#pragma once
#include <SFML/Graphics.hpp>
#include "intersection.h"
#include "animationStateMachine.h"
#include "sharedEnumerations.h"
#include "animatedGridWalker.h"

class Player :public AnimatedGridWalker
{
public:
	Player(sf::Vector2f startPosition, Intersection* currentIntersection,float speed = 100.0f);
	void processEvents(sf::Event event);
	void update(sf::Time deltaTime);
	void Die();
	void Restart();
protected:
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	virtual void UpdateAnimation(sf::Time deltaTime);
private:	
	bool bIsDead;
	Direction currentAnimDirection;
};
