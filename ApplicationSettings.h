#pragma once

#include <string>
#include <memory>

/** Used to access the singleton */
#define SETTINGS (ApplicationSettings::instance)

namespace ResWolf
{
	/** Window mode for the application */
	enum class AppWindowMode
	{
		WINDOWED			= 0,	/** Windowed with title bar */
		FULLSCREEN			= 1,	/** Fullscreen */
		WINDOWED_FULLSCREEN = 2		/** Windowed without title bar */
	};

	/** Input mode for the game */
	enum class InputMode
	{
		MODERN				= 0,	/** Mouse and keyboard, WASD movement */
		CLASSIC				= 1		/** Keyboard only. Arrow key movement, `,` and `.` for strafing */
	};

	/** Settings across the entire application. Defined in the settings.conf file or command line override */
	class ApplicationSettings
	{
	public:

		/** Singleton */
		static std::unique_ptr<ApplicationSettings> instance;
		/** Creates and assigns the singleton */
		static void init(std::string path);

		/** Constructs and loads the application settings object from the given conf file */
		ApplicationSettings(std::string path);
		~ApplicationSettings();

		/** [0, 1], volume of sound effects. Serialized as an integer from 0 - 10. Default 1.0f */
		float gameVolume;
		/** [0, 1] multiplier of light in the game. Serialized as an integer from 0 - 10. Default 0.5f */
		float brightness;
		/** [0, 1] mutliplier of mouse sensitivity in the game. Serialized as an integer from 0 - 10. Default 0.5f */
		float mouseSensitivity;
		/** [45, 180]. Default 45.0f */
		float fov;

		/** true/false. Enables certain features for debugging the game. Default false */
		bool debugMode;

		/** Width of the window. serialized as an integer. Default 1024 */
		uint16_t width;
		/** Height of the window. serialized as an integer. Default 768 */
		uint16_t height;
		/** Window mode of the application. Serialized as an integer corresponding to the AppWindowMode enum. Default WINDOWED */
		AppWindowMode appWindowMode;
		/** Input (control) mode of the application. Serialized as an integer corresponding to the InputMode enum. Default MODERN */
		InputMode inputMode;
	private:
		void parseAppConfig(_In_ const char* str);

		// Maybe should convert these specific parsers to general TryParseFloat, TryParseBool etc

		_Success_(return == true)
		bool parseGameVolume(_In_ const char* str, _Out_ float* gameVolume);
		
		_Success_(return == true)
		bool parseBrightness(_In_ const char* str, _Out_ float* brightness);
		
		_Success_(return == true)
		bool parseMouseSensitivity(_In_ const char* str, _Out_ float* mouseSensitivity);
		
		_Success_(return == true)
		bool parseFov(_In_ const char* str, _Out_ float* fov);

		_Success_(return == true)
		bool parseDebugMode(_In_ const char* str, _Out_ bool* debugMode);

		_Success_(return == true)
		bool parseWidth(_In_ const char* str, _Out_ uint16_t* width);
		
		_Success_(return == true)
		bool parseHeight(_In_ const char* str, _Out_ uint16_t* height);

		_Success_(return == true)
		bool parseAppWindowMode(_In_ const char* str, _Out_ AppWindowMode* appWindowMode);

		_Success_(return == true)
		bool parseInputMode(_In_ const char* str, _Out_ InputMode * inputMode);

	};
}