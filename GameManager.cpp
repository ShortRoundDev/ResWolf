#include "GameManager.h"

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
	return instance->status;
}

#pragma endregion

#pragma region Public

GameManager::GameManager()
{
	status = GameError::OK;
}

#pragma endregion

#pragma region Private

GameManager::~GameManager()
{

}

#pragma endregion