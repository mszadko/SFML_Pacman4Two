#pragma once
#include <vector>
#include "collider.h"

class CollisionManager
{
public:
	static CollisionManager& GetCollisionManager();
	void Tick();
	void RegisterCollider(Collider* toRegister);
private:
	CollisionManager();
	std::vector<Collider*> colliders;

public:
	//unwanted methods (they can mess with our singleton pattern)
	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;
};