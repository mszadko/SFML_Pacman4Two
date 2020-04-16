#pragma once
#include "collider.h"

class PlayerCollider :public Collider
{
public:
	PlayerCollider();

	void OnCollisionEnter(Collider other) override;

	class Player* owner;
};