#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/** Class responsible for single animation in animation state machine.
*  Animations are used by animation state machine. They got basic motion picture capabilities like playing, looping and stopping.
*/
class Animation
{
public:
	/**Construcor
     * Constructor that takes all needed information as parameters.
     */
	Animation(int numberOfFrames, int frameTimeInMs,bool bShouldLoop, sf::Sprite* spriteToUpdate, std::vector<sf::IntRect>frameset);
	/** Core function of all game objects.
	*  It is called every frame to update state of the object.
	*  deltaTime parameter is time elapsed from previous update.
	*/
	void Update(sf::Time deltaTime);
	/**Play method
	 * It is used by animation state machine to play current animation. You can choose if you want to play from
	 * beginning or play where it ended.
	 */
	void Play(bool bPlayFromBeginning);
	/**Stop
	 * Stops updating of animation frames.
	 */
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
	/**
     * 
     */
