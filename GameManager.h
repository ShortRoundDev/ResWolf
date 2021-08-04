#pragma once

#include <functional>
#include <string>
#include <memory>
#include <map>

#include "Level.h"

//forward declaration
struct GLFWwindow;

#define GAME (GameManager::instance)

namespace ResWolf
{
	enum class GameState
	{
		MAIN_MENU,
		PLAYING_GAME,
		LOADING_SAVE,
		OPTIONS_MENU
	};

	enum class GameError
	{
		OK
	};

	std::string GameErrorMessage(GameError error);

	class GameManager
	{
	public:
		static std::unique_ptr<GameManager> instance;
		static GameError init();

		GameManager();
		~GameManager();

		GameError status;
		GameState state = GameState::MAIN_MENU;

		std::map<size_t, std::function<void(GLFWwindow*, int, int, int, int)>> keydown;
		std::map<size_t, std::function<void(GLFWwindow*, int, int, int, int)>> keyup;

		bool loadLevel(std::string path);

		void draw();
		void update();
	private:
		void setInputCallbacks();

		Level* level;
	};
}

void dispatchKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mod);