#include "MainMenu.h"

#include <iostream>

#include "GraphicsManager.h"
#include "GameManager.h"
#include "UIManager.h"

using namespace ResWolf;

std::unique_ptr<MainMenu> MainMenu::instance;

MainMenu* MainMenu::init()
{
	instance = std::make_unique<MainMenu>();
	return instance.get();
}

MainMenu::MainMenu()
{
	shown = true;
	shader = GRAPHICS->shaders["UI"];
	box = GRAPHICS->vertices["UIRect"];
	background = GRAPHICS->createTexture("Resources/Texture/MainMenu.png", "Main Menu");
	arrow = GRAPHICS->createTexture("Resources/Texture/MainArrow.png", "Arrow");

	auto callback = [this](GLFWwindow* window, int key, int scancode, int action, int mod)
	{
		if (key == GLFW_KEY_DOWN)
		{
			option++;
			option %= 3;
		}
		else if (key == GLFW_KEY_UP)
		{
			option--;
			if (option < 0)
			{
				option += 3;
			}
		}
	};
	GAME->keydown[typeid(this).hash_code()] = callback;
}

MainMenu::~MainMenu()
{

}

void MainMenu::toggle()
{
	shown ^= true;
}

void MainMenu::draw()
{
	if (!shown)
		return;
	glDisable(GL_DEPTH_TEST);
	UI_MGR->drawRect(background, 0, 0, (float)GRAPHICS->width, (float)GRAPHICS->height);
	UI_MGR->drawRect(arrow, 1216, (float)(470 + 96 * option), 64, 64);
	glEnable(GL_DEPTH_TEST);
}