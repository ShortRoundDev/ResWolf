#pragma once

#include <memory>
#include <map>

class GameManager
{
public:
	static std::unique_ptr<GameManager> instance;
	static void init(int width, int height);

	GameManager(int width, int height);
	~GameManager();
	
	void draw();
	void update();

};

