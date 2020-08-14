#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Animation
{
public:
	Animation(int numberOfFrames, int frameTimeInMs,bool bShouldLoop, sf::Sprite* spriteToUpdate, std::vector<sf::IntRect>frameset);
	void Update(sf::Time deltaTime);
	void Play(bool bPlayFromBeginning);
	void Stop();
private:
	bool bShouldLoop;
	int numberOfFrames;
	int frameTimeInMs;
	sf::Sprite* spriteToUpdate;
	std::vector<sf::IntRect> frameset;

	bool bIsPlaying;
	int currentFrame;
	int elapsedTimeOnCurrentFrame;
};
