#include "GameManager.h"
#include "GraphicsManager.h"
#include "MainMenu.h"

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
}

#pragma endregion

#pragma region Private

void GameManager::setInputCallbacks()
{
	glfwSetKeyCallback(GRAPHICS->window, dispatchKeyEvent);
}

#pragma endregion

//Key Handlers:

void dispatchKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	if (action == GLFW_PRESS)
	{
		for (const auto& down : GAME->keydown)
		{
			down.second(window, key, scancode, action, mod);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		for (const auto& up : GAME->keyup)
		{
			up.second(window, key, scancode, action, mod);
		}
	}
}
