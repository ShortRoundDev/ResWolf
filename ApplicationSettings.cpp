#include "ApplicationSettings.h"

#include "FileHandling.h"

#include "Logging.h"

using namespace ResWolf;

#pragma region Static

std::unique_ptr<ApplicationSettings> ApplicationSettings::instance;
void ApplicationSettings::init(std::string path)
{
	instance = std::make_unique<ApplicationSettings>(path);
}

#pragma endregion

#pragma region Public

ApplicationSettings::ApplicationSettings(std::string path):
	gameVolume(1.0f),
	brightness(0.5f),
	mouseSensitivity(0.5f),
	fov(45.0f),
	debugMode(false),
	width(1920),
	height(1080),
	appWindowMode(AppWindowMode::WINDOWED),
	inputMode(InputMode::MODERN)
{
	char* appConfigText = NULL;
	int err = ReadTextFile(path, &appConfigText, NULL);
	if (err)
	{
		Warn("Couldn't open settings.conf for reading!\nGot " + std::to_string(err));
		return;
	}

	parseAppConfig(appConfigText);
}

ApplicationSettings::~ApplicationSettings()
{

}

#pragma endregion

#pragma region Private

void ApplicationSettings::parseAppConfig(_In_ const char* str)
{
	char* start = NULL;
	char* end = (char*) str;
	int line = 0;
	do
	{
		errno = 0;
		line++;
		start = end;

		// Get first half of string
		for (; *end != 0 && *end != '=' && *end != '\n'; end++);
		if (*end == '\n')
		{
			end++;
			continue;	// fucked up line...
		}
		else if (*end == EOF)
		{
			break;		// really fucked up line
		}
		if (*end == 0)
		{
			break;		// really REALLY fucked up line
		}
		// *end == '='
		*end = '\0'; // null terminate first half
		end++;

		// Get second half
		for (; *end != 0 && *end != '\n'; end++);

		*end = '\0';
		end++;

		std::string failLine = "";

		char* value = start + strnlen(start, 128) + 1;

		if (!strcmp(start, "GameVolume"))
		{
			float _gameVolume = gameVolume;
			if (parseGameVolume(value, &_gameVolume))
			{
				gameVolume = _gameVolume;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else if (!strcmp(start, "Brightness"))
		{
			float _brightness = brightness;
			if (parseBrightness(value, &_brightness))
			{
				brightness = _brightness;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else if (!strcmp(start, "MouseSensitivity"))
		{
			float _mouseSensitivity = mouseSensitivity;
			if (parseMouseSensitivity(value, &_mouseSensitivity))
			{
				mouseSensitivity = _mouseSensitivity;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else if (!strcmp(start, "FOV"))
		{
			float _fov = fov;
			if (parseFov(value, &_fov))
			{
				fov = _fov;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else if (!strcmp(start, "Width"))
		{
			uint16_t _width = width;
			if (parseWidth(value, &_width))
			{
				width = _width;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else if (!strcmp(start, "Height"))
		{
			uint16_t _height = height;
			if (parseHeight(value, &_height))
			{
				height = _height;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else if (!strcmp(start, "AppWindowMode"))
		{
			AppWindowMode _appWindowMode = appWindowMode;
			if (parseAppWindowMode(value, &_appWindowMode))
			{
				appWindowMode = _appWindowMode;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else if (!strcmp(start, "InputMode"))
		{
			InputMode _inputMode = inputMode;
			if (parseInputMode(value, &_inputMode))
			{
				inputMode = _inputMode;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else if (!strcmp(start, "DebugMode"))
		{
			bool _debugMode = debugMode;
			if (parseDebugMode(value, &_debugMode))
			{
				debugMode = _debugMode;
			}
			else
			{
				failLine = std::string(start);
			}
		}
		else
		{
			Warn("Got invalid settings.conf variable: " + std::string(start));
		}

		if (!failLine.empty())
		{
			Warn("Couldn't parse variable '" + failLine
				+ "'\n got '" + value
				+ "'\nin settings.conf at line " + std::to_string(line)
			);
		}

	} while (*end != 0);
}

_Success_(return == true)
bool ApplicationSettings::parseGameVolume(_In_ const char* str, _Out_ float* gameVolume)
{
	char* end;
	UINT64 range = strtoul(str, &end, 10);
	if (errno != 0 || range > 10)
	{
		return false;
	}
	if (range == 10)
		*gameVolume = 1.0f; // making sure 1 is 1
	else
		*gameVolume = ((float)range) / 10.0f;
	return true;
}

_Success_(return == true)
bool ApplicationSettings::parseBrightness(_In_ const char* str, _Out_ float* brightness)
{
	char* end;
	UINT64 range = strtoul(str, &end, 10);
	if (errno != 0 || range > 10)
	{
		return false;
	}
	if (range == 10)
		*brightness = 1.0f; // making sure 1 is 1
	else
		*brightness = ((float)range) / 10.0f;
	return true;
}

_Success_(return == true)
bool ApplicationSettings::parseMouseSensitivity(_In_ const char* str, _Out_ float* mouseSensitivity)
{
	char* end;
	UINT64 range = strtoul(str, &end, 10);
	if (errno != 0 || range > 10)
	{
		return false;
	}
	if (range == 10)
		*mouseSensitivity = 1.0f; // making sure 10 is 10
	else
		*mouseSensitivity = ((float)range) / 10.0f;
	return true;
}

_Success_(return == true)
bool ApplicationSettings::parseFov(_In_ const char* str, _Out_ float* fov)
{
	char* end;
	UINT64 range = strtoul(str, &end, 10);
	if (errno != 0 || range > 180 || range < 45)
	{
		return false;
	}
	
	*fov = (float)range;
	return true;
}

_Success_(return == true)
bool ApplicationSettings::parseDebugMode(_In_ const char* str, _Out_ bool* debugMode)
{
	char* lower = (char*) str;
	if (_strlwr_s(lower, strlen(str) + 1))
	{
		return false;
	}
	if (strcmp(lower, "true"))
	{
		if (strcmp(lower, "false"))
		{
			// neither true nor false
			return false;
		}
		//false
		*debugMode = false;
	}
	else
	{
		//true
		*debugMode = true;
	}
	return true;

}


_Success_(return == true)
bool ApplicationSettings::parseWidth(_In_ const char* str, _Out_ uint16_t* width)
{
	char* end;
	UINT64 range = strtoul(str, &end, 10);
	if (errno != 0)
	{
		return false;
	}

	*width = (uint16_t)range;
	return true;
}

_Success_(return == true)
bool ApplicationSettings::parseHeight(_In_ const char* str, _Out_ uint16_t* height)
{
	char* end;
	UINT64 range = strtoul(str, &end, 10);
	if (errno != 0)
	{
		return false;
	}

	*height = (uint16_t)range;
	return true;
}

_Success_(return == true)
bool ApplicationSettings::parseAppWindowMode(_In_ const char* str, _Out_ AppWindowMode* appWindowMode)
{
	char* end;
	UINT64 range = strtoul(str, &end, 10);
	if (errno != 0)
	{
		return false;
	}
	switch (range)
	{
	case 0:
		*appWindowMode = AppWindowMode::WINDOWED;
		break;
	case 1:
		*appWindowMode = AppWindowMode::FULLSCREEN;
		break;
	case 2:
		*appWindowMode = AppWindowMode::WINDOWED_FULLSCREEN;
		break;
	default:
		return false;
	}
	return true;
}

_Success_(return == true)
bool ApplicationSettings::parseInputMode(_In_ const char* str, _Out_ InputMode* inputMode)
{
	char* end;
	UINT64 range = strtoul(str, &end, 10);
	if (errno != 0)
	{
		return false;
	}
	switch (range)
	{
	case 0:
		*inputMode= InputMode::MODERN;
		break;
	case 1:
		*inputMode = InputMode::CLASSIC;
		break;
	default:
		return false;
	}
	return true;
}

#pragma endregion