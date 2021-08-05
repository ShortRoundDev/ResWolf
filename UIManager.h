#pragma once

#include <memory>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

/** Shortcut to the UI Manager's singleton */
#define UI_MGR (UIManager::instance)

namespace ResWolf
{
	/** Responsible for drawing simple 2D UI images and text */
	class UIManager
	{
	public:
		/** Singleton */
		static std::unique_ptr<UIManager> instance;
		/** Initializes the Singleton */
		static void init();
		/** Constructs the UIManager, caching shaders, textures, and models */
		UIManager();
		~UIManager();

		/** Draws the provided texture at the given x, y coordinate (in pixels) with the provided w, h dimensions (in pixels) */
		void drawRect(_In_ Texture* image, float x, float y, float w, float h);
		
		/** Draws the provided string at the given x, y, coordinate (in pixels) with each character of the provided w, h dimensions (in pixels).
		  * Uses the ASCII table font found at Resources/Texture/Font.png */
		void drawText(_In_ std::string text, float x, float y, float w, float h);

		/** Draws the provided text at the given x, y, coordinate (in pixels) with each character of the provided w, h dimensions (in pixels).
		  * Uses the ASCII table font found at Resources/Texture/Font.png */
		void drawText(_In_ const char* text, float x, float y, float w, float h);
	private:

		/** Cached shader for drawing 2D UI */
		Shader* uiShader;
		/** Cached shader for drawing text */
		Shader* fontShader;

		/** Cached fallback texture for when the provided texture cannot be found */
		Texture* notFound;
		/** Cached font texture */
		Texture* font;

		/** Cached UI 2D rect mesh */
		Model* rect;
		/** Cached text character 2D rect mesh */
		Model* letter;
	};
}