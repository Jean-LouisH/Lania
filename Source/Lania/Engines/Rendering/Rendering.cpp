#include "Rendering.hpp"
#include "Rendering2D.hpp"
#include <Utilities/Definitions/Constants.hpp>
#include <GL/glew.h>

void Lania::Rendering::render(Renderables* renderables, uint8_t renderer, SDL_Window* window)
{
	Layer2D* layer2Ds = renderables->layer2Ds.data();
	Layer3D* layer3Ds = renderables->layer3Ds.data();
	LayerType* layerTypeOrder = renderables->layerTypeOrder.data();
	int layer2DCount = renderables->layer2Ds.size();
	int layer3DCount = renderables->layer3Ds.size();
	int totalLayerCount = layer2DCount + layer3DCount;
	int currentSubscene2D = 0;
	int currentSubscene3D = 0;

	switch (renderer)
	{
		case LANIA_OPENGL_3_3_RENDERER:

			Rendering::OpenGL::clearBuffers();

			for (int i = 0; i < totalLayerCount; i++)
			{
				if (layerTypeOrder[i] == SUBSCENE_2D)
				{
					Layer2D* currentLayer2D = &layer2Ds[currentSubscene2D];
					List<Sprite2DRenderable>* sprites2D = &currentLayer2D->sprites2D;
					static List<GLuint> glTextureIDs;
					
					if (renderables->hasChanged)
					{
						Rendering2D::OpenGL::delete2DTextures(&glTextureIDs);
						glTextureIDs.clear();
						Rendering2D::OpenGL::generate2DTextures(sprites2D->data(), sprites2D->size(), &glTextureIDs);
					}
					Rendering2D::OpenGL::drawSprites(
						sprites2D->data(),
						sprites2D->size(),
						glTextureIDs.data(),
						&currentLayer2D->currentCamera2D);
					currentSubscene2D++;
				}
				else if (layerTypeOrder[i] == SUBSCENE_3D)
				{
					currentSubscene3D++;
				}
			}
			SDL_GL_SwapWindow(window);
			break;

		case LANIA_VULKAN_1_1_RENDERER:
			break;
	}
}

void Lania::Rendering::OpenGL::clearBuffers()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}