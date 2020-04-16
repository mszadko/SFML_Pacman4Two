#include "collisionManager.h"

CollisionManager::CollisionManager()
{
	colliders.clear();
}

CollisionManager & CollisionManager::GetCollisionManager()
{
	static CollisionManager instance;
	return instance;
}

void CollisionManager::Tick()
{
	for (size_t i = 0; i < colliders.size(); i++)
	{
		for (size_t j = i+1; j < colliders.size(); j++)
		{
			if (i != j)
			{
				if (colliders[i]->bounds.intersects(colliders[j]->bounds))
				{
					colliders[i]->OnCollisionEnter(*colliders[j]);
					colliders[j]->OnCollisionEnter(*colliders[i]);
				}
			}
		}
	}
}

void CollisionManager::RegisterCollider(Collider * toRegister)
{
	if (toRegister)
	{
		colliders.push_back(toRegister);
	}
}


