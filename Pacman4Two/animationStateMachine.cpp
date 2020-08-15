#include "animationStateMachine.h"
#include <iostream>


void AnimationStateMachine::Update(sf::Time deltaTime)
{	
	try
	{
		Animation& animAtCurrentState = stateMap.at(currentState);
		animAtCurrentState.Update(deltaTime);
	}
	catch (const std::exception&)
	{
		std::cout << "AnimationStateMachine error - There is no such state - " << currentState << std::endl;
	}
}

void AnimationStateMachine::AddState(std::string stateName, Animation animationToAdd)
{
	stateMap.insert(stateMap.begin(), std::pair<std::string, Animation>(stateName, animationToAdd));
}

void AnimationStateMachine::PlayState(std::string newState,bool bPlayFromStart)
{
	if (stateMap.find(newState)==stateMap.end())
		return;
	try
	{
		stateMap.at(currentState).Stop();
	}
	catch (const std::exception&)
	{

	}
	currentState = newState;
	try
	{
		stateMap.at(currentState).Play(bPlayFromStart);
	}
	catch (const std::exception&)
	{

	}
	
}
