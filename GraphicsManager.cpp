#include "GraphicsManager.h"
#include "Windows.h"

#include "WindowEvents.h"
#include "Logging.h"

using namespace ResWolf;

#pragma region Errors
std::string ResWolf::GraphicsErrorMessage(GraphicsError error)
{
	std::string code = "";
	switch (error)
	{
	case GraphicsError::OK:
		code = "OK";
		break;
	case GraphicsError::GLFW_WINDOW_FAILED:
		code = "GLFW_WINDOW_FAILED)\nFailed to initialize window!";
		break;
	case GraphicsError::GL_FAILED:
		code = "GL_FAILED)\nFailed to initialize OpenGL!";
		break;
	case GraphicsError::GLAD_FAILED:
		code = "GLAD_FAILED)\nFailed to load GLAD!";
		break;
	case GraphicsError::SHADERS_FAILED:
		code = "SHADERS_FAILED\nShader compilation failed!";
		break;
	}
	return "(GraphicsError::" + code;
}
#pragma endregion

#pragma region Static

std::unique_ptr<GraphicsManager> GraphicsManager::instance;

GraphicsError GraphicsManager::init()
{
	instance = std::make_unique<GraphicsManager>();
	GraphicsError code = instance->status;
	if (code != GraphicsError::OK)
	{
		// TODO log error?
		instance = nullptr;
	}
	return code;
}

#pragma endregion

#pragma region Public

GraphicsManager::GraphicsManager()
{
	if ((status = initGLFW()) != GraphicsError::OK)
	{
		// TODO log error?
		return;
	}
	if ((status = initGLAD()) != GraphicsError::OK)
	{
		// TODO log error?
		return;
	}
	if ((status = initGL()) != GraphicsError::OK)
	{
		// TODO log error?
		return;
	}
	if ((status = initShaders()) != GraphicsError::OK)
	{
		// TODO log error?
		return;
	}
}

GraphicsManager::~GraphicsManager()
{
	// clean up window?
}

#pragma endregion

#pragma region Private

/* ========== PRIVATE ========== */

GraphicsError GraphicsManager::initGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(
		1024, 768,
		"ResWolf3D",
		nullptr, nullptr
	);
	RaiseException(0, EXCEPTION_NONCONTINUABLE_EXCEPTION, 0, NULL);

	if (!window)
	{
		// TODO log error?
		return GameErr(GraphicsError::GLFW_WINDOW_FAILED);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	return GameErr(GraphicsError::OK);
}

GraphicsError GraphicsManager::initGL()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return GameErr(GraphicsError::OK);
}

GraphicsError GraphicsManager::initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return GameErr(GraphicsError::GLAD_FAILED);
	}
	return GameErr(GraphicsError::OK);
}

GraphicsError GraphicsManager::initShaders()
{
	shaders["Wall"] = std::make_unique<Shader>("WallsVertexShader.glsl", "WallsFragmentShader.glsl");
	shaders["UI"] = std::make_unique<Shader>("UIVertexShader.glsl", "UIFragmentShader.glsl");
	shaders["Entity"] = std::make_unique<Shader>("EntityVertexShader.glsl", "EntityFragmentShader.glsl");
}

#pragma endregion