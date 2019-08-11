#include "Model.hpp"

void Lania::Model::load(String filePath)
{
	tinygltf::TinyGLTF tinygltf;
	String error;
	String warning;
	tinygltf.LoadBinaryFromFile(&this->model, &error, &warning, filePath);
}