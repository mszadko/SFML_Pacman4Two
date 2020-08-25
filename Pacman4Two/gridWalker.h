#pragma once
#include "sharedEnumerations.h"
#include <SFML/Graphics.hpp>
class Intersection;
/**Class responsible for intersection based movement. It is used for pacman players and chasing ghosts.
 */
class GridWalker : public sf::Transformable
{
public:
	/**Construcor
     * Constructor that takes all needed information as parameters.
     */
	GridWalker(sf::Vector2f startPosition,Intersection* currentIntersection,float speed = 100.0f);
	/**Move is most important function of GridWalker class
	 * It handles intersection to intersection based movement.
	 */
	void Move(sf::Time deltaTime);
	/**Set next direction function
	 * is used to tell grid walker where to turn on next intersection.
	 */
	void SetNextDirection(Direction newDirection);
	/**Helper function 
	 * that transform grid walker actual position to level coordinates.
	 */
	sf::Vector2i PositionToMapCoord();
	/**Used for correct position that came as packet from the server.
	 * Actual grid walker info is stored on server. If data displayed on the client is different that
	 * one on the server this method teleports grid walker on proper position.
	 */
	void CorrectPosition(sf::Vector2f correctedPosition, Direction newDir, Intersection* newTargetIntersection);
protected:
	/** Virtual method to check if intersection is valid.
	 *  Intersections on level got different types. You can add new types and then
	 *  allow or forbid some classes to use them easily.
	 */
	virtual bool IsIntersectionValid(Intersection* intersectionToCheck);
	/**Direction
	 * Direction in grid walker is currently moving.
	 */
	Direction direction;
	/**Intersection
	 * needed to process intersection to intersection based movement.
	 */
	Intersection* currentIntersection;
	/**Intersection
	 * needed to process intersection to intersection based movement.
	 */
	Intersection* previousIntersection;
	/**Intersection
	 * needed to process intersection to intersection based movement.
	 */
	Intersection* targetIntersection;
	/**Next direction
	 * is used to store next direction we want to try to go to at next intersection.
	 */
	Direction nextDirection;
	/**Resets all movement data
	 * and teleports grid walker to the intersection it started from.
	 */
	void ResetMovement();
	/**Virtual method called from move method.
	 * It is called every time grid walker goes too far in some direction and cross past intersection
	 */
	virtual void OnTargetOvershot();
	/**Respawn location
	 * used to store information where grid walker started game.
	 */
	sf::Vector2f respawnLocation;
	/**Respawn intersection
	 * It is used to store infromation where grid walker started game.
	 */
	Intersection* respawnIntersection;
private:
	Intersection* FindIntersectionInDirection(Direction direction);
	void SwapDirection();
	bool OvershotTarget();
	float DistanceFromPreviousNode(sf::Vector2f targetPosition);
	sf::Vector2f DirectionToVector(Direction direction);

	float speed;	
};
