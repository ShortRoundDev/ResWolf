#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "Win32Application.h"
#include "Logging.h"

// Singletons
#include "ApplicationSettings.h"
#include "GraphicsManager.h"
#include "GameManager.h"

#include "MainMenu.h"

// Level
#include "Level.h"
#include "UIManager.h"
#include "WavefrontLoader.h"

using namespace ResWolf;

/** Initializes all managers. returns 1 on success */
int init(int argc, char** argv);
/** Runs the game */
int run();

int main(int argc, char** argv)
{
	if (init(argc, argv) != 1)
		run();
}

int init(int argc, char** argv)
{
	/* Set win32 handlers. This is the very first thing so that mem dumps can be created and
	 * sent to a server on failure */
	SetHandlers();

	/* ----- APPLICATION SETTINGS ----- */
	/* Get the app settings from settings.conf */
	ApplicationSettings::init("settings.conf");
	
	/* ----- GRAPHICS MANAGER ----- */
	/* Initialize GLAD, GL, and GLFW */
	GraphicsError graphicsStatus = GraphicsManager::init(
		SETTINGS->width,
		SETTINGS->height,
		SETTINGS->fov
	);
	if (graphicsStatus != GraphicsError::OK)
	{
		ShowError("Couldn't Initialize Graphics!", GraphicsErrorMessage(graphicsStatus));
		return -1;
	}

	/* ----- GAME MANAGER ----- */
	/* Initialize models, textures, etc. This also initializes input handlers for GLFW*/
	GameError gameStatus = GameManager::init();
	if (gameStatus != GameError::OK)
	{
		ShowError("Couldn't Initialize Game!", GameErrorMessage(gameStatus));
		return -2;
	}

	/* Initialize UI. This includes fonts and UI rectangle models */
	UIManager::init();
	MainMenu::init(); // TODO Put this in UI Manager class

	// TODO make a more robust CLI handler
	if (argc > 1)
	{
		GAME->loadLevel(std::string(argv[1]));
	}

	return 0;
}

int run()
{
	// TODO: Timer
	while (!glfwWindowShouldClose(GRAPHICS->window))
	{
		GAME->update();
		GAME->draw();
	}
	return 1;
}