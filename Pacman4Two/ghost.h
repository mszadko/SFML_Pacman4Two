#pragma once
#include "animatedGridWalker.h"

enum GhostType
{
	RED,
	PINK,
	BLUE,
	ORANGE
};
enum GhostFrightenedState
{
	NOTFRIGHTENED,
	FRIGHTENED,
	FRIGHTENEDENDING
};
class Player;

class Ghost:public AnimatedGridWalker
{
public:
	Ghost(sf::Vector2f startPosition, Intersection* currentIntersection,GhostType type,float speed);
	void update(sf::Time deltaTime);
	GhostType type;
	Player* player;
	void SwitchFrightenedMode(GhostFrightenedState NewIsFrightened);
	bool IsFrightened();
	bool IsDead();
	void Die();
protected:
	virtual void UpdateAnimation(sf::Time deltaTime);
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	void FindNextDirection();
	GhostFrightenedState frightenedState;
	bool bIsReturningToBase;
	bool bIsOnPatrol;
	sf::Vector2f patrolPoint;
private:
	void TogglePatrolMode();
	void UpdateFrightenedMode();
	Direction currentAnimDirection;
	int milisecondsElapsedFromTargetSwitch;
	int milisecondsElapsedDuringBeingFrightened;
	sf::Vector2f respawnLocation;
	const int patrolTime = 5000;
	const int chasingTime = 30000;
	const int frightenedTime = 6500;
	const int frightenedEndingTime = 3000;
	
};