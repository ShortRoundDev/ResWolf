#pragma once

#include <memory>

#include "Shader.h"
#include "Texture.h"

#define MENU (MainMenu::instance)

namespace ResWolf
{
	class MainMenu
	{
	public:
		static std::unique_ptr<MainMenu> instance;
		static MainMenu* init();

		Shader* shader;

		MainMenu();
		~MainMenu();

		void toggle();
		void draw();

		void update();

		Texture* background;

		bool shown;
	};
}