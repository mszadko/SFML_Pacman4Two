#pragma once
#include "gridWalker.h"
#include "SFML/Graphics.hpp"
#include "animationStateMachine.h"
#include <string>

class Intersection;

class AnimatedGridWalker:public GridWalker,public sf::Drawable
{
public:
	AnimatedGridWalker(sf::Vector2f startPosition, Intersection* currentIntersection,std::string textureFileDestination, float speed = 100.0f);
	sf::Sprite sprite;
	sf::Texture tileset;
	AnimationStateMachine animStateMachine;
	virtual void update(sf::Time deltaTime);
protected:
	
	virtual void UpdateAnimation(sf::Time deltaTime);
	virtual sf::Vector2f CalculateSpritePosition();
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};