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

	if (renderer == LANIA_OPENGL_3_3_RENDERER)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < totalLayerCount; i++)
		{
			if (layerTypeOrder[i] == SUBSCENE_2D)
			{
				Layer2D* currentLayer2D = &layer2Ds[currentSubscene2D];
				List<Sprite2DRenderable>* sprites2D = &currentLayer2D->sprites2D;
				Rendering2D::OpenGL::drawSprites(sprites2D->data(), sprites2D->size(), &currentLayer2D->currentCamera2D);
				currentSubscene2D++;
			}
			else if (layerTypeOrder[i] == SUBSCENE_3D)
			{
				currentSubscene3D++;
			}
		}
		SDL_GL_SwapWindow(window);
	}
	else if (renderer == LANIA_VULKAN_1_1_RENDERER)
	{
		;
	}
}