#include "player.h"
#include <iostream>
#include <math.h>

Player::Player(sf::Vector2f startPosition, Intersection* currentIntersection, float speed)
	: GridWalker(currentIntersection, speed)
{
	setPosition(startPosition);
	tileset.loadFromFile("Textures/pacmanspritesheet.png");
	playerSprite.setTexture(tileset);
	playerSprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
	playerSprite.setScale(sf::Vector2f(1.5f, 1.5f));
	playerSprite.setPosition(CalculateSpritePosition(startPosition));
	
	Animation moveUpAnim = Animation(3, 100, true, &playerSprite,
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

bool Player::IsIntersectionValid(Intersection * intersectionToCheck)
{
	return true;
}

