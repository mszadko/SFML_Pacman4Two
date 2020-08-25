#pragma once
#include "gridWalker.h"
#include "SFML/Graphics.hpp"
#include "animationStateMachine.h"
#include <string>

class Intersection;

/** Class made for players and ghosts representation.
*  It combines possibilities of GridWalker and sf::Drawable.
* 	It handles animations via AnimationStateMachine class.
*/
class AnimatedGridWalker:public GridWalker,public sf::Drawable
{
public:
	/** Constructor
     *  Constructor that takes all needed information as parameters.
     * 	Some of the parameters are then passed to GridWalker.
     */
	AnimatedGridWalker(sf::Vector2f startPosition, Intersection* currentIntersection,std::string textureFileDestination, float speed = 100.0f);
	/** Sprite with shape and texture.
     * 	It displays game object shape and is animated by AnimationStateMachine.
     */
	sf::Sprite sprite;
	/** Texture with tileset.
     *  It is used to create 2d animation by switching proper tiles to create motion picture effect.
     */
	sf::Texture tileset;
	/**AnimationStateMachine class is responsible for caching and switching different animations. 
     */
	AnimationStateMachine animStateMachine;
	/** Core function of all game objects.
     *  It is called every frame to update state of the object.
     *  deltaTime parameter is time elapsed from previous update.
     */
	virtual void update(sf::Time deltaTime);
protected:
	/** Virtual method that needs to be overriden to change animation states.
	 *  It is called every frame.
     */
	virtual void UpdateAnimation(sf::Time deltaTime);
	/** It is used to draw pixel perfect sprites.
     *  Gameobject movement is float based. We want to draw sprites at discrete range of pixels.
     *  It is virtual so you can easly scale your sprites and adjust this function properly.
     */
	virtual sf::Vector2f CalculateSpritePosition();
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
