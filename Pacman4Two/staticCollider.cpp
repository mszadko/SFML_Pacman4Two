#include "staticCollider.h"

#include <iostream>

StaticCollider::StaticCollider()
{
	collisionType = CollisionType::StaticCollisionType;
}


void StaticCollider::OnCollisionEnter(Collider other)
{
	//its a wall so we leave it empty;
}

