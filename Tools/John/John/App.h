#pragma once

#include <string>
#include <map>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"

#include "Texture.h"

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

	std::map<std::string, Texture*> textures;
	
	bool shouldQuit = false;

	UINode* rootDom;

	void update();
	void draw();
	void events();

	void windowResizeEvent(const SDL_Event& e);

	_Success_(return)
	bool tryLoadTexture(_In_ std::string path, _In_ std::string alias, _Out_ Texture** texture);

	int width;
	int height;

	// ----- Editor stuff -----
	int selectedTile = 0;
	Texture* selectedTileTexture = nullptr;
};

