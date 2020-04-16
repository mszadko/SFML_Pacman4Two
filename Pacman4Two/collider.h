#pragma once
#include <SFML/Graphics.hpp>

enum CollisionType
{
	StaticCollisionType,
	PlayerCollisionType,
	PickupCollisionType,
	EnemyCollisionType,
	TeleportCollisionType
};

class Collider
{
public:
	Collider(sf::FloatRect bounds = sf::FloatRect(0.f, 0.f, 0.f, 0.f));
	virtual void OnCollisionEnter(Collider other);
	CollisionType collisionType;
	sf::FloatRect bounds;
};