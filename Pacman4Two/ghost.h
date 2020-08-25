#pragma once
#include "animatedGridWalker.h"

class Player;
/**Class that abstracts ghots that chases the player across the level.
 */
class Ghost:public AnimatedGridWalker
{
public:
	/**Construcor
     * Constructor that takes all needed information as parameters.
     */
	Ghost(sf::Vector2f startPosition, Intersection* currentIntersection,GhostType type,float speed);
	/** Core function of all game objects.
	*  It is called every frame to update state of the object.
	*  deltaTime parameter is time elapsed from previous update.
	*/
	void update(sf::Time deltaTime);
	/**Ghost type
	 * type of ghost. Used to change respawn order and some behaviour differences.
	 */
	GhostType type;
	/**Vector with all players on the map
	 * It is used by other methods to chase the closest player.
	 */
	std::vector<Player*> players;
	/**Swiches ghost behaviour and animation states from normal behaviour to frightened state.
	 */
	void SwitchFrightenedMode(GhostFrightenedState NewIsFrightened);
	/**Returns wheter ghost is frightened or not.
	 */
	bool IsFrightened();
	/**Returns wheter ghost is dead or not.
	 */
	bool IsDead();
	/**Kills ghost. Sets proper animation and make him go back to the respawn base.
	 */
	void Die();
	/**Restart ghost state to default values.
	 */
	void Restart();
protected:
	/**Used to update animation. See AnimatedGridWalker and AnimationStateMachine for more information.
	 */
	virtual void UpdateAnimation(sf::Time deltaTime);
	/**Used to check it this class can use some special intersections. See GridWalker for more information.
	 */
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	/**Calls RPC-like method to update client's view to match server view.
	 */
	virtual void OnTargetOvershot();
	/**Looks for closest intersection to search target. It may be player or some other place like respawn base when ghost is dead.
	 */
	Direction FindNextDirection();
	/**Used to update ghost behaviour and animation.
	 */
	GhostFrightenedState frightenedState;
	/**Used to update ghost behaviour and animation.
	 */
	bool bIsReturningToBase;
	/**Used to update ghost behaviour.
	 */
	bool bIsOnPatrol;
	/**When bIsOnPatrol is set ghost moves toward this point instead of chasing player.
	 */
	sf::Vector2f patrolPoint;
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void TogglePatrolMode();
	void UpdateFrightenedMode();
	void UpdateTurnedOffMode();
	bool IsTherePlayerToChase();
	Player* GetClosestPlayer();
	Direction currentAnimDirection;
	int milisecondsElapsedFromTargetSwitch;
	int milisecondsElapsedDuringBeingFrightened;
	const int patrolTime = 5000;
	const int chasingTime = 30000;
	const int frightenedTime = 6500;
	const int frightenedEndingTime = 3000;
	const int turnedOffTime = 2000;
	bool bIsTurnedOn;
	int milisecondsElapsedDuringBeingTurnedOff;
};
