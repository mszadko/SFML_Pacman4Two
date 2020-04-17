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
		ChangePosition(UP);

	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		ChangePosition(DOWN);

	}	
	else if (event.key.code == sf::Keyboard::Left)
	{
		ChangePosition(LEFT);

	}
	else if (event.key.code == sf::Keyboard::Right)
	{
		ChangePosition(RIGHT);

	}
}

void Player::update(sf::Time deltaTime)
{
	float elapsed = deltaTime.asSeconds();
	Move(deltaTime);
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

sf::Vector2f Player::DirectionToVector(Direction direction)
{
	switch (direction)
	{
	case UP:
		return sf::Vector2f(0.0f, -1.0f);
		break;
	case DOWN:
		return sf::Vector2f(0.0f, 1.0f);
		break;
	case LEFT:
		return sf::Vector2f(-1.0f, 0.0f);
		break;
	case RIGHT:
		return sf::Vector2f(1.0f, 0.0f);
		break;
	case IDLE:
		return sf::Vector2f(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

float Player::LengthFromPreviousNode(sf::Vector2f targetPosition)
{
	sf::Vector2f difference = targetPosition - sf::Vector2f(previousIntersection->intersectionPosition.x*16.0f, previousIntersection->intersectionPosition.y*16.0f);
	return sqrt(pow(difference.x, 2) + pow(difference.y, 2));
}

bool Player::OvershotTarget()
{
	float distanceFromPreviousToTarget = LengthFromPreviousNode(sf::Vector2f(targetIntersection->intersectionPosition.x*16.0f, targetIntersection->intersectionPosition.y*16.0f));
	float distanceFromPreviousToPlayer = LengthFromPreviousNode(getPosition());
	return distanceFromPreviousToPlayer > distanceFromPreviousToTarget;
}

void Player::SwapDirection()
{
	direction = nextDirection;
	nextDirection = IDLE;
	Intersection* swap = targetIntersection;
	targetIntersection = previousIntersection;
	previousIntersection = swap;
}

sf::Vector2i Player::playerPositionToMapIndex()
{
	sf::Vector2f playerPos = playerSprite.getPosition();
	return sf::Vector2i(((int)playerPos.x) / 16, ((int)playerPos.y) / 16);
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

void Player::ChangePosition(Direction newDirection)
{
	if (newDirection!=direction)
	{
		nextDirection = newDirection;;
	}
	if (currentIntersection!=nullptr)
	{
		sf::Vector2f dir = DirectionToVector(newDirection);
		Intersection* moveToIntersection = CanMove(dir);
		if (moveToIntersection!=nullptr)
		{
			direction = newDirection;
			targetIntersection = moveToIntersection;
			previousIntersection = currentIntersection;
			currentIntersection = nullptr;
		}
	}
}

void Player::Move(sf::Time deltaTime)
{
	if (direction != nextDirection)
	{
		switch (direction)
		{
		case UP:
			if (nextDirection == DOWN)
				SwapDirection();
			break;
		case DOWN:
			if (nextDirection == UP)
				SwapDirection();
			break;
		case LEFT:
			if (nextDirection == RIGHT)
				SwapDirection();
			break;
		case RIGHT:
			if (nextDirection == LEFT)
				SwapDirection();
			break;
		default:
			break;
		}
	}
	if (targetIntersection != currentIntersection &&targetIntersection!=nullptr)
	{
		if (OvershotTarget())
		{
			currentIntersection = targetIntersection;

			setPosition(sf::Vector2f(currentIntersection->intersectionPosition.x*16.0f, currentIntersection->intersectionPosition.y*16.0f));

			Intersection* moveToIntersection = CanMove(DirectionToVector(nextDirection));
			if (moveToIntersection!=nullptr)
			{
				direction = nextDirection;
			}
			if (moveToIntersection==nullptr)
			{
				moveToIntersection = CanMove(DirectionToVector(direction));
			}
			if (moveToIntersection != nullptr)
			{
				targetIntersection = moveToIntersection;
				previousIntersection = currentIntersection;
				currentIntersection = nullptr;
			}
			else
			{
				direction = IDLE;
			}
		}
		else
		{
			float elapsed = deltaTime.asSeconds();
			std::cout << playerPositionToMapIndex().x << std::endl;
			float speedMultipler = (playerPositionToMapIndex().x > 28 || playerPositionToMapIndex().x < 0) ? 40.0f : 1.0f;
			sf::Vector2f moveOffset = DirectionToVector(direction)*elapsed*speed*speedMultipler;
			move(moveOffset);
		}
	}
}



