#pragma once
#include <SFML/Graphics.hpp>

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	IDLE
};

class Player : public sf::Transformable, public sf::Drawable
{
public:
	Player(float radius, sf::Vector2f startPosition);

	void processEvents(sf::Event event);
	void update(sf::Time deltaTime);

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;


	Direction direction;
	sf::CircleShape playerSprite;
	float speed;
};
