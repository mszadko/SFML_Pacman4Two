#pragma once
#include "animationStateMachine.h"
#include "animation.h"
#include <map>
#include <string>

/**Animation state machine is responsible for playing
 * and handling all ingame animations.
 */
class AnimationStateMachine
{
public:
	/** Core function of all game objects.
	*  It is called every frame to update state of the object.
	*  deltaTime parameter is time elapsed from previous update.
	*/
	void Update(sf::Time deltaTime);
	/**Adds animation state to state machine.
	 * After calling that function you can later play that animation
	 * by calling PlayState with same stateName you passed here.
	 */
	void AddState(std::string stateName, Animation animationToAdd);
	/**Tries to play animation at given state name.
	 */
	void PlayState(std::string newState,bool bPlayFromStart=false);
	/**Returns currently played state in animation state machine.
	 */
	std::string GetCurrentState();
private:
	std::string currentState;
	std::map<std::string, Animation> stateMap;
};
