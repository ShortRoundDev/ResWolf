#include "GraphicsManager.h"
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
		code = "OK)";
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

GraphicsError GraphicsManager::init(
	_In_ uint16_t width,
	_In_ uint16_t height,
	_In_ float fov
)
{
	instance = std::make_unique<GraphicsManager>(width, height, fov);
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

GraphicsManager::GraphicsManager(
	_In_ uint16_t width,
	_In_ uint16_t height,
	_In_ float fov
):
	camera(new Camera(width, height, fov))
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

GLuint GraphicsManager::uploadVertices(_In_ const float* data, _In_ size_t size)
{
	unsigned int vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	return vao;
}

GLuint GraphicsManager::assignNamedVertices(_In_ std::string name, _In_ const float* data, _In_ size_t size)
{
	GLuint vao = uploadVertices(data, size);
	vertices[name] = vao;
	return vao;
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
	Shader* wallShader = new Shader("Resources/Shaders/WallsVertexShader.glsl", "Resources/Shaders/WallsFragmentShader.glsl");
	if (wallShader->status != ShaderStatus::OK)
	{
		return GameErr(GraphicsError::SHADERS_FAILED);
	}
	shaders["wall"] = wallShader;
	
	Shader* uiShader = new Shader("Resources/Shaders/UIVertexShader.glsl", "Resources/Shaders/UIFragmentShader.glsl");
	if (uiShader->status != ShaderStatus::OK)
	{
		return GameErr(GraphicsError::SHADERS_FAILED);
	}
	shaders["UI"] = uiShader;

	Shader* entityShader = new Shader("Resources/Shaders/EntityVertexShader.glsl", "Resources/Shaders/EntityFragmentShader.glsl");
	if (entityShader->status != ShaderStatus::OK)
	{
		return GameErr(GraphicsError::SHADERS_FAILED);
	}
	shaders["entity"] = entityShader;

	return GameErr(GraphicsError::OK);
}

#pragma endregion