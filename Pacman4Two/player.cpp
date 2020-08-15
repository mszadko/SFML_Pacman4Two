#include "player.h"
#include <iostream>
#include <math.h>

Player::Player(sf::Vector2f startPosition, Intersection* currentIntersection, float speed)
	: AnimatedGridWalker(startPosition,currentIntersection,"Textures/pacmanspritesheet.png", speed)
{
	Animation moveUpAnim = Animation(3, 60, true, &sprite,
		{
		sf::IntRect( 0, 0,tileSize,tileSize),
		sf::IntRect(16,16,tileSize,tileSize),
		sf::IntRect(32,16,tileSize,tileSize)
		});
	Animation moveDownAnim = Animation(3, 60, true, &sprite,
		{
		sf::IntRect( 0, 0,tileSize,tileSize),
		sf::IntRect(48,16,tileSize,tileSize),
		sf::IntRect( 0,32,tileSize,tileSize)
		});
	Animation moveLeftAnim = Animation(3, 60, true, &sprite,
		{
		sf::IntRect(0 , 0,tileSize,tileSize),
		sf::IntRect(48, 0,tileSize,tileSize),
		sf::IntRect( 0,16,tileSize,tileSize)
		});
	Animation moveRightAnim = Animation(3, 60, true, &sprite,
		{
		sf::IntRect( 0, 0,tileSize,tileSize),
		sf::IntRect(16, 0,tileSize,tileSize),
		sf::IntRect(32, 0,tileSize,tileSize)
		});
	Animation deathAnim = Animation(12, 60, false, &sprite,
		{
		sf::IntRect( 0, 0,tileSize,tileSize),
		sf::IntRect(16,32,tileSize,tileSize),
		sf::IntRect(32,32,tileSize,tileSize),
		sf::IntRect(48,32,tileSize,tileSize),
		sf::IntRect( 0,48,tileSize,tileSize),
		sf::IntRect(16,48,tileSize,tileSize),
		sf::IntRect(32,48,tileSize,tileSize),
		sf::IntRect(48,48,tileSize,tileSize),
		sf::IntRect( 0,64,tileSize,tileSize),
		sf::IntRect(16,64,tileSize,tileSize),
		sf::IntRect(32,64,tileSize,tileSize),
		sf::IntRect(48,64,tileSize,tileSize),
		});

	animStateMachine.AddState("UP", moveUpAnim);
	animStateMachine.AddState("DOWN", moveDownAnim);
	animStateMachine.AddState("LEFT", moveLeftAnim);
	animStateMachine.AddState("RIGHT", moveRightAnim);
	animStateMachine.AddState("DEATH", deathAnim);
	currentAnimDirection = IDLE;
}

void Player::processEvents(sf::Event event)
{
	if (bIsDead)
		return;
	if (event.key.code == sf::Keyboard::Up)
	{
		SetNextDirection(UP);

	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		SetNextDirection(DOWN);

	}	
	else if (event.key.code == sf::Keyboard::Left)
	{
		SetNextDirection(LEFT);

	}
	else if (event.key.code == sf::Keyboard::Right)
	{
		SetNextDirection(RIGHT);
	}
	else if (event.key.code ==sf::Keyboard::Space)
	{
		Die();
	}
}

void Player::update(sf::Time deltaTime)
{
	AnimatedGridWalker::update(deltaTime);
	float elapsed = deltaTime.asSeconds();
	Move(deltaTime);
	sprite.setPosition(CalculateSpritePosition());
}

void Player::UpdateAnimation(sf::Time deltaTime)
{
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

bool Player::IsIntersectionValid(Intersection * intersectionToCheck)
{
	return true;
}

