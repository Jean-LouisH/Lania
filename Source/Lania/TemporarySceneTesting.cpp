#include <SDL_image.h>
#include <Application/Application.hpp>
#include <Application/Scenes/Scene.hpp>
#include <TemporarySceneTesting.hpp>

using namespace Lania;

void testLoadEntityComponentSystem(
	Application* application,
	Lania::Core* core)
{
	///////// Temporary Testing (Before Procedures): Entity Component System Loading Algorithms

	Scene2D scene2D;

	///////////////////////////////////////////////////////////////////////
	Entity2D camera;
	scene2D.entities.push_back(camera);

	Camera2D camera2D;
	camera2D.viewport_px.width = core->appConfig.windowWidth_px;
	camera2D.viewport_px.height = core->appConfig.windowHeight_px;
	camera2D.current = true;
	camera2D.entityID = scene2D.entities.size() - 1;
	scene2D.activeCameras.push_back(camera2D);
	scene2D.entities.back().components.emplace(CAMERA_2D, scene2D.activeCameras.size() - 1);
	scene2D.currentCameraIndex = scene2D.activeCameras.size() - 1;
	////////////////////////////////////////////////////////////////////////

	Entity2D background;
	scene2D.entities.push_back(background);

	Sprite2D bgSprite;
	bgSprite.textureFrames.push_back(application->scene.loadTexture("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/background.png",
		core->SDLRenderer));
	bgSprite.alpha = 255;
	SDL_SetTextureAlphaMod(bgSprite.textureFrames.back().data, bgSprite.alpha);
	bgSprite.entityID = scene2D.entities.size() - 1;
	scene2D.activeSprites.push_back(bgSprite);
	scene2D.entities.back().components.emplace(SPRITE_2D, scene2D.activeSprites.size() - 1);

	scene2D.entities.back().transform.position_px.x = bgSprite.textureFrames.back().pixels.width / 2.0;
	scene2D.entities.back().transform.position_px.y = bgSprite.textureFrames.back().pixels.height / 2.0;

	//Camera position
	scene2D.entities.at(scene2D.activeCameras.at(scene2D.currentCameraIndex).entityID).transform.position_px.x = bgSprite.textureFrames.back().pixels.width / 2.0;
	scene2D.entities.at(scene2D.activeCameras.at(scene2D.currentCameraIndex).entityID).transform.position_px.y = bgSprite.textureFrames.back().pixels.height / 2.0;
	scene2D.activeCameras.at(scene2D.currentCameraIndex).viewport_px.width = bgSprite.textureFrames.back().pixels.width;
	scene2D.activeCameras.at(scene2D.currentCameraIndex).viewport_px.height = bgSprite.textureFrames.back().pixels.width / 1.777;

	///////////

	Entity2D floorCollider;
	floorCollider.transform.position_px.x = 1326 / 2;
	floorCollider.transform.position_px.y = 150;
	floorCollider.transform.scale.x = 15.0;
	scene2D.entities.push_back(floorCollider);

	Sprite2D boxSprite;
	boxSprite.textureFrames.push_back(application->scene.loadTexture("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/box.png",
		core->SDLRenderer));
	boxSprite.alpha = 255;
	SDL_SetTextureAlphaMod(boxSprite.textureFrames.back().data, boxSprite.alpha);
	boxSprite.entityID = scene2D.entities.size() - 1;
	scene2D.activeSprites.push_back(boxSprite);
	scene2D.entities.back().components.emplace(SPRITE_2D, scene2D.activeSprites.size() - 1);

	BoxCollider2D floorBoxCollider;
	floorBoxCollider.aabb.min_px.x = -1400 / 2;
	floorBoxCollider.aabb.min_px.y = -boxSprite.textureFrames.back().pixels.height / 2.0;
	floorBoxCollider.aabb.max_px.x = -floorBoxCollider.aabb.min_px.x;
	floorBoxCollider.aabb.max_px.y = -floorBoxCollider.aabb.min_px.y;
	floorBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.activeBoxColliders.push_back(floorBoxCollider);
	scene2D.entities.back().components.emplace(BOX_COLLIDER_2D, scene2D.activeBoxColliders.size() - 1);

	double testScale = 2.5;
	//testScale = 1.0;

	Entity2D beldum;
	beldum.transform.position_px.x = 260;
	beldum.transform.position_px.y = 500;
	beldum.transform.scale.x = testScale;
	beldum.transform.scale.y = testScale;
	beldum.audioSources.push_back(Mix_LoadWAV("../Demos/PhysicsTest/PhysicsTest/Audio/Sounds/Beldum cry.wav"));
	scene2D.entities.push_back(beldum);

	RigidBody2D rigid;
	rigid.gravity_scale = 20.0;
	rigid.entityID = scene2D.entities.size() - 1;
	scene2D.activeRigidBodies.push_back(rigid);
	scene2D.entities.back().components.emplace(RIGID_BODY_2D, scene2D.activeRigidBodies.size() - 1);

	Sprite2D beldumSprite;
	beldumSprite.textureFrames.push_back(application->scene.loadTexture("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/beldum.png",
		core->SDLRenderer));
	beldumSprite.alpha = 255;
	SDL_SetTextureAlphaMod(beldumSprite.textureFrames.back().data, beldumSprite.alpha);
	beldumSprite.entityID = scene2D.entities.size() - 1;
	scene2D.activeSprites.push_back(beldumSprite);
	scene2D.entities.back().components.emplace(SPRITE_2D, scene2D.activeSprites.size() - 1);

	BoxCollider2D beldumBoxCollider;
	beldumBoxCollider.aabb.min_px.x = -(beldumSprite.textureFrames.back().pixels.width * beldum.transform.scale.x) / 2.0;
	beldumBoxCollider.aabb.min_px.y = -(beldumSprite.textureFrames.back().pixels.height * beldum.transform.scale.y) / 2.0;
	beldumBoxCollider.aabb.max_px.x = -beldumBoxCollider.aabb.min_px.x;
	beldumBoxCollider.aabb.max_px.y = -beldumBoxCollider.aabb.min_px.y;
	beldumBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.activeBoxColliders.push_back(beldumBoxCollider);
	scene2D.entities.back().components.emplace(BOX_COLLIDER_2D, scene2D.activeBoxColliders.size() - 1);

	//////////

	Entity2D arcanine;
	arcanine.transform.position_px.x = 1326 - 260;
	arcanine.transform.position_px.y = 500;
	arcanine.transform.scale.x = testScale;
	arcanine.transform.scale.y = testScale;
	scene2D.entities.push_back(arcanine);

	rigid.entityID = scene2D.entities.size() - 1;
	scene2D.activeRigidBodies.push_back(rigid);
	scene2D.entities.back().components.emplace(RIGID_BODY_2D, scene2D.activeRigidBodies.size() - 1);

	Sprite2D arcanineSprite;
	arcanineSprite.textureFrames.push_back(application->scene.loadTexture("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/arcanine.png",
		core->SDLRenderer));
	arcanineSprite.alpha = 255;
	SDL_SetTextureAlphaMod(arcanineSprite.textureFrames.back().data, arcanineSprite.alpha);
	arcanineSprite.entityID = scene2D.entities.size() - 1;
	arcanineSprite.flip = SDL_FLIP_HORIZONTAL;
	scene2D.activeSprites.push_back(arcanineSprite);
	scene2D.entities.back().components.emplace(SPRITE_2D, scene2D.activeSprites.size() - 1);

	BoxCollider2D arcanineBoxCollider;
	arcanineBoxCollider.aabb.min_px.x = -(arcanineSprite.textureFrames.back().pixels.width * arcanine.transform.scale.x) / 2.0;
	arcanineBoxCollider.aabb.min_px.y = -(arcanineSprite.textureFrames.back().pixels.height * arcanine.transform.scale.y) / 2.0;
	arcanineBoxCollider.aabb.max_px.x = -arcanineBoxCollider.aabb.min_px.x;
	arcanineBoxCollider.aabb.max_px.y = -arcanineBoxCollider.aabb.min_px.y;
	arcanineBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.activeBoxColliders.push_back(arcanineBoxCollider);
	scene2D.entities.back().components.emplace(BOX_COLLIDER_2D, scene2D.activeBoxColliders.size() - 1);

	////////////

	application->scene.subscenes2D.push_back(scene2D);

	////////////
}