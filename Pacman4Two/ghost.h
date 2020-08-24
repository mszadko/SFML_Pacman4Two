#pragma once
#include "animatedGridWalker.h"

class Player;

class Ghost:public AnimatedGridWalker
{
public:
	Ghost(sf::Vector2f startPosition, Intersection* currentIntersection,GhostType type,float speed);
	void update(sf::Time deltaTime);
	GhostType type;
	std::vector<Player*> players;
	void SwitchFrightenedMode(GhostFrightenedState NewIsFrightened);
	bool IsFrightened();
	bool IsDead();
	void Die();
	void Restart();
protected:
	virtual void UpdateAnimation(sf::Time deltaTime);
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	virtual void OnTargetOvershot();
	Direction FindNextDirection();
	GhostFrightenedState frightenedState;
	bool bIsReturningToBase;
	bool bIsOnPatrol;
	sf::Vector2f patrolPoint;
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void TogglePatrolMode();
	void UpdateFrightenedMode();
	void UpdateTurnedOffMode();
	bool IsTherePlayerToChase();
	Player* GetClosestPlayer();
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
