#pragma once

#include <map>
#include <vector>
#include <SDL.h>

#define PCT(x) (-(x))

#define CALC_X(x) ((int)((x) < 0		\
	? (APP->width  * (-(x)/100.0f))		\
	: (x)))

#define CALC_Y(y) ((int)((y) < 0		\
	? (APP->height * (-(y)/100.0f))		\
	: (y)))

class UINode
{
public:
	UINode(SDL_FRect dimensions);
	UINode(SDL_FRect dimensions, SDL_Color color);
	UINode(SDL_FRect dimensions, int totalChildren, ...);
	UINode(SDL_FRect dimensions, SDL_Color color, int totalChildren, ...);

	virtual ~UINode();
	
	virtual void draw(SDL_FPoint offset);
	virtual void update();

	bool click(const SDL_Event& e);
	
	virtual bool mouseDown(const SDL_Event& e);
	virtual bool mouseUp(const SDL_Event& e);

	virtual bool keyDown(const SDL_Event& e);
	virtual bool keyUp(const SDL_Event& e);

	std::vector<UINode*> children;

protected:
	SDL_Texture* image;
	SDL_Color color;
	SDL_FRect dimensions;
	SDL_Rect src;
};

