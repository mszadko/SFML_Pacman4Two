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
	void Restart();
protected:
	virtual void UpdateAnimation(sf::Time deltaTime);
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	void FindNextDirection();
	GhostFrightenedState frightenedState;
	bool bIsReturningToBase;
	bool bIsOnPatrol;
	sf::Vector2f patrolPoint;
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void TogglePatrolMode();
	void UpdateFrightenedMode();
	void UpdateTurnedOffMode();
	Direction currentAnimDirection;
	int milisecondsElapsedFromTargetSwitch;
	int milisecondsElapsedDuringBeingFrightened;
	const int patrolTime = 5000;
	const int chasingTime = 30000;
	const int frightenedTime = 6500;
	const int frightenedEndingTime = 3000;
	const int turnedOffTime = 2000;
	bool bIsTurnedOn;
	int milisecondsElapsedDuringBeingTurnedOff;
};