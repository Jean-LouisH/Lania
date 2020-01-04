#include "ShaderCompilerGLSL330.hpp"
#include "BuiltInShadersGLSL330.hpp"
#include <iostream>

void Lania::Rendering::OpenGL33::ShaderCompilerGLSL330::compileShaders(List<String>* vertexShaderSources, List<String>* fragmentShaderSources)
{
	bool compilationSuccess = true;

	int vertexShaderSourceCount = vertexShaderSources->size();
	for (int i = 0; i < vertexShaderSourceCount && compilationSuccess; i++)
		compilationSuccess = this->compileVertexShader(vertexShaderSources->at(i));

	int fragmentShaderSourceCount = fragmentShaderSources->size();
	for (int i = 0; i < fragmentShaderSourceCount && compilationSuccess; i++)
		compilationSuccess = this->compileFragmentShader(fragmentShaderSources->at(i));

	if (compilationSuccess)
		this->linkShaderProgram();

	this->deleteShaders();
}

void Lania::Rendering::OpenGL33::ShaderCompilerGLSL330::use()
{
	glUseProgram(this->shaderProgram);
}

bool Lania::Rendering::OpenGL33::ShaderCompilerGLSL330::compileVertexShader(String vertexShaderSource)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLchar* source = (GLchar*)vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &source, NULL);
	glCompileShader(vertexShader);
	this->vertexShaders.push_back(vertexShader);
	return this->checkCompileTimeErrors(vertexShader, GL_COMPILE_STATUS);
}

bool Lania::Rendering::OpenGL33::ShaderCompilerGLSL330::compileFragmentShader(String fragmentShaderSource)
{
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLchar* source = (GLchar*)fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &source, NULL);
	glCompileShader(fragmentShader);
	this->fragmentShaders.push_back(fragmentShader);
	return this->checkCompileTimeErrors(fragmentShader, GL_COMPILE_STATUS);
}

void Lania::Rendering::OpenGL33::ShaderCompilerGLSL330::linkShaderProgram()
{
	GLuint shaderProgram = glCreateProgram();
	int vertexShaderCount = this->vertexShaders.size();
	for (int i = 0; i < vertexShaderCount; i++)
		glAttachShader(shaderProgram, this->vertexShaders.at(i));

	int fragmentShaderCount = this->fragmentShaders.size();
	for (int i = 0; i < fragmentShaderCount; i++)
		glAttachShader(shaderProgram, this->fragmentShaders.at(i));

	glLinkProgram(shaderProgram);
	this->checkCompileTimeErrors(shaderProgram, GL_LINK_STATUS);
	this->shaderProgram = shaderProgram;
}

bool Lania::Rendering::OpenGL33::ShaderCompilerGLSL330::checkCompileTimeErrors(GLuint ID, GLuint status)
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

void Lania::Rendering::OpenGL33::ShaderCompilerGLSL330::deleteShaders()
{
	int vertexShaderCount = this->vertexShaders.size();
	for (int i = 0; i < vertexShaderCount; i++)
		glDeleteShader(this->vertexShaders.at(i));
	this->vertexShaders.clear();

	int fragmentShaderCount = this->fragmentShaders.size();
	for (int i = 0; i < fragmentShaderCount; i++)
		glDeleteShader(this->fragmentShaders.at(i));
	this->fragmentShaders.clear();
}

void Lania::Rendering::OpenGL33::ShaderCompilerGLSL330::setIntUniform(String name, int value)
{
	glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), value);
}