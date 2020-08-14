#include "animation.h"
#include <iostream>
Animation::Animation(int numberOfFrames, int frameTimeInMs, bool bShouldLoop, sf::Sprite* spriteToUpdate, std::vector<sf::IntRect> frameset)
{
	this->numberOfFrames = numberOfFrames;
	this->frameTimeInMs = frameTimeInMs;
	this->bShouldLoop = bShouldLoop;
	this->spriteToUpdate = spriteToUpdate;
	this->frameset = frameset;
	
	bIsPlaying = false;
	currentFrame = 0;
	elapsedTimeOnCurrentFrame = 0;
}

void Animation::Update(sf::Time deltaTime)
{
	if (!bIsPlaying)
		return;
	
	elapsedTimeOnCurrentFrame += deltaTime.asMilliseconds();
	if (elapsedTimeOnCurrentFrame >frameTimeInMs)
	{
		elapsedTimeOnCurrentFrame = 0;
		
		if (bShouldLoop)
		{
			currentFrame++;
			currentFrame %= numberOfFrames;
		}
		else if (currentFrame<numberOfFrames-1)
		{
			currentFrame++;
		}
		
		if (spriteToUpdate)
		{
			spriteToUpdate->setTextureRect(frameset[currentFrame]);
		}
	}
}

void Animation::Play(bool bPlayFromBeginning)
{
	bIsPlaying = true;
	if (bPlayFromBeginning)
	{
		currentFrame = 0;
		elapsedTimeOnCurrentFrame = 0;
	}
}

void Animation::Stop()
{
	bIsPlaying = false;
}
