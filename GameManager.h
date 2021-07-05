#pragma once

#include <string>
#include <memory>
#include <map>

namespace ResWolf
{
	enum class GameState
	{
		MAIN_MENU,
		PLAYING_GAME,
		LOADING_SAVE,
		OPTIONS_MENU
	};

	std::string GameErrorMessage(GameError error);

	enum class GameError
	{
		OK
	};
	class GameManager
	{
	public:
		static std::unique_ptr<GameManager> instance;
		static GameError init();

		GameManager();
		~GameManager();

		GameError status;

		void draw();
		void update();

	};
}