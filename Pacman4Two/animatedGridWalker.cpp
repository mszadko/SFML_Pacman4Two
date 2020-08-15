#include "animatedGridWalker.h"

AnimatedGridWalker::AnimatedGridWalker(sf::Vector2f startPosition, Intersection * currentIntersection, std::string textureFileDestination, float speed)
	:GridWalker(startPosition ,currentIntersection, speed)
{
	tileset.loadFromFile(textureFileDestination);
	sprite.setTexture(tileset);
	sprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
	sprite.setPosition(CalculateSpritePosition());
}

void AnimatedGridWalker::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void AnimatedGridWalker::update(sf::Time deltaTime)
{
	UpdateAnimation(deltaTime);
}

void AnimatedGridWalker::UpdateAnimation(sf::Time deltaTime)
{
}

sf::Vector2f AnimatedGridWalker::CalculateSpritePosition()
{
	sf::Vector2f position = getPosition();
	return sf::Vector2f(floorf(position.x), floorf(position.y));
}