#include "UINode.h"
#include "App.h"

UINode::UINode(SDL_FRect dimensions) : UINode(dimensions, { 0, 0, 0, 0 })
{
}

UINode::UINode(SDL_FRect dimensions, SDL_Color color)
{
	image = NULL;
	this->dimensions = dimensions;
	this->color = color;
	this->src = {
		0, 0,
		(int)dimensions.w, (int)dimensions.h
	};
}

UINode::UINode(SDL_FRect dimensions, int totalChildren, ...) : UINode(dimensions, { 0, 0, 0, 0 })
{
	va_list args;
	UINode* children = NULL;
	va_start(args, totalChildren);
	for (int i = 0; i < totalChildren; i++)
	{
		auto child = va_arg(args, UINode*);
		this->children.push_back(child);
	}
}

UINode::UINode(SDL_FRect dimensions, SDL_Color color, int totalChildren, ...) : UINode(dimensions, color)
{
	va_list args;
	UINode* children = NULL;
	va_start(args, totalChildren);
	for (int i = 0; i < totalChildren; i++)
	{
		auto child = va_arg(args, UINode*);
		this->children.push_back(child);
	}
}

UINode::~UINode()
{

}

void UINode::draw(SDL_FPoint offset)
{

	SDL_FPoint _offset = {
		offset.x + dimensions.x,
		offset.y + dimensions.y
	};

	if (image != NULL)
	{
		SDL_FRect _dimensions
		{
			_offset.x,
			_offset.y,
			CALC_X(dimensions.w),
			CALC_Y(dimensions.h)
		};

		SDL_RenderCopyF(
			APP->renderer,
			image,
			&src,
			&_dimensions
		);
	}

	if (color.a != 0)
	{
		SDL_FRect _dimension{
			_offset.x,
			_offset.y,
			CALC_X(dimensions.w),
			CALC_Y(dimensions.h)
		};
		SDL_SetRenderDrawColor(APP->renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRectF(
			APP->renderer,
			&_dimension
		);
	}

	for (const auto& c : children)
	{
		c->draw(_offset);
	}
}

void UINode::update()
{

}

bool UINode::click(const SDL_Event& e)
{
	SDL_Point pos = { e.button.x, e.button.y };
	//if(SDL_PointInRect()
	for (auto c : children)
	{
		//sif()
	}
	return true;
}

bool UINode::mouseDown(const SDL_Event& e)
{

	return true;
}

bool UINode::mouseUp(const SDL_Event& e)
{

	return true;
}

bool UINode::keyDown(const SDL_Event& e)
{

	return true;
}

bool UINode::keyUp(const SDL_Event& e)
{
	return true;
}