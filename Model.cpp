#include "Model.h"

using namespace ResWolf;

Model::Model(GLuint vao, size_t size):
	vao(vao),
	size(size/(sizeof(float) * 5))
{

}

Model::~Model()
{

}