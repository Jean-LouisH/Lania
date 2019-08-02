#include "GLSLShader.hpp"
#include "DefaultGLSLShaders.hpp"
#include <iostream>

void Lania::Rendering::OpenGL::GLSLShaders::compileShaders()
{
	if (this->compileVertexShaders())
		if (this->compileFragmentShaders())
			this->linkShaderProgram();
	this->deleteShaders();
}

void Lania::Rendering::OpenGL::GLSLShaders::use()
{
	glUseProgram(this->shaderProgram);
}

bool Lania::Rendering::OpenGL::GLSLShaders::compileVertexShaders()
{
	GLuint vertexShader;
	GLchar* vertexShaderSource = (GLchar*)Rendering::OpenGL::defaultVertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	this->vertexShaders.push_back(vertexShader);
	return this->checkCompileTimeErrors(vertexShader, GL_COMPILE_STATUS);
}

bool Lania::Rendering::OpenGL::GLSLShaders::compileFragmentShaders()
{
	GLuint fragmentShader;
	GLchar* fragmentShaderSource = (GLchar*)Rendering::OpenGL::defaultFragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	this->fragmentShaders.push_back(fragmentShader);
	return this->checkCompileTimeErrors(fragmentShader, GL_COMPILE_STATUS);
}

void Lania::Rendering::OpenGL::GLSLShaders::linkShaderProgram()
{
	GLuint shaderProgram = glCreateProgram();
	int vertexShaderCount = this->vertexShaders.size();
	for (int i = 0; i < this->vertexShaders.size(); i++)
		glAttachShader(shaderProgram, this->vertexShaders.at(i));

	int fragmentShaderCount = this->fragmentShaders.size();
	for (int i = 0; i < this->fragmentShaders.size(); i++)
		glAttachShader(shaderProgram, this->fragmentShaders.at(i));

	glLinkProgram(shaderProgram);
	this->checkCompileTimeErrors(shaderProgram, GL_LINK_STATUS);
	this->shaderProgram = shaderProgram;
}

bool Lania::Rendering::OpenGL::GLSLShaders::checkCompileTimeErrors(GLuint ID, GLuint status)
{
	GLint compilationSuccess = GL_FALSE;
	char infoLog[512];

	if (status == GL_COMPILE_STATUS)
		glGetShaderiv(ID, status, &compilationSuccess);
	else if (status == GL_LINK_STATUS)
		glGetProgramiv(ID, status, &compilationSuccess);

	if (!compilationSuccess)
	{
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		std::cout << "\n" << infoLog << "\n";
	}

	return compilationSuccess;
}

void Lania::Rendering::OpenGL::GLSLShaders::deleteShaders()
{
	int vertexShaderCount = this->vertexShaders.size();
	for (int i = 0; i < this->vertexShaders.size(); i++)
		glDeleteShader(this->vertexShaders.at(i));
	this->vertexShaders.clear();

	int fragmentShaderCount = this->fragmentShaders.size();
	for (int i = 0; i < this->fragmentShaders.size(); i++)
		glDeleteShader(this->fragmentShaders.at(i));
	this->fragmentShaders.clear();
}