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

		void drawRect(Texture* image, float x, float y, float w, float h);
	private:
		Shader* uiShader;
		Texture* notFound;
		Model* rect;
	};
}