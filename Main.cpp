#include "Engine.h"
//Namespaces
// bonus::
// perk::
// elem::
// weap::
// obj::
// sel::

//ToDo

//Unit::Command
//Исправить на пересечение MoveMarker'a 
//Размер маркера уравнять с размером спрайта


int params[3];
bool SHOWFPS;//temp

int main()
{
	InitConfig();
	sf::RenderWindow window(VideoMode(params[0],params[1]), "TDShooter",params[2]+7);

	//sf::RenderWindow window(VideoMode::getDesktopMode(), "TDShooter");
	
	Engine engine(&window);

	Clock timer;
	float time;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::F1)) //temp
				SHOWFPS = true; //temp

				engine.Controls(event);
			
		}

		time = timer.restart().asSeconds();
		if (SHOWFPS)//temp
			cout << 1 / time << endl;//temp

		engine.Update(time);
		engine.Draw();
	}

	return 0;
}