#include "App.h"

#include "UINode.h"
#include "UIButton.h"

std::unique_ptr<App> App::instance = nullptr;

void App::init(std::string title)
{
	instance = std::make_unique<App>(title);
	instance->createDom();
}

App::App(std::string title)
{
	window = NULL;
	renderer = NULL;

	width = 1024;
	height = 768;

	SDL_CreateWindowAndRenderer(
		1024,
		768,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
		&window,
		&renderer
	);
	SDL_SetWindowTitle(window, title.c_str());

}

App::~App()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;
}

void App::createDom()
{
	rootDom = new UINode(
		{
			0, 0,
			PCT(100), PCT(100)
		},
		1,
		new UINode(
			{
				0, 0,
				PCT(100), 32
			},
			{ 85, 85, 255, 255 },
			2,
			new UIButton(
				{ 0, 0 },
				"Resources/Save"
			),
			new UIButton(
				{ 128, 0 },
				"Resources/Load"
			)
		)
	);
}

void App::update()
{

}

void App::draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 170, 255);
	SDL_RenderClear(renderer);

	rootDom->draw({ 0, 0 });

	SDL_RenderPresent(renderer);
}

void App::events()
{
	SDL_Event e = { 0 };
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
		{
			shouldQuit = true;
			return;
		}
		case SDL_KEYDOWN:
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_F11)
			{
				auto current = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
				SDL_SetWindowFullscreen(window, current ^ SDL_WINDOW_FULLSCREEN_DESKTOP);
			}
			break;
		}
		case SDL_WINDOWEVENT:
		{
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
			{
				windowResizeEvent(e);
				break;
			}
			}
			break;
		}
		}
	}
}

void App::windowResizeEvent(const SDL_Event& e)
{
	SDL_GetWindowSize(window, &width, &height);
}

_Success_(return)
bool App::tryLoadTexture(_In_ std::string path, _In_ std::string alias, _Out_ SDL_Texture** texture)
{
	auto tex = IMG_LoadTexture(this->renderer, path.c_str());
	if (tex == NULL)
	{
		return false;
	}

	textures[alias] = tex;

	*texture = tex;
	return true;
}
