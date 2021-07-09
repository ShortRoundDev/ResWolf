#pragma once

#include <string>
#include <map>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"

#define APP (App::instance)

/* Forward declaration */

class UINode;

class App
{
public:

	static std::unique_ptr<App> instance;
	static void init(std::string title);

	App(std::string title);
	~App();

	void createDom();

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::map<std::string, SDL_Texture*> textures;
	
	bool shouldQuit = false;

	UINode* rootDom;

	void update();
	void draw();
	void events();

	void windowResizeEvent(const SDL_Event& e);

	_Success_(return)
	bool tryLoadTexture(_In_ std::string path, _In_ std::string alias, _Out_ SDL_Texture** texture);

	int width;
	int height;
};

