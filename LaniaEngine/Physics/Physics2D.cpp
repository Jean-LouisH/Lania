#include "Physics2D.hpp"
#include <Constants.hpp>

void Lania::Physics2D::detectCollisions(
	Entity2D* entities, 
	BoxCollider2D* boxColliders, 
	int boxColliderCount)
{
	for (int i = 0; i < boxColliderCount; i++)
	{
		Vector2* position1 = &entities[boxColliders[i].entityID].transform.position_px;
		AABB2D* aabb1 = &boxColliders[i].aabb;

		for (int j = 0; j < boxColliderCount; j++)
		{
			if (i != j)
			{
				Vector2* position2 = &entities[boxColliders[j].entityID].transform.position_px;
				AABB2D* aabb2 = &boxColliders[j].aabb;

				double r1left = position1->x - (aabb1->max_px.x / 2.0);
				double r1right = position1->x + (aabb1->max_px.x / 2.0);
				double r1top = position1->y + (aabb1->max_px.y / 2.0);
				double r1bottom = position1->y - (aabb1->max_px.y / 2.0);

				double r2left = position2->x - (aabb2->max_px.x / 2.0);
				double r2right = position2->x + (aabb2->max_px.x / 2.0);
				double r2top = position2->y + (aabb2->max_px.y / 2.0);
				double r2bottom = position2->y - (aabb2->max_px.y / 2.0);

				if (!(r2left > r1right
					|| r2right < r1left
					|| r2top < r1bottom
					|| r2bottom > r1top))
				{
					;
				}
			}
		}
	}
}

void Lania::Physics2D::gravitate(
	RigidBody2D* rigidBodies, 
	int rigidBodyCount)
{
	for (int i = 0; i < rigidBodyCount; i++)
	{
		rigidBodies[i].velocity_px_per_s.y -= 
			EARTH_GRAVITY * S_PER_UPDATE * rigidBodies[i].gravity_scale;
	}
}

void Lania::Physics2D::displace(
	Entity2D* entities,
	RigidBody2D* rigidBodies,
	int rigidBodyCount)
{
	for (int i = 0; i < rigidBodyCount; i++)
	{
		RigidBody2D* rigidBody = &rigidBodies[i];
		entities[rigidBody->entityID].transform.position_px.x +=
			rigidBody->velocity_px_per_s.x * S_PER_UPDATE;
		entities[rigidBody->entityID].transform.position_px.y +=
			rigidBody->velocity_px_per_s.y * S_PER_UPDATE;
	}
}

void Lania::Physics2D::lock(
	Entity2D* entities,
	PointLock2D* pointLocks,
	int pointLockCount)
{
	for (int i = 0; i < pointLockCount; i++)
	{
		PointLock2D* pointLock = &pointLocks[i];
		entities[pointLock->entityID].transform.position_px.x =
			pointLock->point.x;
		entities[pointLock->entityID].transform.position_px.y =
			pointLock->point.y;
	}
}