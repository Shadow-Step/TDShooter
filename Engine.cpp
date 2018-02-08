#include "Engine.h"

Engine::Engine(RenderWindow * window)
{
	this->window = window;
	this->window->setMouseCursorVisible(false);
	this->winsize = (Vector2f)window->getSize();
	InitResources();
	this->gameStage = inst::mainmenu;
	mainmenu = new MainMenu(window, &gameStage);
	currentStage = mainmenu;
}
Engine::~Engine()
{
	
}
void Engine::Update(const float &time)
{	
	currentStage->Update(time);

	if (currentStage->GetStage() != this->gameStage)
	{
		switch (this->gameStage)
		{
		case inst::gameloop:
			if (gameloop == 0)
			{
				gameloop = new GameLoop(window, &gameStage);
			}
			this->currentStage = gameloop;
			break;
		case inst::mainmenu:
			this->currentStage = mainmenu;
			break;
		default:
			break;
		}
	}

}
void Engine::Draw()
{
	currentStage->Draw();
}
void Engine::InitResources()
{
	Resources::InitFont();
	Resources::InitStrings();
}
void Engine::Controls(Event &event)
{
	currentStage->Controls(event);
}
