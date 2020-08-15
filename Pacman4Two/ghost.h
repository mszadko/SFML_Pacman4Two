#pragma once
#include "animatedGridWalker.h"

enum GhostType
{
	RED,
	PINK,
	BLUE,
	ORANGE
};

class Player;

class Ghost:public AnimatedGridWalker
{
public:
	Ghost(sf::Vector2f startPosition, Intersection* currentIntersection,GhostType type,float speed);
	void update(sf::Time deltaTime);
	GhostType type;
	Player* player;
protected:
	virtual void UpdateAnimation(sf::Time deltaTime);
	void FindNextDirection();
	bool bIsFrightened;
	bool bIsFlashing;
	bool bIsReturningToBase;
	bool bIsOnPatrol;
	sf::Vector2f patrolPoint;
private:
	void SwitchTarget();
	Direction currentAnimDirection;
	float milisecondsElapsedFromTargetSwitch;
	float patrolTime;
	float chasingTime;
};