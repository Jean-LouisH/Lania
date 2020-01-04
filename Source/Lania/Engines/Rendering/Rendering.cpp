#include "Rendering.hpp"
#include "Rendering2DOpenGL33.hpp"
#include "ShaderCompilerGLSL330.hpp"
#include "BuiltInShadersGLSL330.hpp"
#include "Rendering2DSDL2.hpp"
#include <Utilities/Definitions/Constants.hpp>
#include <SDL_video.h>
#include <GL/glew.h>

void Lania::Rendering::render(
	Renderables* renderables, 
	uint8_t renderer, 
	SDL_Window* window, 
	SDL_Renderer* sdlRenderer)
{
	switch (renderer)
	{
		case Core::renderers::LANIA_SDL_2_RENDERER:
			Rendering::SDL2::render(renderables, window, sdlRenderer);
			SDL_GL_SwapWindow(window);
			break;
		case Core::renderers::LANIA_OPENGL_3_3_RENDERER:
			Rendering::OpenGL33::render(renderables);
			SDL_GL_SwapWindow(window);
			break;
	}
}

void Lania::Rendering::SDL2::render(Renderables* renderables, SDL_Window* window, SDL_Renderer* sdlRenderer)
{
	static List<SDLSubEngines::SDLRenderable> sdlRenderables;
	static List<SDLSubEngines::Sprite2D> sprite2Ds;
	static SDLSubEngines::Camera2D camera2D;

	Lania::Rendering::SDL2::clearBuffers(sdlRenderer);

	//Only suitable for static scenes at the moment
	if (renderables->hasChanged)
	{
		Layer2D backLayer2D = renderables->layer2Ds.at(0);
		Camera2DRenderable currentCamera2D = backLayer2D.currentCamera2D;

		for (int i = 0; i < sprite2Ds.size(); i++)
		{
			SDL_DestroyTexture(sprite2Ds.at(i).textureFrames.at(0).data);
		}

		sprite2Ds.clear();

		camera2D.transform.position_px.x = currentCamera2D.transform_px.position_px.x;
		camera2D.transform.position_px.y = currentCamera2D.transform_px.position_px.y;
		camera2D.transform.rotation_rad = currentCamera2D.transform_px.rotation_rad;
		camera2D.transform.scale.x = currentCamera2D.transform_px.scale.x;
		camera2D.transform.scale.y = currentCamera2D.transform_px.scale.y;
		camera2D.viewport_px.height = currentCamera2D.viewport_px.height;
		camera2D.viewport_px.width = currentCamera2D.viewport_px.width;

		//ToDo: Add scene function to fit camera to sprites
		float scale = 5.0;
		camera2D.viewport_px.height *= scale;
		camera2D.viewport_px.width *= scale;

		for (int i = 0; i < backLayer2D.sprites2D.size(); i++)
		{
			Sprite2DRenderable sprite2DRenderable = backLayer2D.sprites2D.at(i);
			SDLSubEngines::Sprite2D sprite2D;

			sprite2D.transform.position_px.x = sprite2DRenderable.transform_px.position_px.x;
			sprite2D.transform.position_px.y = sprite2DRenderable.transform_px.position_px.y;
			sprite2D.transform.rotation_rad = sprite2DRenderable.transform_px.rotation_rad;
			sprite2D.transform.scale.x = sprite2DRenderable.transform_px.scale.x;
			sprite2D.transform.scale.y = sprite2DRenderable.transform_px.scale.y;

			SDLSubEngines::Texture texture;

			texture.data = SDL_CreateTextureFromSurface(
				sdlRenderer,
				sprite2DRenderable.texture.getSDLSurface());

			texture.pixels.height = sprite2DRenderable.texture.getHeight();
			texture.pixels.width = sprite2DRenderable.texture.getWidth();

			sprite2D.textureFrames.push_back(texture);
			sprite2Ds.push_back(sprite2D);
		}
	}

	SDLSubEngines::buildRenderablesFromSprites(
		&sdlRenderables,
		sprite2Ds,
		camera2D,
		window);

	for (int i = 0; i < sdlRenderables.size(); i++)
	{
		SDL_RenderCopyEx(
			sdlRenderer,
			sdlRenderables.at(i).texture,
			&sdlRenderables.at(i).textureRect,
			&sdlRenderables.at(i).renderingRect,
			sdlRenderables.at(i).rotation,
			NULL,
			sdlRenderables.at(i).flip
		);
	}

	SDL_RenderPresent(sdlRenderer);
}

void Lania::Rendering::SDL2::clearBuffers(SDL_Renderer* sdlRenderer)
{
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sdlRenderer);
}

void Lania::Rendering::OpenGL33::render(Renderables* renderables)
{
	Layer2D* layer2Ds = renderables->layer2Ds.data();
	Layer3D* layer3Ds = renderables->layer3Ds.data();
	LayerType* layerTypeOrder = renderables->layerTypeOrder.data();
	int layer2DCount = renderables->layer2Ds.size();
	int layer3DCount = renderables->layer3Ds.size();
	int totalLayerCount = layer2DCount + layer3DCount;
	int currentSubscene2D = 0;
	int currentSubscene3D = 0;

	static List<GLuint> glTextureIDs;
	static List<String> glslVertexShaderSources;
	static List<String> glslFragmentShaderSources;
	static Rendering::OpenGL33::ShaderCompilerGLSL330 glslShaders;

	Rendering::OpenGL33::clearBuffers();

	for (int i = 0; i < totalLayerCount; i++)
	{
		if (layerTypeOrder[i] == SUBSCENE_2D)
		{
			Layer2D* currentLayer2D = &layer2Ds[currentSubscene2D];
			List<Sprite2DRenderable>* sprites2D = &currentLayer2D->sprites2D;

			if (renderables->hasChanged)
			{
				glslVertexShaderSources.clear();
				glslFragmentShaderSources.clear();
				glslVertexShaderSources.push_back(Rendering::OpenGL33::defaultVertexShader);
				glslFragmentShaderSources.push_back(Rendering::OpenGL33::defaultFragmentShader);
				glslShaders.compileShaders(&glslVertexShaderSources, &glslFragmentShaderSources);
				Rendering2D::OpenGL33::delete2DTextures(&glTextureIDs);
				glTextureIDs.clear();
				Rendering2D::OpenGL33::generate2DTextures(sprites2D->data(), sprites2D->size(), &glTextureIDs);
			}

			Rendering2D::OpenGL33::drawSprites(
				sprites2D->data(),
				sprites2D->size(),
				glTextureIDs.data(),
				&currentLayer2D->currentCamera2D,
				&glslShaders);

			currentSubscene2D++;
		}
		else if (layerTypeOrder[i] == SUBSCENE_3D)
		{
			currentSubscene3D++;
		}
	}
}

void Lania::Rendering::OpenGL33::clearBuffers()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}