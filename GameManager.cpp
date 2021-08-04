#include "GameManager.h"

#include <iostream>

#include "GraphicsManager.h"
#include "MainMenu.h"
#include "Logging.h"

using namespace ResWolf;

#pragma region Error

std::string ResWolf::GameErrorMessage(GameError error)
{
	std::string code = "";
	switch (error)
	{
	case GameError::OK:
		code = "OK)";
		break;
	}
	return "(GameError::" + code;
}


#pragma endregion

#pragma region Static

std::unique_ptr<GameManager> GameManager::instance;

GameError GameManager::init()
{
	instance = std::make_unique<GameManager>();

	// init game-related stuff
	Level::init();

	return instance->status;
}

#pragma endregion

#pragma region Public

GameManager::GameManager():
	keydown(),
	keyup()
{
	status = GameError::OK;
	setInputCallbacks();
}

GameManager::~GameManager()
{

}

bool GameManager::loadLevel(std::string path)
{
	if (level != nullptr)
	{
		// TODO: Save player in tmp var here
		delete level;
	}
	level = new Level(path);

	if (level->status != LevelStatus::OK)
	{
		delete level;
		state = GameState::MAIN_MENU; // Go back to main menu on failed
		return false;
	}
	state = GameState::PLAYING_GAME;
	return true;
}

void GameManager::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (state)
	{
	case GameState::MAIN_MENU:
	{
		MENU->draw();
		break;
	}
	case GameState::PLAYING_GAME:
		level->draw();
		break;
	}
	GRAPHICS->draw();
}

void GameManager::update()
{
	GRAPHICS->camera->update();
	if (keymap[GLFW_KEY_W])
	{
		GRAPHICS->camera->cameraPos += GRAPHICS->camera->cameraFront * 0.1f;
	}
	if (keymap[GLFW_KEY_SPACE])
	{
		GRAPHICS->camera->cameraPos += GRAPHICS->camera->cameraUp * 0.1f;
	}
}

#pragma endregion

#pragma region Private

void GameManager::setInputCallbacks()
{
	glfwSetInputMode(GRAPHICS->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glfwSetKeyCallback(GRAPHICS->window, dispatchKeyEvent);
	glfwSetCursorPosCallback(GRAPHICS->window, dispatchMousePosEvent);
	glfwSetMouseButtonCallback(GRAPHICS->window, dispatchMouseButtonEvent);
}

#pragma endregion

//Key Handlers:

void dispatchKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mod)
{

	if (action == GLFW_PRESS)
	{
		KEYS[key] = true;
		for (const auto& down : GAME->keydown)
		{
			down.second(window, key, scancode, action, mod);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		KEYS[key] = false;
		for (const auto& up : GAME->keyup)
		{
			up.second(window, key, scancode, action, mod);
		}
	}
}

void dispatchMousePosEvent(GLFWwindow* window, double xPos, double yPos)
{

	//return;
	auto width = GRAPHICS->width;
	auto height = GRAPHICS->height;

	Camera* camera = GRAPHICS->camera;

	float sensitivity = 0.1f;
	float x = ((float)xPos - width / 2) * sensitivity;
	float y = ((float)yPos - height / 2) * sensitivity;

	camera->yaw += x;
	camera->pitch -= y;

	if (camera->pitch > 89.0f)
		camera->pitch = 89.0f;
	if (camera->pitch < -89.0f)
		camera->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
	front.y = sin(glm::radians(camera->pitch));
	front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
	camera->cameraFront = glm::normalize(front);
	//if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		glfwSetCursorPos(window, width / 2, height / 2);
}

void dispatchMouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	std::cout << std::to_string(button) << ", " << std::to_string(action) << std::endl;
}