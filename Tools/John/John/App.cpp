#include "App.h"

#include "UINode.h"

#include "Grid.h"

#include "UIButton.h"
#include "SaveButton.h"
#include "LoadButton.h"

#include "SectionHeader.h"
#include "Tile.h"
#include "TileArea.h"

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

	auto mouse = IMG_Load("Resources/mouse.png");
	auto cursor = SDL_CreateColorCursor(mouse, 0, 0);
	SDL_SetCursor(cursor);
	// todo: set mouse

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
			UINode::PCT(100), UINode::PCT(100)
		},
		3,
		new Grid(),
		new UINode(
			{
				0, 0,
				256, UINode::PCT(100),
				"",
				CGA_LT_BLUE,
				StyleDirection::TOP,
				StyleDirection::RIGHT,
			},
			4,
			new SectionHeader(
				64, 48,
				"Resources/Tiles"
			),
			new TileArea(),
			new SectionHeader(
				64, 256 + 80,
				"Resources/Entities"
			),
			new UINode(
				{
					16, 256 + 112,
					224, 256,
					"",
					CGA_BLUE,
					StyleDirection::TOP,
					StyleDirection::LEFT,
					CGA_CYAN
				}
			)
		),
		new UINode(
			{
				0, 0,
				UINode::PCT(100), 32,
				"",
				CGA_LT_BLUE,
				StyleDirection::TOP,
				StyleDirection::LEFT,
				CGA_CYAN
			},
			2,
			new SaveButton(),
			new LoadButton()
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
		case SDL_MOUSEBUTTONDOWN:
		{
			rootDom->handleMouseDown({ 0, 0 }, e);
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			rootDom->handleMouseUp({ 0, 0 }, e);
			break;
		}
		case SDL_MOUSEWHEEL:
		{
			rootDom->handleMouseScroll({ 0, 0 }, e);
			break;
		}
		case SDL_KEYDOWN:
		{
			rootDom->handleKeyDown(e);
			if (e.key.keysym.scancode == SDL_SCANCODE_F11)
			{
				auto current = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
				SDL_SetWindowFullscreen(window, current ^ SDL_WINDOW_FULLSCREEN_DESKTOP);
			}
			break;
		}
		case SDL_KEYUP:
		{
			rootDom->handleKeyUp(e);
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
bool App::tryLoadTexture(_In_ std::string path, _In_ std::string alias, _Out_ Texture** texture)
{
	Texture* t = NULL;
	if (!Texture::tryLoad(path, &t))
	{
		*texture = NULL;
		return false;
	}

	textures[alias] = t;

	*texture = t;
	return true;
}
