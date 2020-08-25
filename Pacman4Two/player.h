#pragma once
#include <SFML/Graphics.hpp>
#include "intersection.h"
#include "animationStateMachine.h"
#include "sharedEnumerations.h"
#include "animatedGridWalker.h"
/**Class that abstracts pacman behavior.
 */
class Player :public AnimatedGridWalker
{
public:
	/**Construcor
     * Constructor that takes all needed information as parameters.
     * Some of that data is passed to AnimatedGridWalker constructor.
     */
	Player(sf::Vector2f startPosition, Intersection* currentIntersection,PlayerNumer playerNumber = PlayerNumer::FIRST,float speed = 100.0f);
	/**Processes key pressing in main game loop.
	 */
	void processEvents(sf::Event event);	
	/** Core function of all game objects.
	*  It is called every frame to update state of the object.
	*  deltaTime parameter is time elapsed from previous update.
	*/
	void update(sf::Time deltaTime);
	/**Kills player.
	 */
	void Die();
	/**Restores default values and move player back to the level start.
	 */
	void Restart();
	/**Returns whether player is dead or alive.
	 */
	bool IsDead();
protected:
	/**Used to check it this class can use some special intersections. See GridWalker for more information.
	 */
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	/**Used to update animation. See AnimatedGridWalker and AnimationStateMachine for more information.
	 */
	virtual void UpdateAnimation(sf::Time deltaTime);
	/**Calls RPC-like method to update client's view to match server view.
	 */
	virtual void OnTargetOvershot();
private:	
	bool bIsDead;
	Direction currentAnimDirection;
	PlayerNumer playerNumber;
};
