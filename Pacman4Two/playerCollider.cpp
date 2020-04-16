#include "playerCollider.h"
#include "player.h"
#include <iostream>
PlayerCollider::PlayerCollider()
{
}

void PlayerCollider::OnCollisionEnter(Collider other)
{
	std::cout << "player collided\n\n\n";
	owner->direction = IDLE;
}
