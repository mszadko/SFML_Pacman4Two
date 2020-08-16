#pragma once
#include "animationStateMachine.h"
#include "animation.h"
#include <map>
#include <string>


class AnimationStateMachine
{
public:
	void Update(sf::Time deltaTime);
	void AddState(std::string stateName, Animation animationToAdd);
	void PlayState(std::string newState,bool bPlayFromStart=false);
	std::string GetCurrentState();
private:
	std::string currentState;
	std::map<std::string, Animation> stateMap;
};