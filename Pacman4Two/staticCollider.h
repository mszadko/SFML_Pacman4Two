#pragma once
#include "collider.h"

class StaticCollider : public Collider
{
public:
	StaticCollider();

	void OnCollisionEnter(Collider other) override;
};