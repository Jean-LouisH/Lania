#include "Physics2D.hpp"
#include <Constants.hpp>

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