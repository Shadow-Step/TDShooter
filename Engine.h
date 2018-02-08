#pragma once

#include "Screen.h"

class Engine
{
private:
	
	RenderWindow * window;
	Vector2f winsize;
	
	MainMenu* mainmenu = 0;
	GameLoop* gameloop = 0;
	Stage * currentStage = 0;

	inst::GameStages gameStage;

	RectangleShape background;
	Texture tex;
public:
	Engine(RenderWindow * window);
	virtual ~Engine();
	//Funtions
	void Update(const float &time);
	void Draw();
	void InitResources();
	void Controls(Event &event);
};

