#include "Scene.hpp"
#include "2D/Entity2D.hpp"

Lania::Texture Lania::Scene::loadTexture(String filepath)
{
	Texture texture;

	if (!this->textures.count(filepath))
	{

	}
	else
	{
		texture = this->textures.at(filepath);
	}

	return texture;
}

void Lania::Scene::deleteTexture(Lania::String filepath)
{

	this->textures.erase(filepath);
}

void Lania::Scene::deleteSound(Lania::String filepath)
{

}

void Lania::Scene::deleteAllTextures()
{
	if (!this->textures.empty())
	{
		for (const auto &pair : this->textures)
		{

		}
		this->textures.clear();
	}
}

void Lania::Scene::deleteAllSounds()
{

}

void Lania::Scene::deleteAssets()
{
	this->deleteAllTextures();
	this->deleteAllSounds();
}

void Lania::Scene::addScene2D()
{
	Scene2D scene2D;
	this->subscenes2D.push_back(scene2D);
}

void Lania::Scene::addEntity2D(LayerID subscene2DID)
{
	Entity2D entity2D;
	this->subscenes2D.at(subscene2DID).entities.push_back(entity2D);
}

void Lania::Scene::addEntity2D(LayerID subscene2DID, double x, double y)
{
	Entity2D entity2D;
	entity2D.transform.position_px.x = x;
	entity2D.transform.position_px.y = y;
	this->subscenes2D.at(subscene2DID).entities.push_back(entity2D);
}

void Lania::Scene::addEntity2D(LayerID scene2DID, double x, double y, double xScale, double yScale)
{
	Entity2D entity2D;
	entity2D.transform.position_px.x = x;
	entity2D.transform.position_px.y = y;
	entity2D.transform.scale.x = xScale;
	entity2D.transform.scale.y = yScale;
	this->subscenes2D.at(scene2DID).entities.push_back(entity2D);
}

void Lania::Scene::addCamera2D(LayerID scene2DID, EntityID entityID)
{
	Camera2D camera2D;
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	camera2D.viewport_px.width = this->windowCopy.width;
	camera2D.viewport_px.height = this->windowCopy.height;
	if (scene2D->activeCameras.size() < 1)
	{
		camera2D.current = true;
		scene2D->currentCameraIndex = 0;
	}
	camera2D.entityID = entityID;
	scene2D->activeCameras.push_back(camera2D);
	scene2D->entities.at(entityID).components.emplace(CAMERA_2D, scene2D->activeCameras.size() - 1);
}

void Lania::Scene::addSprite2D(LayerID scene2DID, EntityID entityID)
{
	Sprite2D sprite2D;
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	sprite2D.alpha = 255;
	sprite2D.entityID = entityID;
	scene2D->activeSprites.push_back(sprite2D);
	scene2D->entities.at(entityID).components.emplace(SPRITE_2D, scene2D->activeSprites.size() - 1);
}

void Lania::Scene::addBoxCollider2D(LayerID scene2DID, EntityID entityID, double xMin, double yMin, double xMax, double yMax)
{
	BoxCollider2D boxCollider2D;
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	boxCollider2D.aabb.min_px.x = xMin;
	boxCollider2D.aabb.min_px.y = yMin;
	boxCollider2D.aabb.max_px.x = xMax;
	boxCollider2D.aabb.max_px.y = yMax;
	boxCollider2D.entityID = entityID;
	scene2D->activeBoxColliders.push_back(boxCollider2D);
	scene2D->entities.at(entityID).components.emplace(BOX_COLLIDER_2D, scene2D->activeBoxColliders.size() - 1);
}

void Lania::Scene::addRigidBody2D(LayerID scene2DID, EntityID entityID)
{
	RigidBody2D rigidBody2D;
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	rigidBody2D.entityID = entityID;
	scene2D->activeRigidBodies.push_back(rigidBody2D);
	scene2D->entities.at(entityID).components.emplace(RIGID_BODY_2D, scene2D->activeRigidBodies.size() - 1);
}

void Lania::Scene::addPointLock2D(LayerID scene2DID, EntityID entityID, double x, double y)
{
	PointLock2D pointLock2D;
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	pointLock2D.point.x = x;
	pointLock2D.point.y = y;
	pointLock2D.entityID = entityID;
	scene2D->pointLocks.push_back(pointLock2D);
	scene2D->entities.at(entityID).components.emplace(POINT_LOCK_2D, scene2D->pointLocks.size() - 1);
}

void Lania::Scene::addSpriteTextureFrame(LayerID scene2DID, ComponentListIndex componentIndex, String filepath)
{
	Sprite2D* sprite2D = &this->subscenes2D.at(scene2DID).activeSprites.at(componentIndex);

}

void Lania::Scene::removeEntity2D(LayerID scene2DID, EntityID entityID)
{
	List<Entity2D>* entities = &this->subscenes2D.at(scene2DID).entities;
	entities->erase(entities->begin() + (entityID - 1));
}

void Lania::Scene::centreEntity2DToSprite(LayerID scene2DID, EntityID entityID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	scene2D->entities.at(entityID).transform.position_px.x = 
		scene2D->activeSprites.at(componentIndex).textureFrames.back().pixels.width / 2.0;
	scene2D->entities.at(entityID).transform.position_px.y =
		scene2D->activeSprites.at(componentIndex).textureFrames.back().pixels.height / 2.0;
}

void Lania::Scene::centreCurrentCamera2DToSprite(LayerID scene2DID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	Sprite2D* sprite2D = &scene2D->activeSprites.at(componentIndex);
	scene2D->entities.at(scene2D->activeCameras.at(scene2D->currentCameraIndex).entityID).transform.position_px.x = sprite2D->textureFrames.back().pixels.width / 2.0;
	scene2D->entities.at(scene2D->activeCameras.at(scene2D->currentCameraIndex).entityID).transform.position_px.y = sprite2D->textureFrames.back().pixels.height / 2.0;
	scene2D->activeCameras.at(scene2D->currentCameraIndex).viewport_px.width = sprite2D->textureFrames.back().pixels.width;
	scene2D->activeCameras.at(scene2D->currentCameraIndex).viewport_px.height = sprite2D->textureFrames.back().pixels.width / 1.777;
}

void Lania::Scene::flipSprite2D(LayerID scene2DID, ComponentListIndex componentIndex, bool flip)
{
	this->subscenes2D.at(scene2DID).activeSprites.at(componentIndex).flip = flip;
}

void Lania::Scene::setCamera2DInactive(LayerID scene2DID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	List<Camera2D>* cameras = &scene2D->activeCameras;
	scene2D->inactiveCameras.push_back(cameras->at(componentIndex));
	cameras->erase(cameras->begin() + (componentIndex - 1));
}

void Lania::Scene::setRigidBody2DInactive(LayerID scene2DID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	List<RigidBody2D>* rigidBodies = &scene2D->activeRigidBodies;
	scene2D->inactiveRigidBodies.push_back(rigidBodies->at(componentIndex));
	rigidBodies->erase(rigidBodies->begin() + (componentIndex - 1));
}

void Lania::Scene::setSprite2DInactive(LayerID scene2DID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subscenes2D.at(scene2DID);
	List<Sprite2D>* sprites = &scene2D->activeSprites;
	scene2D->inactiveSprites.push_back(sprites->at(componentIndex));
	sprites->erase(sprites->begin() + (componentIndex - 1));
}

void Lania::Scene::addAudioSource2D(LayerID scene2DID, EntityID entityID, String filepath)
{

}