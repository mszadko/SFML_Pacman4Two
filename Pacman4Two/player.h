#pragma once
#include <SFML/Graphics.hpp>
#include "intersection.h"
#include "animationStateMachine.h"
#include "sharedEnumerations.h"
#include "gridWalker.h"

class Player : public sf::Drawable,public GridWalker
{
public:
	Player(sf::Vector2f startPosition, Intersection* currentIntersection,float speed = 100.0f);
	void processEvents(sf::Event event);
	void update(sf::Time deltaTime);
	sf::Sprite playerSprite;
	sf::Texture tileset;
	AnimationStateMachine animStateMachine;
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	
private:
	
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
	sf::Vector2f CalculateSpritePosition(sf::Vector2f position);

	void UpdateAnimation(sf::Time deltaTime);
	void Die();
	bool bIsDead;
};
