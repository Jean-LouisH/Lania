#include "Rendering2D.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

void Lania::Rendering2D::OpenGL::drawSprites(
	Sprite2DRenderable* sprites2D, 
	int spriteCount,
	Camera2DRenderable* currentCamera2D)
{
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	float borderColour[] = { 1.0, 1.0, 0.0, 1.0 };

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < spriteCount; i++)
	{
		uint64_t format = 0;
		Sprite2DRenderable* currentSprite2D = &sprites2D[i];

		switch (currentSprite2D->texture.getBytesPerPixel())
		{
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
		}

		//glTexImage2D(
		//	GL_TEXTURE_2D,
		//	0,
		//	GL_RGBA,
		//	currentSprite2D->texture.getWidth(),
		//	currentSprite2D->texture.getHeight(),
		//	0,
		//	format,
		//	GL_UNSIGNED_BYTE,
		//	currentSprite2D->texture.getData());
		//glGenerateMipmap(GL_TEXTURE_2D);

	}
}