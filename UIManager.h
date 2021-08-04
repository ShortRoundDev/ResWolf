#pragma once

#include <memory>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#define UI_MGR (UIManager::instance)

namespace ResWolf
{
	class UIManager
	{
	public:
		static std::unique_ptr<UIManager> instance;
		static void init();
		UIManager();
		~UIManager();

		void drawRect(_In_ Texture* image, float x, float y, float w, float h);
		void drawText(_In_ std::string text, float x, float y, float w, float h);
		void drawText(_In_ const char* text, float x, float y, float w, float h);
	private:
		Shader* uiShader;
		Shader* fontShader;

		Texture* notFound;
		Texture* font;

		Model* rect;
		Model* letter;
	};
}