#include "playerCollider.h"
#include "player.h"
#include <iostream>
PlayerCollider::PlayerCollider()
{
}

void PlayerCollider::OnCollisionEnter(Collider other)
{
	owner->direction = IDLE;
}
