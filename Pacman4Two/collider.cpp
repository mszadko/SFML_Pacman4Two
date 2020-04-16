#include "collider.h"
#include "collisionManager.h"
#include <iostream>

Collider::Collider(sf::FloatRect bounds)
{
	collisionType = CollisionType::StaticCollisionType;
	this->bounds = bounds;
	CollisionManager::GetCollisionManager().RegisterCollider(this);
}

void Collider::OnCollisionEnter(Collider other)
{
	//std::cout << "basic collisiong\n";
}
