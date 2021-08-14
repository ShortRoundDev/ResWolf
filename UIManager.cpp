#include "UIManager.h"

#include "GraphicsManager.h"

using namespace ResWolf;

std::unique_ptr<UIManager> UIManager::instance = nullptr;

void UIManager::init()
{
	instance = std::make_unique<UIManager>();
}

UIManager::UIManager()
{
	uiShader = GRAPHICS->shaders["UI"];
	fontShader = GRAPHICS->shaders["font"];
	font = GRAPHICS->createTexture("Resources/Texture/Font.png", "Font");

	rect = GRAPHICS->vertices["UIRect"];
	letter = GRAPHICS->vertices["letter"];
	notFound = GRAPHICS->textures["NotFound"];
}

UIManager::~UIManager()
{

}

void UIManager::drawRect(_In_ Texture* image, float x, float y, float w, float h)
{
	uiShader->use();
	uiShader->setModel(rect);
	uiShader->setTex(image->image);

	uiShader->setVec3("scale", glm::vec3(GRAPHICS->scrnW(w), GRAPHICS->scrnH(h), 1.0f));
	uiShader->setVec3("offset", glm::vec3(GRAPHICS->scrnX(x), GRAPHICS->scrnY(y), 0.0f));
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)rect->size);
}

void UIManager::drawText(_In_ std::string text, float x, float y, float w, float h)
{
	if (text.empty())
		return;
	drawText(text.c_str(), x, y, w, h);
}

void UIManager::drawText(_In_ const char* text, float x, float y, float w, float h)
{
	//string is null or empty
	if (text == NULL || text[0] == 0)
		return;
	glDisable(GL_DEPTH_TEST);
	fontShader->use();
	fontShader->setModel(letter);
	fontShader->setTex(font->image);
	int i = 0;
	for (char *c = (char*)text; *c != 0; c++, i++)
	{
		fontShader->setFloat("character", (float)(*c));
		fontShader->setVec2(
			"pos",
			glm::vec2(
				GRAPHICS->scrnX(x) + GRAPHICS->scrnW((w * 0.65f) * i),
				GRAPHICS->scrnY(y)
			)
		);
		fontShader->setVec2("size", glm::vec2(GRAPHICS->scrnW(w), GRAPHICS->scrnH(h)));
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)letter->size);
	}
	glEnable(GL_DEPTH_TEST);
}
