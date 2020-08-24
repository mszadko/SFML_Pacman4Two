#pragma once
#include <SFML/Graphics.hpp>
#include "intersection.h"
#include "animationStateMachine.h"
#include "sharedEnumerations.h"
#include "animatedGridWalker.h"

class Player :public AnimatedGridWalker
{
public:
	Player(sf::Vector2f startPosition, Intersection* currentIntersection,PlayerNumer playerNumber = PlayerNumer::FIRST,float speed = 100.0f);
	void processEvents(sf::Event event);
	void update(sf::Time deltaTime);
	void Die();
	void Restart();
	bool IsDead();
protected:
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	virtual void UpdateAnimation(sf::Time deltaTime);
	virtual void OnTargetOvershot();
private:	
	bool bIsDead;
	Direction currentAnimDirection;
	PlayerNumer playerNumber;
};
