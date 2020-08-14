#include "player.h"
#include <iostream>
#include <math.h>

Player::Player(sf::Vector2f startPosition, float speed)
{
	setPosition(startPosition);
	tileset.loadFromFile("Textures/pacmanspritesheet.png");
	playerSprite.setTexture(tileset);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	playerSprite.setScale(sf::Vector2f(1.5f, 1.5f));
	playerSprite.setPosition(CalculateSpritePosition(startPosition));
	direction = IDLE;// LEFT;
	this->speed = speed;
	
	Animation moveUpAnim = Animation(3, 2, true, &playerSprite,
		{
		sf::IntRect(0,0,16,16),
		sf::IntRect(16,16,16,16),
		sf::IntRect(32,16,16,16)
		});
	Animation moveDownAnim = Animation(3, 100, true, &playerSprite,
		{
		sf::IntRect(0,0,16,16),
		sf::IntRect(48,16,16,16),
		sf::IntRect(0,32,16,16)
		});
	Animation moveLeftAnim = Animation(3, 100, true, &playerSprite,
		{
		sf::IntRect(0,0,16,16),
		sf::IntRect(48,0,16,16),
		sf::IntRect(0,16,16,16)
		});
	Animation moveRightAnim = Animation(3, 100, true, &playerSprite,
		{
		sf::IntRect(0,0,16,16),
		sf::IntRect(16,0,16,16),
		sf::IntRect(32,0,16,16)
		});
	Animation deathAnim = Animation(12, 50, false, &playerSprite,
		{
		sf::IntRect( 0, 0,16,16),
		sf::IntRect(16,32,16,16),
		sf::IntRect(32,32,16,16),
		sf::IntRect(48,32,16,16),
		sf::IntRect( 0,48,16,16),
		sf::IntRect(16,48,16,16),
		sf::IntRect(32,48,16,16),
		sf::IntRect(48,48,16,16),
		sf::IntRect( 0,64,16,16),
		sf::IntRect(16,64,16,16),
		sf::IntRect(32,64,16,16),
		sf::IntRect(48,64,16,16),
		});

	animStateMachine.AddState("UP", moveUpAnim);
	animStateMachine.AddState("DOWN", moveDownAnim);
	animStateMachine.AddState("LEFT", moveLeftAnim);
	animStateMachine.AddState("RIGHT", moveRightAnim);
	animStateMachine.AddState("DEATH", deathAnim);
}

void Player::processEvents(sf::Event event)
{
	if (bIsDead)
		return;
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
	else if (event.key.code ==sf::Keyboard::Space)
	{
		Die();
	}
}

void Player::update(sf::Time deltaTime)
{
	float elapsed = deltaTime.asSeconds();
	Move(deltaTime);
	playerSprite.setPosition(CalculateSpritePosition(getPosition()));
	UpdateAnimation(deltaTime);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(playerSprite, states);
}

sf::Vector2f Player::CalculateSpritePosition(sf::Vector2f position)
{
	return sf::Vector2f(floorf(position.x-4), floorf(position.y-4));
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
	default:
		return sf::Vector2f(0.0f, 0.0f);
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

void Player::UpdateAnimation(sf::Time deltaTime)
{
	static Direction currentAnimDirection = direction;
	static bool bIsAlreadyDead = bIsDead;

	if (currentAnimDirection!=direction&&!bIsDead)
	{
		currentAnimDirection = direction;
		switch (direction)
		{
		case UP:
			animStateMachine.PlayState("UP");
			break;
		case DOWN:
			animStateMachine.PlayState("DOWN");
			break;
		case LEFT:
			animStateMachine.PlayState("LEFT");
			break;
		case RIGHT:
			animStateMachine.PlayState("RIGHT");
			break;
		case IDLE:
			break;
		default:
			break;
		}	
	}
	if (bIsDead && !bIsAlreadyDead)
	{
		bIsAlreadyDead = bIsDead;
		animStateMachine.PlayState("DEATH");
	}
	if (direction != IDLE || bIsDead)
	{
		animStateMachine.Update(deltaTime);
	}
}

void Player::Die()
{
	bIsDead = true;
	direction = IDLE;
}



sf::Vector2i Player::playerPositionToMapIndex()
{
	sf::Vector2f playerPos = playerSprite.getPosition();
	return sf::Vector2i((int)roundf(playerPos.x / 16.0f), (int)roundf(playerPos.y / 16.0f));
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
			float speedMultipler = (playerPositionToMapIndex().x > 28 || playerPositionToMapIndex().x < 0) ? 40.0f : 1.0f;
			sf::Vector2f moveOffset = DirectionToVector(direction)*elapsed*speed*speedMultipler;
			move(moveOffset);
		}
	}
}



