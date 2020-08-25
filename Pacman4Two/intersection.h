#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "sharedEnumerations.h"

/**Class responsible for intersection handling.
 * It stores neighbours and directions of the intersection.
 */
class Intersection
{
public:
	/**Neighbours
	 * are used to find closest intersection at given direction.
     */
	std::vector<Intersection*> neighbours;
	/**Directions
     * are used to determine if a grid walker can turn in that direction from current intersection.
     */
	std::vector<Direction> directions;
	/**Intersection position
     * is used to calculate distances between intersections.
     * It is stored as level coordinates.
     */
	sf::Vector2i intersectionPosition;
	/**Type of intersection.
	 * Int based bitmask type. Used for allowing or forbiding some classes to use that intersection.
	 * bitmask like int value that will allow to generate intersections
	 * 1 - means I can go UP    from that place
	 * 2 - means I can go DOWN
	 * 4 - means I can go LEFT
	 * 8 - means I can go RIGHT 
	 * 16 - means that only player can use that intersection
	 * 32 - means that only ghost that returns to base after being eaten can use it
	 * e.g. 5  - means we can go up and left
	 * 15 - means we can go in every direction
	 */
	int type = 0;
};
