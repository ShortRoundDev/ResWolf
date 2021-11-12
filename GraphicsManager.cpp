#include "GraphicsManager.h"
#include "WindowEvents.h"
#include "ApplicationSettings.h"
#include "Logging.h"
#include "WavefrontLoader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>

#define STB_IMAGE_IMPLEMENTATION
#pragma warning(push, 0)
#include "stb_image.h"
#pragma warning(pop)
#include "Texture.h"

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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	
	instance->notFound = instance->createTexture("Resources/Texture/NotFound.png", "NotFound");

	WavefrontLoader::init();

	return code;
}

#pragma endregion

#pragma region Public

GraphicsManager::GraphicsManager(
	_In_ uint16_t w,
	_In_ uint16_t h,
	_In_ float fov
):
	camera(new Camera(w, h, fov)),
	width(w),
	height(h)
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
	if ((status = initVertices()) != GraphicsError::OK)
	{
		return;
	}
}

GraphicsManager::~GraphicsManager()
{
	// clean up window?
}

_Success_(return != NULL)
Texture* GraphicsManager::createTexture(_In_ std::string path, _In_ std::string alias)
{
	auto result = textures.find(alias);
	if (result != textures.end())
	{	// exists
		return result->second;
	}
	// does not exist
	Texture* texture = new Texture(path);
	textures[alias] = texture;
	return texture;
}

Model* GraphicsManager::uploadVertices(_In_ const float* data, _In_ size_t size)
{
	unsigned int vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);

	return new Model(vao, size);
}

Model* GraphicsManager::assignNamedVertices(_In_ std::string name, _In_ const float* data, _In_ size_t size)
{
	auto result = vertices.find(name);
	if (result != vertices.end())
	{	// exists
		return result->second;
	}

	Model* model = uploadVertices(data, size);
	vertices[name] = model;
	return model;
}

_Success_(return != 0)
GLuint GraphicsManager::uploadTexture(_In_ std::string path, _Out_opt_ int* w, _Out_opt_ int* h)
{
	int _w = 0, _h = 0, channels = 0;
	UCHAR* data = stbi_load(path.c_str(), &_w, &_h, &channels, 0);
	if (data == NULL)
	{
		return 0;
	}
	if (w != NULL)
	{
		*w = _w;
	}
	if (h != NULL)
	{
		*h = _h;
	}

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(texture);

	stbi_image_free(data);

	return texture;
}

float GraphicsManager::scrnX(float x)
{
	return ((x / width) * 2.0f) - 1.0f;
}

float GraphicsManager::scrnY(float y)
{
	return -(((y / height) * 2.0f) - 1.0f);
}

float GraphicsManager::scrnW(float w)
{
	return w / width;
}

float GraphicsManager::scrnH(float h)
{
	return h / height;
}

void GraphicsManager::draw()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
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
		SETTINGS->width, SETTINGS->height,
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
	glfwSwapInterval(1);
	glfwShowWindow(window);

	stbi_set_flip_vertically_on_load(false);

	return GameErr(GraphicsError::OK);
}

GraphicsError GraphicsManager::initGL()
{
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	Shader* fontShader = new Shader("Resources/Shaders/FontVertexShader.glsl", "Resources/Shaders/FontFragmentShader.glsl");
	if (fontShader->status != ShaderStatus::OK)
	{
		return GameErr(GraphicsError::SHADERS_FAILED);
	}
	shaders["font"] = fontShader;

	return GameErr(GraphicsError::OK);
}

GraphicsError GraphicsManager::initVertices()
{
	// Top-left oriented rect for UI
	float UIRect[] = {
		0.0f,  0.0f, 0.0f, 0.0f, 1.0f,
		2.0f,  0.0f, 0.0f, 1.0f, 1.0f,
		2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
		
		2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
		0.0f, -2.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 0.0f, 1.0f
	};
	vertices["UIRect"] = uploadVertices(UIRect, sizeof(UIRect));

	const float cw = 1.0f / 254.0f;

	float letter[] = {
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// top left
		1.0f, 0.0f, 1.0f, cw,   1.0f, 0.0f, 0.0f, 0.0f,// top right
		1.0f, 1.0f, 1.0f, cw,	0.0f, 0.0f, 0.0f, 0.0f,// bottom right

		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// top right
		1.0f, 1.0f, 1.0f, cw,	0.0f, 0.0f, 0.0f, 0.0f,// bottom right
		0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f// bottom left
	};
	vertices["letter"] = uploadVertices(letter, sizeof(letter));

	return GraphicsError::OK;
}

#pragma endregion