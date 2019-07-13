#include "Physics.hpp"
#include "Physics2D.hpp"
#include <Utilities/Definitions/Constants.hpp>

void Lania::Physics::compute(
	List<Scene2D>* subScene2Ds,
	double simulation_ms)
{
	int subScene2DCount = subScene2Ds->size();

	for (int i = 0; i < subScene2DCount; i++)
	{
		Scene2D* subScene2D = &subScene2Ds->at(i);
		Entity2D* entities = subScene2D->entities.data();

		BoxCollider2D* boxColliders = subScene2D->activeBoxColliders.data();
		RigidBody2D* rigidBodies = subScene2D->activeRigidBodies.data();
		PositionLock2D* positionLocks = subScene2D->pointLocks.data();

		int boxColliderCount = subScene2D->activeBoxColliders.size();
		int rigidBodyCount = subScene2D->activeRigidBodies.size();
		int positionLockCount = subScene2D->pointLocks.size();

		Physics2D::detectCollisions(
			simulation_ms,
			&subScene2D->dynamicCollisionEvents,
			&subScene2D->staticCollisionEvents,
			entities,
			rigidBodies,
			rigidBodyCount,
			boxColliders,
			boxColliderCount);

		DynamicCollisionEvent2D* dynamicCollisionEvents = subScene2D->dynamicCollisionEvents.data();
		int DynamicCollisionEventCount = subScene2D->dynamicCollisionEvents.size();

		Physics2D::handleCollisions(dynamicCollisionEvents, DynamicCollisionEventCount, rigidBodies);
		Physics2D::decelerate(rigidBodies, rigidBodyCount);
		Physics2D::gravitate(rigidBodies, rigidBodyCount);
		Physics2D::displace(entities, rigidBodies, rigidBodyCount);
		Physics2D::lockTranslation(entities, positionLocks, positionLockCount);
	}
}