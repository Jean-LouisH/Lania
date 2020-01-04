#include "Rendering2DOpenGL33.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

void Lania::Rendering2D::OpenGL33::generate2DTextures(
	Sprite2DRenderable* sprites2D,
	int spriteCount,
	List<GLuint>* glTextureIDs)
{
	for (int i = 0; i < spriteCount; i++)
	{
		float borderColour[] = { 1.0, 1.0, 0.0, 1.0 };
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE, texture);
		glTextureIDs->push_back(texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		uint64_t format = 0;
		Sprite2DRenderable* currentSprite2D = &sprites2D[i];

		switch (currentSprite2D->texture.getBytesPerPixel())
		{
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
		}

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			currentSprite2D->texture.getWidth(),
			currentSprite2D->texture.getHeight(),
			0,
			format,
			GL_UNSIGNED_BYTE,
			currentSprite2D->texture.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Lania::Rendering2D::OpenGL33::delete2DTextures(
	List<GLuint>* glTextureIDs)
{
	int size = glTextureIDs->size();

	for (int i = 0; i < size; i++)
		glDeleteTextures(1, &glTextureIDs->at(i));
}

void Lania::Rendering2D::OpenGL33::drawSprites(
	Sprite2DRenderable* sprites2D, 
	int spriteCount,
	GLuint* glTextureIDs,
	Camera2DRenderable* currentCamera2D,
	Rendering::OpenGL33::ShaderCompilerGLSL330* glslShaderCompiler)
{
	glslShaderCompiler->use();

	for (int i = 0; i < spriteCount; i++)
	{
		glBindVertexArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}