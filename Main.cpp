#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "Win32Application.h"
#include "Logging.h"

// Singletons
#include "ApplicationSettings.h"
#include "GraphicsManager.h"
#include "GameManager.h"

// Level
#include "Level.h"

using namespace ResWolf;

int main(int argc, char** argv)
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
	}

	Level* level = new Level("Resources/Maps/Level.ham");
}