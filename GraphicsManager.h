#pragma once

#include "Windows.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GL/gl.h"

#include "Shader.h"

#include <string>
#include <map>
#include <memory>

namespace ResWolf {

	enum class GraphicsError {
		OK,
		GLFW_WINDOW_FAILED,
		GL_FAILED,
		GLAD_FAILED,
		SHADERS_FAILED
	};

	std::string GraphicsErrorMessage(GraphicsError error);

	class GraphicsManager
	{
	public:
		static std::unique_ptr<GraphicsManager> instance;
		static GraphicsError init();

		std::map<std::string, GLuint> vertices;
		std::map<std::string, Shader*> shaders;
		
		GraphicsError status;
		
		GLFWwindow* window;
		int width;
		int height;

		GraphicsManager();
		~GraphicsManager();

	private:
		GraphicsError initGLFW();
		GraphicsError initGL();
		GraphicsError initGLAD();
		GraphicsError initShaders();
	};
}