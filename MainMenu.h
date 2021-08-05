#pragma once

#include <memory>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

/** Shortcut to the main menu singleton */
#define MENU (MainMenu::instance)

namespace ResWolf
{
	class MainMenu
	{
	public:
		/** Singleton */
		static std::unique_ptr<MainMenu> instance;
		/** Creates the MainMenu singleton */
		static MainMenu* init();

		/** Constructs a main menu */
		MainMenu();
		~MainMenu();
		
		/** Show or no show. Used for pausing the game */
		void toggle();
		/** Draw the main menu */
		void draw();
		/** Update the main menu */
		void update();

		/** Cache the background texture */
		Texture* background;
		/** Cache the arrow for showing which menu item is selected*/
		Texture* arrow;

		/** Currently selected option */ // TODO: Create an enum class to handle menu depth
		int option = 0;

		/** Whether or not to show the menu. Used for pasuing the game */
		bool shown;
	};
}