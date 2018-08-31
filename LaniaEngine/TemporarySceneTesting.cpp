#include <SDL_image.h>
#include <Application/Application.hpp>
#include <Application/Scenes/Scene.hpp>
#include <TemporarySceneTesting.hpp>

using namespace Lania;

void testLoadEntityComponentSystem(
	Application* application,
	Lania::Engine* engine)
{
	///////// Temporary Testing (Before Procedures): Entity Component System Loading Algorithms

	Scene2D scene2D;

	Entity2D dummy;
	scene2D.entities.push_back(dummy);

	///////////////////////////////////////////////////////////////////////
	Entity2D camera;
	scene2D.entities.push_back(camera);

	Camera2D camera2D;
	camera2D.viewport_px.width = engine->appConfig.windowWidth_px;
	camera2D.viewport_px.height = engine->appConfig.windowHeight_px;
	camera2D.current = true;
	camera2D.entityID = scene2D.entities.size() - 1;
	scene2D.activeCameras.push_back(camera2D);
	scene2D.entities.back().components.emplace(CAMERA2D, scene2D.activeCameras.size() - 1);
	scene2D.currentCameraIndex = scene2D.activeCameras.size() - 1;
	////////////////////////////////////////////////////////////////////////

	Entity2D background;
	scene2D.entities.push_back(background);

	Sprite2D bgSprite;
	SDL_Surface* bgSurface =
		IMG_Load("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/background.png");
	bgSprite.texture.data = SDL_CreateTextureFromSurface(engine->SDLRenderer, bgSurface);
	bgSprite.texture.pixels.width = bgSurface->w;
	bgSprite.texture.pixels.height = bgSurface->h;
	bgSprite.alpha = 255;
	SDL_SetTextureAlphaMod(bgSprite.texture.data, bgSprite.alpha);
	SDL_FreeSurface(bgSurface);
	bgSprite.entityID = scene2D.entities.size() - 1;
	scene2D.activeSprites.push_back(bgSprite);
	scene2D.entities.back().components.emplace(SPRITE, scene2D.activeSprites.size() - 1);

	scene2D.entities.back().transform.position_px.x = bgSprite.texture.pixels.width / 2.0;
	scene2D.entities.back().transform.position_px.y = bgSprite.texture.pixels.height / 2.0;

	//Camera position
	scene2D.entities.at(scene2D.activeCameras.at(scene2D.currentCameraIndex).entityID).transform.position_px.x = bgSprite.texture.pixels.width / 2.0;
	scene2D.entities.at(scene2D.activeCameras.at(scene2D.currentCameraIndex).entityID).transform.position_px.y = bgSprite.texture.pixels.height / 2.0;
	scene2D.activeCameras.at(scene2D.currentCameraIndex).viewport_px.width = bgSprite.texture.pixels.width;
	scene2D.activeCameras.at(scene2D.currentCameraIndex).viewport_px.height = bgSprite.texture.pixels.width / 1.777;

	///////////

	Entity2D floorCollider;
	floorCollider.transform.position_px.x = 1326 / 2;
	floorCollider.transform.position_px.y = 150;
	floorCollider.transform.scale.x = 15.0;
	scene2D.entities.push_back(floorCollider);

	Sprite2D boxSprite;
	SDL_Surface* boxSurface =
		IMG_Load("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/box.png");
	boxSprite.texture.data = SDL_CreateTextureFromSurface(engine->SDLRenderer, boxSurface);
	boxSprite.texture.pixels.width = boxSurface->w;
	boxSprite.texture.pixels.height = boxSurface->h;
	boxSprite.alpha = 255;
	SDL_SetTextureAlphaMod(boxSprite.texture.data, boxSprite.alpha);
	SDL_FreeSurface(boxSurface);
	boxSprite.entityID = scene2D.entities.size() - 1;
	scene2D.activeSprites.push_back(boxSprite);
	scene2D.entities.back().components.emplace(SPRITE, scene2D.activeSprites.size() - 1);

	BoxCollider2D floorBoxCollider;
	floorBoxCollider.aabb.min_px.x = -1400 / 2;
	floorBoxCollider.aabb.min_px.y = -boxSprite.texture.pixels.height / 2.0;
	floorBoxCollider.aabb.max_px.x = -floorBoxCollider.aabb.min_px.x;
	floorBoxCollider.aabb.max_px.y = -floorBoxCollider.aabb.min_px.y;
	floorBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.activeBoxColliders.push_back(floorBoxCollider);
	scene2D.entities.back().components.emplace(BOXCOLLIDER2D, scene2D.activeBoxColliders.size() - 1);

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
	scene2D.entities.back().components.emplace(RIGIDBODY2D, scene2D.activeRigidBodies.size() - 1);

	Sprite2D beldumSprite;
	SDL_Surface* beldumSurface =
		IMG_Load("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/beldum.png");
	beldumSprite.texture.data = SDL_CreateTextureFromSurface(engine->SDLRenderer, beldumSurface);
	beldumSprite.texture.pixels.width = beldumSurface->w;
	beldumSprite.texture.pixels.height = beldumSurface->h;
	beldumSprite.alpha = 255;
	SDL_SetTextureAlphaMod(beldumSprite.texture.data, beldumSprite.alpha);
	SDL_FreeSurface(beldumSurface);
	beldumSprite.entityID = scene2D.entities.size() - 1;
	scene2D.activeSprites.push_back(beldumSprite);
	scene2D.entities.back().components.emplace(SPRITE, scene2D.activeSprites.size() - 1);

	BoxCollider2D beldumBoxCollider;
	beldumBoxCollider.aabb.min_px.x = -(beldumSprite.texture.pixels.width * beldum.transform.scale.x) / 2.0;
	beldumBoxCollider.aabb.min_px.y = -(beldumSprite.texture.pixels.height * beldum.transform.scale.y) / 2.0;
	beldumBoxCollider.aabb.max_px.x = -beldumBoxCollider.aabb.min_px.x;
	beldumBoxCollider.aabb.max_px.y = -beldumBoxCollider.aabb.min_px.y;
	beldumBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.activeBoxColliders.push_back(beldumBoxCollider);
	scene2D.entities.back().components.emplace(BOXCOLLIDER2D, scene2D.activeBoxColliders.size() - 1);

	//////////

	Entity2D arcanine;
	arcanine.transform.position_px.x = 1326 - 260;
	arcanine.transform.position_px.y = 500;
	arcanine.transform.scale.x = testScale;
	arcanine.transform.scale.y = testScale;
	scene2D.entities.push_back(arcanine);

	rigid.entityID = scene2D.entities.size() - 1;
	scene2D.activeRigidBodies.push_back(rigid);
	scene2D.entities.back().components.emplace(RIGIDBODY2D, scene2D.activeRigidBodies.size() - 1);

	Sprite2D arcanineSprite;
	SDL_Surface* arcanineSurface =
		IMG_Load("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/arcanine.png");
	arcanineSprite.texture.data = SDL_CreateTextureFromSurface(engine->SDLRenderer, arcanineSurface);
	arcanineSprite.texture.pixels.width = arcanineSurface->w;
	arcanineSprite.texture.pixels.height = arcanineSurface->h;
	arcanineSprite.alpha = 255;
	SDL_SetTextureAlphaMod(arcanineSprite.texture.data, arcanineSprite.alpha);
	SDL_FreeSurface(arcanineSurface);
	arcanineSprite.entityID = scene2D.entities.size() - 1;
	arcanineSprite.flip = SDL_FLIP_HORIZONTAL;
	scene2D.activeSprites.push_back(arcanineSprite);
	scene2D.entities.back().components.emplace(SPRITE, scene2D.activeSprites.size() - 1);

	BoxCollider2D arcanineBoxCollider;
	arcanineBoxCollider.aabb.min_px.x = -(arcanineSprite.texture.pixels.width * arcanine.transform.scale.x) / 2.0;
	arcanineBoxCollider.aabb.min_px.y = -(arcanineSprite.texture.pixels.height * arcanine.transform.scale.y) / 2.0;
	arcanineBoxCollider.aabb.max_px.x = -arcanineBoxCollider.aabb.min_px.x;
	arcanineBoxCollider.aabb.max_px.y = -arcanineBoxCollider.aabb.min_px.y;
	arcanineBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.activeBoxColliders.push_back(arcanineBoxCollider);
	scene2D.entities.back().components.emplace(BOXCOLLIDER2D, scene2D.activeBoxColliders.size() - 1);

	////////////

	application->scene.subscenes2D.push_back(scene2D);

	////////////
}