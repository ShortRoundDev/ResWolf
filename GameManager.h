#pragma once

#include <functional>
#include <string>
#include <memory>
#include <map>

#include "Level.h"

//forward declaration
struct GLFWwindow;

#define GAME (GameManager::instance)
#define KEYS (GAME->keymap)
#define MOUSE (GAME->mouse)

namespace ResWolf
{
	typedef struct _Mouse
	{
		bool left = false;
		bool right = false;
		bool middle = false;
	} Mouse;

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
		std::map<int, bool> keymap;
		Mouse mouse;

		bool loadLevel(std::string path);

		void draw();
		void update();
	private:
		void setInputCallbacks();

		Level* level;
	};
}

void dispatchKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mod);
void dispatchMousePosEvent(GLFWwindow* window, double xPos, double yPos);
void dispatchMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);