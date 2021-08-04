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
	rect = GRAPHICS->vertices["UIRect"];
	notFound = GRAPHICS->textures["NotFound"];
}

UIManager::~UIManager()
{

}

void UIManager::drawRect(Texture* image, float x, float y, float w, float h)
{
	uiShader->use();
	uiShader->setModel(rect);
	uiShader->setTex(image->image);

	uiShader->setVec3("scale", glm::vec3(GRAPHICS->scrnW(w), GRAPHICS->scrnH(h), 1.0f));
	uiShader->setVec3("offset", glm::vec3(GRAPHICS->scrnX(x), GRAPHICS->scrnY(y), 0.0f));
	glDrawArrays(GL_TRIANGLES, 0, rect->size);
}