#pragma once

#include "Windows.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GL/gl.h"

#include "Shader.h"
#include "Camera.h"

#include <string>
#include <map>
#include <memory>

//shortcut to the singleton
#define GRAPHICS (GraphicsManager::instance)

namespace ResWolf {

	//-----forward declarations------
	class Texture;
	//-------------------------------

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
		static GraphicsError init(
			_In_ uint16_t width,
			_In_ uint16_t height,
			_In_ float fov
		);

		Camera* camera;

		std::map<std::string, GLuint> vertices;
		std::map<std::string, Shader*> shaders;
		std::map<std::string, Texture*> textures;
		
		GraphicsError status;
		
		GLFWwindow* window;
		int width;
		int height;

		GraphicsManager(
			_In_ uint16_t width,
			_In_ uint16_t height,
			_In_ float fov
		);
		~GraphicsManager();

		_Success_(return != NULL)
		Texture* createTexture(_In_ std::string path, _In_ std::string alias);

		GLuint uploadVertices(_In_ const float* data, _In_ size_t size);
		GLuint assignNamedVertices(_In_ std::string name, _In_ const float* data, _In_ size_t size);

		_Success_(return != 0)
		GLuint uploadTexture(_In_ std::string path, _Out_ int* w, _Out_ int* h);
	private:
		GraphicsError initGLFW();
		GraphicsError initGL();
		GraphicsError initGLAD();
		GraphicsError initShaders();
	};
}