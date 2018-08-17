#include "Physics2D.hpp"
#include <math.h>
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

				double box1left = position1->x + aabb1->min_px.x;
				double box1right = position1->x + aabb1->max_px.x;
				double box1top = position1->y + aabb1->max_px.y;
				double box1bottom = position1->y + aabb1->min_px.y;

				double box2left = position2->x + aabb2->min_px.x;
				double box2right = position2->x + aabb2->max_px.x;
				double box2top = position2->y + aabb2->max_px.y;
				double box2bottom = position2->y + aabb2->min_px.y;

				if (!(box2left > box1right
					|| box2right < box1left
					|| box2top < box1bottom
					|| box2bottom > box1top))
				{
					;
				}
			}
		}
	}
}

void Lania::Physics2D::decelerate(
	RigidBody2D* rigidBodies,
	int rigidBodyCount)
{
	for (int i = 0; i < rigidBodyCount; i++)
	{
		double dragScale = pow(rigidBodies[i].drag_ratio.x, S_PER_UPDATE);
		rigidBodies[i].velocity_px_per_s.x *= dragScale;
		rigidBodies[i].velocity_px_per_s.y *= dragScale;
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