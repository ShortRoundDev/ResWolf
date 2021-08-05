#pragma once

#include <functional>
#include <string>
#include <memory>
#include <map>

#include "Level.h"

//forward declaration
struct GLFWwindow;

/** Shortcut to Game Manager singleton */
#define GAME (GameManager::instance)
/** Shortcut to keymap */
#define KEYS (GAME->keymap)
/** Shortcut to mouse state */
#define MOUSE (GAME->mouse)

namespace ResWolf
{
	/** Describes mouse up/down status for the 3 mouse buttons */
	typedef struct _Mouse
	{
		bool left = false;
		bool right = false;
		bool middle = false;
	} Mouse;

	/** Current state of the game */
	enum class GameState
	{
		MAIN_MENU,
		PLAYING_GAME,
		LOADING_SAVE,
		OPTIONS_MENU
	};

	/** Error codes for the GameManager */
	enum class GameError
	{
		OK
	};

	/** Converts GameError code to string message */
	std::string GameErrorMessage(GameError error);

	/** Handles all things related to the game, menu, etc. This is the daddy of the entire program */
	class GameManager
	{
	public:
		/** GameManager singleton */
		static std::unique_ptr<GameManager> instance;
		/** Creates the GameManager singleton */
		static GameError init();

		/** Creates a GameManager */
		GameManager();
		~GameManager();

		/** Current status of the GameManager */
		GameError status;
		/** Current Game State */
		GameState state = GameState::MAIN_MENU;

		/** keydown event handlers. All are called on a keydown event.
		  * Owners can choose whatever dictionary key they want, but typeid().hashcode is the designed intent */
		std::map<size_t, std::function<void(GLFWwindow*, int, int, int, int)>> keydown;

		/** keyup event handlers. All are called on a keyup event.
		  * Owners can choose whatever dictionary key they want, but typeid().hashcode is the designed intent */
		std::map<size_t, std::function<void(GLFWwindow*, int, int, int, int)>> keyup;

		/** Current state of all keys. true = down, false = up.
		  * this can be accessed with the regular [] accessor since it will initialize non-existant members to false*/
		std::map<int, bool> keymap;

		/** Current state of the mouse buttons (up/down) */
		Mouse mouse;

		/** Loads a level and starts the game state to play it.
		  * If the game already has a level, this will destroy the current level and 
		  * move the player to the new one. If the provided level path doesn't exist or otherwise fails to load,
		  * the game state is set to go to the main menu */ // TODO: Display some error on failed level loading
		bool loadLevel(std::string path);

		/** Draws level and UI (including main menu UI) */
		void draw();
		/** Updates all game objects */
		void update();
	private:
		/** Initializes the GLFW event handlers */
		void setInputCallbacks();

		/** The current level */
		Level* level;
	};
}

/** Sets the keymap entries to the appropriate values, then dispatches key events in the relevant dictionaries (up/down) */
void dispatchKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mod);
/** Handles mouse movement. Currently all mouse handling is done here, with no events */ // TODO: handle mouse events with event handlers like keys
void dispatchMousePosEvent(GLFWwindow* window, double xPos, double yPos);
/** Handles mouse button events. Currently all buttons are done here, with no events */ // TODO: handle mouse events with event handlers like keys
void dispatchMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);