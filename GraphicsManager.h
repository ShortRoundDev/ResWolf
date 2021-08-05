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
#define TEX_TR 1, 0
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
	/** Converts the given graphics error into a string error code */
	std::string GraphicsErrorMessage(GraphicsError error);

	/** Manages everything associated with OpenGL, GLAD, and everything GLFW does with Graphics */
	class GraphicsManager
	{
	public:
		/** Singleton */
		static std::unique_ptr<GraphicsManager> instance;
		/** Initializes the singleton */
		static GraphicsError init(
			_In_ uint16_t width,
			_In_ uint16_t height,
			_In_ float fov
		);

		/** The main (and only) camera for the game */
		Camera* camera;

		/** All available models in the game */
		std::map<std::string, Model*> vertices;
		/** All available shaders in the game */
		std::map<std::string, Shader*> shaders;
		/** All available textures in the game */
		std::map<std::string, Texture*> textures;
		
		/** The current status of the GraphicsManager*/
		GraphicsError status;
		
		/** The main (and only) window */
		GLFWwindow* window;
		/** Width of the window in pixels */
		int width;
		/** Width of the window in pixels */
		int height;

		/** Create a graphics manager. */
		GraphicsManager(
			_In_ uint16_t width,
			_In_ uint16_t height,
			_In_ float fov
		);
		~GraphicsManager();

		/** The default texture to display when another texture is not found to be displayed */
		Texture* notFound = nullptr;

		/** Creates a texture from the provided image path if it doesn't already exist, places it
		  * in the textures dictionary at the provided alias, then returns it. If it already exists,
		  * it simply returns the texture */
		_Success_(return != NULL)
		Texture* createTexture(_In_ std::string path, _In_ std::string alias);

		/** Uploads a textures from the image at the provided path to the GPU. Sets w to its width (in pixels)
		  * and sets h to its height (in pixels). If w and h are NULL, they are not set (they are optional) */
		_Success_(return != 0)
		GLuint uploadTexture(_In_ std::string path, _Out_opt_ int* w, _Out_opt_ int* h);

		/** Creates a model from the provided vertex data and inserts it into the models dictionary. If it
		  * already exists in the dictionary, that model is returned and nothing is uploaded */
		Model* assignNamedVertices(_In_ std::string name, _In_ const float* data, _In_ size_t size);
		/** Uploads the provided vertices to the GPU and constructs a Model from the created VAO */
		Model* uploadVertices(_In_ const float* data, _In_ size_t size);

		/** Converts screen coordinate X to normalized device coordinate */
		float scrnX(float x);
		/** Converts screen coordinate Y to normalized device coordinate */
		float scrnY(float y);
		/** Converts screen width W to normalized device width */
		float scrnW(float w);
		/** Converts screen height H to normalized device height */
		float scrnH(float h);

		/** Performs basic draw tasks (swapping the buffer), and polls GLFW events */
		// TODO: Move GLFW event polling to update
		void draw();
	private:
		/** Initializes GLFW (window) */
		GraphicsError initGLFW();
		/** Sets OpenGL initial variables (clipping) */
		GraphicsError initGL();
		/** runs GLAD loader */
		GraphicsError initGLAD();
		/** Creates shaders and puts them into the shader dictionary */
		GraphicsError initShaders();
		/** Creates some global models and puts them into the vertices dictionary */
		GraphicsError initVertices();
	};
}