#include "Layer.h"

Selector BuildScreen::selector;

Layer::Layer()
{
}
Layer::~Layer()
{
	
}

//Stat screen
StatScreen::StatScreen(Player * player)
{
	boardTex.loadFromFile("Textures/Background/back_01.png");//
	winTex.loadFromFile("Textures/Background/back_03.jpg");//

	this->window.setTexture(&winTex);
	this->window.setSize(Vector2f(600, 400));
	this->window.setPosition(100, 100);

	//this->boarder.setTexture(&boardTex);
	this->boarder.setSize(Vector2f(610, 410));
	this->boarder.setPosition(95, 95);

	this->clicktimer = 0;
	this->player = player;

	label.push_back(new Label("Hp: ", Color(136, 136, 136, 255), Vector2f(100, 100), 16, 1));
	label.push_back(new Label("Level: ", Color(136, 136, 136, 255), Vector2f(100, 130), 16, 1));
}
StatScreen::~StatScreen()
{
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
}
void StatScreen::Update(Vector2i mouse, const float & time)
{
	clicktimer += time;
	UpdateLabels();
	for (size_t i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->IsAlive())
		{
			buttons[i]->Update(mouse, time);
			CheckButtonInst(*buttons[i]);
		}
		else
		{
			delete buttons[i];
			buttons.erase(buttons.begin() + i);
		}
	}
	for (size_t i = 0; i < label.size(); i++)
	{
		label[i]->Update(mouse, time);
	}
}
void StatScreen::UpdateLabels()
{
	label[0]->SetText("Hp: " + to_string(player->health.current) + "/" +
		to_string(player->health.maximum));
	label[1]->SetText("Level: " + to_string(player->level));
}
void StatScreen::Draw(RenderTarget & target)
{
	target.draw(boarder);
	target.draw(window);
	for (size_t i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Draw(target);
	}
	for (size_t i = 0; i < label.size(); i++)
	{
		label[i]->Draw(target);
	}
}
void StatScreen::CheckButtonInst(Button & button)
{
	if (button.GetButtonInstance() == elem::idle)
		button.ShowToolTip(false);
	else if (button.GetButtonInstance() == elem::hover)
		button.ShowToolTip(true);
	else if (button.GetButtonInstance() == elem::onclick)
	{
		if (clicktimer > 0.2)
		{
			switch (button.GetButtonId())
			{
			case 0:

				break;
			case 1:

				break;
			case 2:

				break;


			default:
				break;
			}
			clicktimer = 0;
		}
	}
}

///////////////////////////////////////////////////////////

BuildScreen::BuildScreen()
{
	
	/*this->building.push_back(new Mine(Vector2f(2, 600), obj::Iron));
	this->building.push_back(new Mine(Vector2f(2+66,600),obj::Stone));
	this->building.push_back(new Mine(Vector2f(2, 600-66), obj::Wood));
	this->building.push_back(new Mine(Vector2f(2+66, 600 - 66), obj::Gold));
*/
	this->resourcesText.setFont(Resources::font);
	this->resourcesText.setCharacterSize(24);
	this->resourcesText.setFillColor(Color::Black);

	this->priceText.setFont(Resources::font);
	this->priceText.setCharacterSize(24);
	this->priceText.setFillColor(Color::Red);
	this->priceText.setPosition(0, 30);
	
	//selector = new Mine();

	RectangleShape temp;
	//Minimap
	temp.setSize(Vector2f(200, 200));
	temp.setPosition(2, 768-202);
	temp.setFillColor(Color(70, 70, 70, 255));
	temp.setOutlineThickness(2);
	modules.push_back(temp);//push
	//Portret
	temp.setSize(Vector2f(160, 160));
	temp.setPosition(204, 768-162);
	modules.push_back(temp);//push
	//Icons
	temp.setSize(Vector2f(321, 106));
	temp.setPosition(366, 768-108);
	modules.push_back(temp);//push
	//Buttons
	temp.setSize(Vector2f(158, 158));
	temp.setPosition(689, 768-160);
	modules.push_back(temp);//push

	/*for (size_t i = 0,x = 0,y = 0; i < 9; i++)
	{
		if (x == 3)
		{
			x = 0;
			y++;
		}
		button.push_back(new Button(Vector2f(50, 50), Vector2f(970 + (54*x), 302 + (54*y)), Mine::mineTexture, IntRect(29, 43, 220, 200), i));
		x++;
	}*/
	
	//for (size_t i = 0,y = 0,x = 0; i < 12; i++,x++)
	//{
	//	if (i == 6)
	//	{
	//		x = 0;
	//		y++;
	//	}
	//	temp.setSize(Vector2f(50, 50));
	//	temp.setPosition(366+(54*x)+2, 340+(54*y)+2);
	//	temp.setFillColor(Color::Red);
	//	temp.setOutlineThickness(1);
	//	modules.push_back(temp);//push
	//	
	//}

}
void BuildScreen::Update(Vector2f mouse, const float & time)
{
	if(clicktimer<clicktimerMax)
	clicktimer += time;

	selector.Update((Vector2f)mouse,time);
	
	//Buildings
	for (size_t i = 0; i < Building::building.size(); i++)
	{
		Building::building[i]->Update(mouse, time);
		if (Building::building[i]->life == false)
		{
			selector.Clear(Building::building[i]->GetId());
			delete Building::building[i];
			Building::building.erase(Building::building.begin()+i);
		}
	}
	for (size_t i = 0; i < Unit::unit.size(); i++)
	{
		Unit::unit[i]->Update(mouse,time);
	}

	/*for (size_t i = 0; i < building.size(); i++)
	{
		building[i]->UpdateIcon((Vector2f)mouse, time);
		CheckIconsInst(*building[i]);
	}*/
	
	for (size_t i = 0; i < button.size(); i++)
	{
		button[i]->Update((Vector2i)mouse, time);
		CheckButtonInst(*button[i]);
	}
	/*if (selector != 0)
	{
		selector->AtSelector((Vector2f)mouse);
	}*/

	this->resourcesText.setString(to_string(Shell::resources[0]) + " | " +
		to_string(Shell::resources[1]) + " | " +
		to_string(Shell::resources[2]) + " | " +
		to_string(Shell::resources[3]));

	/*if (selector != 0)
	{
		this->priceText.setString(to_string(selector->price[0]) + " | " +
			to_string(selector->price[1]) + " | " +
			to_string(selector->price[2]) + " | " +
			to_string(selector->price[3]));
	}*/
}
void BuildScreen::Draw(RenderTarget & target)
{
	for (size_t i = 0; i < modules.size(); i++)
	{
		target.draw(modules[i]);
	}

	
	for (size_t i = 0; i < button.size(); i++)
	{
		button[i]->Draw(target);
	}
	/*if (selector != 0)
	{
		selector->Draw(target);
	}*/

	target.draw(this->resourcesText);
	target.draw(this->priceText);
	
	selector.Draw(target);
}
void BuildScreen::CheckButtonInst(Button & button)
{
	
	
}
void BuildScreen::CheckIconsInst(Building & building)
{
}
void BuildScreen::Controls(Vector2f mouse,Event & event)
{
	
	//if (clicktimer > clicktimerMax)
	//{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if(!selector.GetDragOn())
			selector.DragOn(mouse,true);
			if (clicktimer > clicktimerMax)
			{
				selector.LeftAction((Vector2f)mouse);
				clicktimer = 0;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			if (clicktimer > clicktimerMax)
			{
				clicktimer = 0;
				selector.RightAction((Vector2f)mouse);
			}
		}

		if (event.type == Event::MouseButtonReleased)
		{
			if (event.key.code == Mouse::Left)
			{
				selector.DragOn(mouse,false);
			}
		}
	//}

	//Temp buttons
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		selector.SwitchCommand(sel::None);
		clicktimer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		selector.SwitchCommand(obj::Mine_Stone);
		clicktimer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		selector.SwitchCommand(obj::Mine_Gold);
		clicktimer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::X))
	{
		selector.Clear();
		ChangeActivity();
		clicktimer = 0;
	}
}
void BuildScreen::SpawnBuilding(Vector2f mouse, obj::Type type)
{

	Building::building.push_back(new Mine(mouse, type));
	for (size_t i = 0; i < 4; i++)
	{
		Shell::resources[i] -= Building::building[Building::building.size() - 1]->price[i];
	}

	switch (type)
	{
	case obj::Mine_Iron:
			break;
	case obj::Mine_Stone:
		break;
	case obj::Mine_Wood:
		break;
	case obj::Mine_Gold:
		break;

	}
	
}