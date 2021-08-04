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

using namespace ResWolf;

int init(int argc, char** argv);
int run();

int main(int argc, char** argv)
{
	if (init(argc, argv) != 1)
		run();
}

int init(int argc, char** argv)
{
	SetHandlers();

	/* ----- APPLICATION SETTINGS ----- */
	ApplicationSettings::init("settings.conf");
	GraphicsError graphicsStatus = GraphicsManager::init(
		SETTINGS->width,
		SETTINGS->height,
		SETTINGS->fov
	);

	/* ----- GRAPHICS MANAGER ----- */
	if (graphicsStatus != GraphicsError::OK)
	{
		ShowError("Couldn't Initialize Graphics!", GraphicsErrorMessage(graphicsStatus));
		return -1;
	}

	/* ----- GAME MANAGER ----- */
	GameError gameStatus = GameManager::init();
	if (gameStatus != GameError::OK)
	{
		ShowError("Couldn't Initialize Game!", GameErrorMessage(gameStatus));
		return -2;
	}

	UIManager::init();

	MainMenu::init(); // TODO Put this in some UI Manager class

	if (argc > 1)
	{
		GAME->loadLevel(std::string(argv[1]));
	}

	return 0;
}

int run()
{
	while (!glfwWindowShouldClose(GRAPHICS->window))
	{
		GAME->update();
		GAME->draw();
	}
	return 1;
}