#include "Scene.hpp"
#include "2D/Entity2D.hpp"
#include <yaml-cpp/yaml.h>
#include <SDL_image.h>
#include <Utilities/Definitions/Constants.hpp>
#include <Core/FileSystem.hpp>
#include <Application/Scene/Assets/Model.hpp>

void Lania::Scene::load(String filePath)
{
	try
	{
		YAML::Node newScene = YAML::LoadFile(filePath);
		subScenes2D.clear();
		layerTypeList.clear();

		for (YAML::const_iterator it0 = newScene.begin(); it0 != newScene.end(); ++it0)
		{
			if (it0->first.as<std::string>() == "Layer2D")
			{
				if (this->subScenes2D.size() == 0)
					this->addScene2D();
				this->layerTypeList.push_back(SUBSCENE_2D);

				for (YAML::const_iterator it1 = it0->second.begin(); it1 != it0->second.end(); ++it1)
				{
					if (it1->first.as<std::string>() == "Entity2D")
					{
						String name = "";
						Transform2D transform;
						Vector<String> shaders2D;

						bool hasParent = false;
						String parentName;

						bool hasCamera2D = false;
						Vector2 cameraViewport_px;

						bool hasSprite2D = false;
						Vector<String> textureFrameFilePaths;

						bool hasRigidBody2D = false;
						bool hasBoxCollider2D = false;
						bool hasPointLock2D = false;

						for (YAML::const_iterator it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
						{
							if (it2->first.as<std::string>() == "name")
							{
								name = it2->second.as<std::string>();
							}
							else if (it2->first.as<std::string>() == "parent")
							{
								hasParent = true;
								parentName = it2->second.as<std::string>();
							}
							else if (it2->first.as<std::string>() == "position_px")
							{
								transform.position_px.x = it2->second[0].as<double>();
								transform.position_px.y = it2->second[1].as<double>();
							}
							else if (it2->first.as<std::string>() == "rotation_rad")
							{
								transform.rotation_rad = it2->second.as<double>();
							}
							else if (it2->first.as<std::string>() == "scale")
							{
								transform.scale.x = it2->second[0].as<double>();
								transform.scale.y = it2->second[1].as<double>();
							}
							else if (it2->first.as<std::string>() == "shader2D")
							{
								MemoryPoolU8 shaderContents = FileSystem::readString(this->dataFilePath + it2->second.as<std::string>());
								shaders2D.push_back((const char*) shaderContents.getData());
								shaderContents.deallocate();

							}
							else if (it2->first.as<std::string>() == "Camera2D")
							{
								hasCamera2D = true;
								for (YAML::const_iterator it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
								{
									if (it3->first.as<std::string>() == "viewport_px")
									{
										cameraViewport_px.x = it3->second[0].as<double>();
										cameraViewport_px.y = it3->second[1].as<double>();
									}
								}
							}
							else if (it2->first.as<std::string>() == "Sprite2D")
							{
								hasSprite2D = true;
								for (YAML::const_iterator it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
								{
									if (it3->first.as<std::string>() == "texture")
									{
										textureFrameFilePaths.push_back(it3->second.as<std::string>());
									}
								}
							}
							else if (it2->first.as<std::string>() == "RigidBody2D")
							{

							}
							else if (it2->first.as<std::string>() == "BoxCollider2D")
							{

							}
							else if (it2->first.as<std::string>() == "PointLock2D")
							{

							}
						}

						LayerID lastLayer = this->layerTypeList.size() - 1;

						this->addEntity2D(
							lastLayer,
							name, 
							transform.position_px.x, 
							transform.position_px.y, 
							transform.rotation_rad, 
							transform.scale.x, 
							transform.scale.y);

						Vector<Entity2D>* entities = &this->subScenes2D.at(lastLayer).entities;
						EntityID lastEntity = this->subScenes2D.at(lastLayer).entities.size() - 1;

						entities->at(lastEntity).shaders2D = shaders2D;

						if (hasParent)
						{
							this->addParentToEntity2D(lastLayer, lastEntity, parentName);
						}
						if (hasCamera2D)
						{
							this->addCamera2D(lastLayer, lastEntity);
						}
						if (hasSprite2D)
						{
							this->addSprite2D(lastLayer, lastEntity);
							for (int i = 0; i < textureFrameFilePaths.size(); i++)
								this->addSpriteTextureFrame(
									lastLayer,
									entities->at(lastEntity).components.at(Entity2D::components::SPRITE_2D), 
									this->dataFilePath + textureFrameFilePaths.at(i));
						}
					}
				}
			}
		}
	}
	catch (int e)
	{

	}
}

Lania::Texture Lania::Scene::loadTexture(String filePath)
{
	Texture texture;

	if (!this->textures.count(filePath))
	{
		texture.load(filePath);
	}
	else
	{
		texture = this->textures.at(filePath);
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
	this->subScenes2D.push_back(scene2D);
}

void Lania::Scene::addEntity2D(LayerID scene2DID, String name, double x, double y, double rotation, double xScale, double yScale)
{
	Entity2D entity2D;
	this->subScenes2D.at(scene2DID).entityNameRegistry.emplace(name, this->subScenes2D.at(scene2DID).entities.size());
	entity2D.transform.position_px.x = x;
	entity2D.transform.position_px.y = y;
	entity2D.transform.rotation_rad = rotation;
	entity2D.transform.scale.x = xScale;
	entity2D.transform.scale.y = yScale;
	this->subScenes2D.at(scene2DID).entities.push_back(entity2D);
}

void Lania::Scene::addCamera2D(LayerID scene2DID, EntityID entityID)
{
	Camera2D camera2D;
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	camera2D.viewport_px.width = this->windowDimensions.width;
	camera2D.viewport_px.height = this->windowDimensions.height;
	if (scene2D->activeCameras.size() < 1)
	{
		camera2D.current = true;
		scene2D->currentCameraIndex = 0;
	}
	camera2D.entityID = entityID;
	scene2D->activeCameras.push_back(camera2D);
	scene2D->entities.at(entityID).components.emplace(Entity2D::components::CAMERA_2D, scene2D->activeCameras.size() - 1);
}

void Lania::Scene::addSprite2D(LayerID scene2DID, EntityID entityID)
{
	Sprite2D sprite2D;
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	sprite2D.alpha = 255;
	sprite2D.entityID = entityID;
	scene2D->activeSprites.push_back(sprite2D);
	scene2D->entities.at(entityID).components.emplace(Entity2D::components::SPRITE_2D, scene2D->activeSprites.size() - 1);
}

void Lania::Scene::addBoxCollider2D(LayerID scene2DID, EntityID entityID, double xMin, double yMin, double xMax, double yMax)
{
	BoxCollider2D boxCollider2D;
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	boxCollider2D.aabb.min_px.x = xMin;
	boxCollider2D.aabb.min_px.y = yMin;
	boxCollider2D.aabb.max_px.x = xMax;
	boxCollider2D.aabb.max_px.y = yMax;
	boxCollider2D.entityID = entityID;
	scene2D->activeBoxColliders.push_back(boxCollider2D);
	scene2D->entities.at(entityID).components.emplace(Entity2D::components::BOX_COLLIDER_2D, scene2D->activeBoxColliders.size() - 1);
}

void Lania::Scene::addRigidBody2D(LayerID scene2DID, EntityID entityID)
{
	RigidBody2D rigidBody2D;
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	rigidBody2D.entityID = entityID;
	scene2D->activeRigidBodies.push_back(rigidBody2D);
	scene2D->entities.at(entityID).components.emplace(Entity2D::components::RIGID_BODY_2D, scene2D->activeRigidBodies.size() - 1);
}

void Lania::Scene::addParentToEntity2D(LayerID scene2DID, EntityID entityID, String parentName)
{
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	EntityID parentEntityID = scene2D->entityNameRegistry.at(parentName);
	scene2D->entities.at(entityID).parent = parentEntityID;
	scene2D->entities.at(parentEntityID).children.push_back(entityID);
}

void Lania::Scene::addPointLock2D(LayerID scene2DID, EntityID entityID, double x, double y)
{
	PositionLock2D pointLock2D;
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	pointLock2D.point.x = x;
	pointLock2D.point.y = y;
	pointLock2D.entityID = entityID;
	scene2D->pointLocks.push_back(pointLock2D);
	scene2D->entities.at(entityID).components.emplace(Entity2D::components::POINT_LOCK_2D, scene2D->pointLocks.size() - 1);
}

void Lania::Scene::addSpriteTextureFrame(LayerID scene2DID, ComponentListIndex componentIndex, String filepath)
{
	Sprite2D* sprite2D = &this->subScenes2D.at(scene2DID).activeSprites.at(componentIndex);
	sprite2D->textureFrames.push_back(this->loadTexture(filepath));
}

void Lania::Scene::removeEntity2D(LayerID scene2DID, EntityID entityID)
{
	Vector<Entity2D>* entities = &this->subScenes2D.at(scene2DID).entities;
	entities->erase(entities->begin() + (entityID - 1));
}

void Lania::Scene::centreEntity2DToSprite(LayerID scene2DID, EntityID entityID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	scene2D->entities.at(entityID).transform.position_px.x = 
		scene2D->activeSprites.at(componentIndex).textureFrames.back().getWidth() / 2.0;
	scene2D->entities.at(entityID).transform.position_px.y =
		scene2D->activeSprites.at(componentIndex).textureFrames.back().getHeight() / 2.0;
}

void Lania::Scene::centreCurrentCamera2DToSprite(LayerID scene2DID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	Sprite2D* sprite2D = &scene2D->activeSprites.at(componentIndex);
	scene2D->entities.at(scene2D->activeCameras.at(scene2D->currentCameraIndex).entityID).transform.position_px.x = sprite2D->textureFrames.back().getWidth() / 2.0;
	scene2D->entities.at(scene2D->activeCameras.at(scene2D->currentCameraIndex).entityID).transform.position_px.y = sprite2D->textureFrames.back().getHeight() / 2.0;
	scene2D->activeCameras.at(scene2D->currentCameraIndex).viewport_px.width = sprite2D->textureFrames.back().getWidth();
	scene2D->activeCameras.at(scene2D->currentCameraIndex).viewport_px.height = sprite2D->textureFrames.back().getHeight() / 1.777;
}

void Lania::Scene::flipSprite2D(LayerID scene2DID, ComponentListIndex componentIndex, bool flip)
{
	this->subScenes2D.at(scene2DID).activeSprites.at(componentIndex).flip = flip;
}

void Lania::Scene::setCamera2DInactive(LayerID scene2DID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	Vector<Camera2D>* cameras = &scene2D->activeCameras;
	scene2D->inactiveCameras.push_back(cameras->at(componentIndex));
	cameras->erase(cameras->begin() + (componentIndex - 1));
}

void Lania::Scene::setRigidBody2DInactive(LayerID scene2DID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	Vector<RigidBody2D>* rigidBodies = &scene2D->activeRigidBodies;
	scene2D->inactiveRigidBodies.push_back(rigidBodies->at(componentIndex));
	rigidBodies->erase(rigidBodies->begin() + (componentIndex - 1));
}

void Lania::Scene::setSprite2DInactive(LayerID scene2DID, ComponentListIndex componentIndex)
{
	Scene2D* scene2D = &this->subScenes2D.at(scene2DID);
	Vector<Sprite2D>* sprites = &scene2D->activeSprites;
	scene2D->inactiveSprites.push_back(sprites->at(componentIndex));
	sprites->erase(sprites->begin() + (componentIndex - 1));
}

void Lania::Scene::addAudioSource2D(LayerID scene2DID, EntityID entityID, String filepath)
{

}

void Lania::Scene::updateTimers(double runtime_ms) 
{
	int timerCount = this->timers.size();
	Timer* timers = this->timers.data();

	for (int i = 0; i < timerCount; i++)
	{
		switch (timers[i].request)
		{
		case Timer::requestFlags::SET_START:; break;
		case Timer::requestFlags::SET_END:; break;
		case Timer::requestFlags::RESET:; break;
		case Timer::requestFlags::LAP:; break;
		}
	}
}