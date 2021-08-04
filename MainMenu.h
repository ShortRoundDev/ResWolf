#pragma once

#include <memory>

#include "Model.h"
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

		MainMenu();
		~MainMenu();

		Shader* shader;
		Model* box;

		void toggle();
		void draw();

		void update();

		Texture* background;
		Texture* arrow;

		int option = 0;

		bool shown;
	};
}