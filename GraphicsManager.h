#pragma once

#include "Windows.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GL/gl.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

#include <string>
#include <map>
#include <memory>

//shortcut to the singleton
#define GRAPHICS (GraphicsManager::instance)

#define TEX_TL 0, 0
#define TEX_TR 0, 1
#define TEX_BL 0, 1
#define TEX_BR 1, 1

namespace ResWolf {

	//-----forward declarations------
	class Texture;
	//-------------------------------

	enum class GraphicsError {
		OK,
		GLFW_WINDOW_FAILED,
		GL_FAILED,
		GLAD_FAILED,
		SHADERS_FAILED,
		VERTICES_FAILED
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

		std::map<std::string, Model*> vertices;
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

		Texture* notFound = nullptr;
		_Success_(return != NULL)
		Texture* createTexture(_In_ std::string path, _In_ std::string alias);

		Model* uploadVertices(_In_ const float* data, _In_ size_t size);
		Model* assignNamedVertices(_In_ std::string name, _In_ const float* data, _In_ size_t size);

		_Success_(return != 0)
		GLuint uploadTexture(_In_ std::string path, _Out_opt_ int* w, _Out_opt_ int* h);

		float scrnX(float x);
		float scrnY(float y);
		float scrnW(float w);
		float scrnH(float h);

		void draw();
	private:
		GraphicsError initGLFW();
		GraphicsError initGL();
		GraphicsError initGLAD();
		GraphicsError initShaders();
		GraphicsError initVertices();
	};
}