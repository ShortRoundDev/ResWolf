#pragma once

#include "glad/glad.h"

#include <string>
#include <map>
#include <memory>

class GraphicsManager
{
public:
	static std::unique_ptr<GraphicsManager> instance;
	static void init();

	std::map<std::string, GLuint> vertices;

	GraphicsManager();
	~GraphicsManager();

private:
	void initGLFW();
	void initGL();

};

