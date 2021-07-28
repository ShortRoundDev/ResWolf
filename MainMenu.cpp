#include "MainMenu.h"

using namespace ResWolf;

#include "GraphicsManager.h"

MainMenu::MainMenu()
{
	shown = true;
	shader = GRAPHICS->shaders["UI"];
	background = GRAPHICS->createTexture("Resources/MainMenu.png", "Main Menu");
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
	shader->setTex(background->image);
	//TODO Stopped here last time
}