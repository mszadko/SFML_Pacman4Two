#include "ghost.h"
#include "intersection.h"
#include <iostream>
#include "player.h"
#include "sharedEnumerations.h"

Ghost::Ghost(sf::Vector2f startPosition, Intersection * currentIntersection, GhostType type, float speed)
	: AnimatedGridWalker(startPosition, currentIntersection, "Textures/ghostsspritesheet.png", speed)
{
	this->type = type;
	bIsOnPatrol = true;
	bIsReturningToBase = false;
	bIsTurnedOn = false;
	frightenedState = NOTFRIGHTENED;
	milisecondsElapsedFromTargetSwitch = 0;
	milisecondsElapsedDuringBeingFrightened = 0;

	switch (type)
	{
	case RED:
		patrolPoint = sf::Vector2f(ftileSize, ftileSize);
		break;
	case PINK:
		patrolPoint = sf::Vector2f((mapWidth-1)*ftileSize, ftileSize);
		break;
	case BLUE:
		patrolPoint = sf::Vector2f(ftileSize, (mapHeight - 1)* ftileSize);
		break;
	case ORANGE:
		patrolPoint = sf::Vector2f((mapWidth - 1)*ftileSize, (mapHeight - 1)* ftileSize);
		break;
	default:
		break;
	}
	Animation chaseUpAnim = Animation(2, 60, true, &sprite,
		{
		sf::IntRect( 4* tileSize,tileSize*type,tileSize,tileSize),
		sf::IntRect( 5* tileSize,tileSize*type,tileSize,tileSize)
		});
	Animation chaseDownAnim = Animation(2, 60, true, &sprite,
		{
		sf::IntRect(6 * tileSize,tileSize*type,tileSize,tileSize),
		sf::IntRect(7 * tileSize,tileSize*type,tileSize,tileSize)

		});
	Animation chaseLeftAnim = Animation(2, 60, true, &sprite,
		{
		sf::IntRect(2 * tileSize,tileSize*type,tileSize,tileSize),
		sf::IntRect(3 * tileSize,tileSize*type,tileSize,tileSize)

		});
	Animation chaseRightAnim = Animation(2, 60, true, &sprite,
		{
		sf::IntRect(0 * tileSize,tileSize*type,tileSize,tileSize),
		sf::IntRect(1 * tileSize,tileSize*type,tileSize,tileSize)
		});
	Animation runAwayAnim = Animation(2, 60, true, &sprite,
		{
		sf::IntRect(0 * tileSize,tileSize*4,tileSize,tileSize),
		sf::IntRect(1 * tileSize,tileSize*4,tileSize,tileSize)
		});
	Animation runAwayFlashingAnim = Animation(4, 60, true, &sprite,
		{
		sf::IntRect(0 * tileSize,tileSize * 4,tileSize,tileSize),
		sf::IntRect(1 * tileSize,tileSize * 4,tileSize,tileSize),
		sf::IntRect(2 * tileSize,tileSize * 4,tileSize,tileSize),
		sf::IntRect(3 * tileSize,tileSize * 4,tileSize,tileSize)
		});
	Animation returnToBaseRight = Animation(1, 60, false, &sprite,
		{
		sf::IntRect(4 * tileSize,tileSize * 4,tileSize,tileSize),
		});
	Animation returnToBaseLeft = Animation(1, 60, false, &sprite,
		{
		sf::IntRect(5 * tileSize,tileSize * 4,tileSize,tileSize),
		});
	Animation returnToBaseUp = Animation(1, 60, false, &sprite,
		{
		sf::IntRect(6 * tileSize,tileSize * 4,tileSize,tileSize),
		});
	Animation returnToBaseDown = Animation(1, 60, false, &sprite,
		{
		sf::IntRect(7 * tileSize,tileSize * 4,tileSize,tileSize),
		});
	animStateMachine.AddState("CHASEUP", chaseUpAnim);
	animStateMachine.AddState("CHASEDOWN", chaseDownAnim);
	animStateMachine.AddState("CHASELEFT", chaseLeftAnim);
	animStateMachine.AddState("CHASERIGHT", chaseRightAnim);
	animStateMachine.AddState("RUNAWAY", runAwayAnim);
	animStateMachine.AddState("RUNAWAYFLASH", runAwayFlashingAnim);
	animStateMachine.AddState("RETURNUP", returnToBaseUp);
	animStateMachine.AddState("RETURNDOWN", returnToBaseDown);
	animStateMachine.AddState("RETURNLEFT", returnToBaseLeft);
	animStateMachine.AddState("RETURNRIGHT", returnToBaseRight);
	currentAnimDirection = IDLE;
	SetNextDirection(DOWN);
}

void Ghost::update(sf::Time deltaTime)
{
	if (!bIsTurnedOn)
	{
		milisecondsElapsedDuringBeingTurnedOff += deltaTime.asMilliseconds();
		UpdateTurnedOffMode();
		return;
	}

	milisecondsElapsedFromTargetSwitch += deltaTime.asMilliseconds();
	if (frightenedState)
	{
		milisecondsElapsedDuringBeingFrightened += deltaTime.asMilliseconds();
		UpdateFrightenedMode();
	}
		
	AnimatedGridWalker::update(deltaTime);
	Move(deltaTime);
	sprite.setPosition(CalculateSpritePosition());
	FindNextDirection();
	TogglePatrolMode();
	if (bIsReturningToBase)
	{
		if (VectorDifferenceMagnitue(getPosition(), respawnLocation) < 1)
		{
			bIsReturningToBase = false;
		}
	}
}

void Ghost::UpdateAnimation(sf::Time deltaTime)
{
	if (frightenedState)
	{
		currentAnimDirection = IDLE;
		switch (frightenedState)
		{
		case FRIGHTENED:
			animStateMachine.PlayState("RUNAWAY");
			break;
		case FRIGHTENEDENDING:
			animStateMachine.PlayState("RUNAWAYFLASH");
			break;
		default:
			break;
		}
	}
	else if (currentAnimDirection != direction)
	{
		currentAnimDirection = direction;

		switch (direction)
		{
		case UP:
			animStateMachine.PlayState(bIsReturningToBase?"RETURNUP": "CHASEUP");
			break;
		case DOWN:
			animStateMachine.PlayState(bIsReturningToBase ? "RETURNDOWN" : "CHASEDOWN");
			break;
		case LEFT:
			animStateMachine.PlayState(bIsReturningToBase ? "RETURNLEFT" : "CHASELEFT");
			break;
		case RIGHT:
			animStateMachine.PlayState(bIsReturningToBase ? "RETURNRIGHT" : "CHASERIGHT");
			break;
		case IDLE:
			break;
		default:
			break;
		}
	}

	if (direction != IDLE)
	{
		animStateMachine.Update(deltaTime);
	}
}

bool Ghost::IsIntersectionValid(Intersection * intersectionToCheck)
{
	if (intersectionToCheck)
	{
		if ((intersectionToCheck->type & 16) == 16)
		{
			return false;
		}
		else if ((intersectionToCheck->type & 32)==32)
		{
			if (bIsReturningToBase)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void Ghost::FindNextDirection()
{
	if (targetIntersection)
	{
		int chosenIndex = 0;
		float minimalDist = 99999.0f;

		for (size_t i = 0; i < targetIntersection->neighbours.size(); i++)
		{
			if (previousIntersection != targetIntersection->neighbours[i])
			{
				if (!IsIntersectionValid(targetIntersection->neighbours[i]))
					continue;
				if (!player)
				{
					SetNextDirection(targetIntersection->directions[i]);
					break;
				}
				else
				{
					sf::Vector2f targetPosition = (bIsOnPatrol||frightenedState) ? patrolPoint : player->getPosition();
					targetPosition = bIsReturningToBase ? respawnLocation : targetPosition;
					sf::Vector2f intersectionPos = sf::Vector2f(targetIntersection->neighbours[i]->intersectionPosition.x*ftileSize, targetIntersection->neighbours[i]->intersectionPosition.y*ftileSize);
					sf::Vector2f difference = targetPosition - intersectionPos;
					float dist = sqrt(pow(difference.x, 2) + pow(difference.y, 2));
					if (minimalDist>dist)
					{
						minimalDist = dist;
						chosenIndex = i;
					} 
				}
			}
		}
		SetNextDirection(targetIntersection->directions[chosenIndex]);
	}
}

void Ghost::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (bIsTurnedOn)
	{
		target.draw(sprite, states);
	}
}

void Ghost::TogglePatrolMode()
{
	if (bIsOnPatrol)
	{
		if (milisecondsElapsedFromTargetSwitch>patrolTime)
		{
			bIsOnPatrol = false;
			milisecondsElapsedFromTargetSwitch = 0;
		}
	}
	else
	{
		if (milisecondsElapsedFromTargetSwitch>chasingTime)
		{
			bIsOnPatrol = true;
			milisecondsElapsedFromTargetSwitch = 0;
		}
	}
}

void Ghost::SwitchFrightenedMode(GhostFrightenedState NewIsFrightened)
{
	if (bIsReturningToBase)
	{
		return;
	}
	if (NewIsFrightened==NOTFRIGHTENED||NewIsFrightened==FRIGHTENED)
	{
		milisecondsElapsedDuringBeingFrightened = 0;
	}
	frightenedState = NewIsFrightened;
}

bool Ghost::IsFrightened()
{
	return frightenedState;
}

bool Ghost::IsDead()
{
	return bIsReturningToBase;
}

void Ghost::Die()
{
	SwitchFrightenedMode(NOTFRIGHTENED);
	bIsReturningToBase = true;
}

void Ghost::Restart()
{
	bIsOnPatrol = true;
	bIsReturningToBase = false;
	bIsTurnedOn = false;
	frightenedState = NOTFRIGHTENED;
	milisecondsElapsedFromTargetSwitch = 0;
	milisecondsElapsedDuringBeingFrightened = 0;
	ResetMovement();
	SetNextDirection(DOWN);
}

void Ghost::UpdateFrightenedMode()
{
	if (frightenedState)
	{
		if (milisecondsElapsedDuringBeingFrightened > frightenedTime + frightenedEndingTime)
			SwitchFrightenedMode(NOTFRIGHTENED);
		else if (milisecondsElapsedDuringBeingFrightened > frightenedTime)
			SwitchFrightenedMode(FRIGHTENEDENDING);
	}
}

void Ghost::UpdateTurnedOffMode()
{
	if (milisecondsElapsedDuringBeingTurnedOff>type*turnedOffTime)
	{
		bIsTurnedOn = true;
		milisecondsElapsedDuringBeingTurnedOff = 0;
	}
}

