#include "player.h"
#include <iostream>
#include <math.h>

Player::Player(float radius, sf::Vector2f startPosition, float speed)
{
	setPosition(startPosition);
	playerSprite = sf::CircleShape(radius);
	playerSprite.setFillColor(sf::Color::Yellow);
	playerSprite.setPosition(FloorPosition(startPosition));
	direction = IDLE;// LEFT;
	this->speed = speed;
	collider.bounds = playerSprite.getGlobalBounds();
	collider.owner = this;
}
void Player::processEvents(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Up)
	{
		direction = UP;
		MoveToIntersection(sf::Vector2f(0.0f, -1.0f));
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		direction = DOWN;
		MoveToIntersection(sf::Vector2f(0.0f, 1.0f));
	}	
	else if (event.key.code == sf::Keyboard::Left)
	{
		direction = LEFT;
		MoveToIntersection(sf::Vector2f(-1.0f, 0.0f));
	}
	else if (event.key.code == sf::Keyboard::Right)
	{
		direction = RIGHT;
		MoveToIntersection(sf::Vector2f(1.0f, 0.0f));
	}
}

void Player::update(sf::Time deltaTime)
{
	float elapsed = deltaTime.asSeconds();
	/*if (direction == UP)
		move(0, -1 * elapsed*speed);
	else if (direction == DOWN)
		move(0, 1 * elapsed*speed);
	else if (direction == LEFT)
		move(-1 * elapsed*speed, 0);
	else if (direction == RIGHT)
		move(1 * elapsed*speed, 0);*/
	collider.bounds = playerSprite.getGlobalBounds();
	playerSprite.setPosition(FloorPosition(getPosition()));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(playerSprite, states);
}

sf::Vector2f Player::FloorPosition(sf::Vector2f position)
{
	return sf::Vector2f(floorf(position.x), floorf(position.y));
}

sf::Vector2i Player::playerPositionToMapIndex()
{
	sf::Vector2f playerPos = playerSprite.getPosition();
	return sf::Vector2i(((int)playerPos.x) / 8, ((int)playerPos.y) / 8);
}

Intersection * Player::CanMove(sf::Vector2f direction)
{
	Intersection* moveToNode = nullptr;
	for (size_t i = 0; i < currentIntersection->neighbours.size(); i++)
	{
		//just checking if direction passed to function is in available directions (we should not trust floats so thats how we'll do it)
		sf::Vector2f difference;
		difference = currentIntersection->directions[i] - direction;
		if (sqrtf(pow(difference.x, 2) + pow(difference.y, 2)) < 0.1f)
		{
			moveToNode = currentIntersection->neighbours[i];
			break;
		}
	}
	return moveToNode;
}

void Player::MoveToIntersection(sf::Vector2f direction)
{
	Intersection* moveToIntersection = CanMove(direction);
	if (moveToIntersection)
	{
		setPosition(moveToIntersection->intersectionPosition.x*16.0f, moveToIntersection->intersectionPosition.y*16.0f);
		currentIntersection = moveToIntersection;
	}
}
