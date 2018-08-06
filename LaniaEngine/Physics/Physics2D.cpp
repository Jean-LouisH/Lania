#include "Physics2D.hpp"
#include <Constants.hpp>

void Lania::Physics2D::detectCollisions(List<Scene2D>* scene2Ds)
{
	int scene2DCount = scene2Ds->size();
	for (int i = 0; i < scene2DCount; i++)
	{
		Scene2D* scene2D = &scene2Ds->at(i);
		Entity2D* entities = scene2D->entities.data();
		BoxCollider2D* boxColliders = scene2D->activeBoxColliders.data();

		int boxColliderCount = scene2D->activeBoxColliders.size();
		for (int j = 0; j < boxColliderCount; j++)
		{
			Vector2* position1 = &entities[boxColliders[j].entityID].transform.position_px;
			AABB2D* aabb1 = &boxColliders[j].aabb;

			for (int k = 0; k < boxColliderCount; k++)
			{
				if (j != k)
				{
					Vector2* position2 = &entities[boxColliders[k].entityID].transform.position_px;
					AABB2D* aabb2 = &boxColliders[k].aabb;

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
}

void Lania::Physics2D::gravitate(List<Scene2D>* scene2Ds)
{
	int scene2DCount = scene2Ds->size();
	for (int i = 0; i < scene2DCount; i++)
	{
		Scene2D* scene2D = &scene2Ds->at(i);
		RigidBody2D* rigidBodies = scene2D->activeRigidBodies.data();

		int rigidBodyCount = scene2D->activeRigidBodies.size();
		for (int j = 0; j < rigidBodyCount; j++)
		{
			rigidBodies[j].velocity_px_per_s.y -= 
				EARTH_GRAVITY * S_PER_UPDATE * rigidBodies[j].gravity_scale;
		}
	}
}

void Lania::Physics2D::displace(List<Scene2D>* scene2Ds)
{
	int scene2DCount = scene2Ds->size();
	for (int i = 0; i < scene2DCount; i++)
	{
		Scene2D* scene2D = &scene2Ds->at(i);
		Entity2D* entities = scene2D->entities.data();
		RigidBody2D* rigidBodies = scene2D->activeRigidBodies.data();

		int rigidBodyCount = scene2D->activeRigidBodies.size();
		for (int j = 0; j < rigidBodyCount; j++)
		{
			RigidBody2D* rigidBody = &rigidBodies[j];
			entities[rigidBody->entityID].transform.position_px.x +=
				rigidBody->velocity_px_per_s.x * S_PER_UPDATE;
			entities[rigidBody->entityID].transform.position_px.y +=
				rigidBody->velocity_px_per_s.y * S_PER_UPDATE;
		}
	}
}

void Lania::Physics2D::lock(List<Scene2D>* scene2Ds)
{
	int scene2DCount = scene2Ds->size();
	for (int i = 0; i < scene2DCount; i++)
	{
		Scene2D* scene2D = &scene2Ds->at(i);
		Entity2D* entities = scene2D->entities.data();
		PointLock2D* pointLocks = scene2D->pointLocks.data();

		int pointLockCount = scene2D->pointLocks.size();
		for (int j = 0; j < pointLockCount; j++)
		{
			PointLock2D* pointLock = &pointLocks[j];
			entities[pointLock->entityID].transform.position_px.x =
				pointLock->point.x;
			entities[pointLock->entityID].transform.position_px.y =
				pointLock->point.y;
		}
	}
}