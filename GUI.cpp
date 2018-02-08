#include "GUI.h"

enum enum_GUI
{
	enum_HPBar,
	enum_AmmoBar,
	enum_ReloadBar,
	enum_ExpBar
};

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::InitGUI(Vector2u winsize)
{
	RectangleShape temp;
	//Static Bars//

	//HealthBar
	temp.setSize(Vector2f(200, 20));
	temp.setFillColor(Color::Black);
	temp.setPosition(10, winsize.y - temp.getSize().y - 10);
	this->staticBars.push_back(temp);
	//AmmoBar
	temp.setSize(Vector2f(200, 20));
	temp.setFillColor(Color::Black);
	temp.setPosition(winsize.x - temp.getSize().x-165, winsize.y - temp.getSize().y - 10);
	this->staticBars.push_back(temp);
	//ExpBar
	temp.setSize(Vector2f(200, 10));
	temp.setFillColor(Color::Black);
	temp.setPosition(10, winsize.y - temp.getSize().y - 33);
	this->staticBars.push_back(temp);

	//DynamicBars//

	//HealthBar
	temp.setSize(Vector2f(200, 20));
	temp.setFillColor(Color::Red);
	temp.setPosition(10, winsize.y - temp.getSize().y - 10);
	this->dynamicBars.push_back(temp);
	//AmmoBar
	temp.setSize(Vector2f(-200, 20));
	temp.setFillColor(Color::Blue);
	temp.setPosition(winsize.x - temp.getSize().x - 365, winsize.y - temp.getSize().y - 10);
	this->dynamicBars.push_back(temp);
	//ReloadBar
	temp.setSize(Vector2f(0, 20));
	temp.setFillColor(Color::Yellow);
	temp.setPosition(winsize.x - temp.getSize().x - 165, winsize.y - temp.getSize().y - 10);
	this->dynamicBars.push_back(temp);
	//ExpBar
	temp.setSize(Vector2f(200, 10));
	temp.setFillColor(Color::Yellow);
	temp.setPosition(10, winsize.y - temp.getSize().y - 33);
	this->dynamicBars.push_back(temp);

	//Text
	Text text;
	text.setFont(Resources::font);
	text.setCharacterSize(18);
	text.setFillColor(Color::Black);
	//AmmoText
	text.setPosition(winsize.x - 200, winsize.y - 50);
	this->textFields.push_back(text);

	//HealthText
	text.setFillColor(Color(50, 50, 50, 255));
	this->textFields.push_back(text);
	
	//Press To take TEXT
	
	text.setString(Resources::strings[str_Press_to_take]);
	text.setPosition(winsize.x / 2 - text.getLocalBounds().width/2, winsize.y - 50);
	this->textFields.push_back(text);

	//Weapon Ammo text
	text.setFillColor(Color(50, 50, 50, 255));
	this->textFields.push_back(text);

	text.setFillColor(Color(50, 50, 50, 255));
	this->textFields.push_back(text);

	//Time text
	text.setCharacterSize(24);
	text.setFillColor(Color(50,50,50,255));
	this->textFields.push_back(text);

	//test
	testtex1.loadFromFile("Textures/Background/back_03.jpg");//
	test1.setTexture(&testtex1);
	test1.setRadius(150);
	test1.setOrigin(test1.getRadius(), test1.getRadius());
	test1.setPosition((Vector2f)winsize);
	test1.setFillColor(Color(255, 255, 255, 200));
	test1.setOutlineThickness(5);
	test1.setOutlineColor(Color(50, 50, 50, 200));

	/*test2.setRadius(100);
	test2.setFillColor(Color::Blue);
	test2.setOrigin(test2.getRadius(), test2.getRadius());
	test2.setPosition(winsize.x,winsize.y-150);*/
}
void GUI::Update(const Player*player,Vector2u winsize,const float & time)
{
	//Health Bar
	this->dynamicBars[enum_GUI::enum_HPBar].setSize(Vector2f(200*((float)player->health.current/player->health.maximum),20));
	
	//Ammo Bar
	if(!player->inhand->RELOAD)
	this->dynamicBars[enum_GUI::enum_AmmoBar].setSize(Vector2f(-200 * ((float)player->inhand->magazine.current / player->inhand->magazine.maximum), 20));
	else
		this->dynamicBars[enum_GUI::enum_AmmoBar].setSize(Vector2f(0, 20));

	//ExpBar
	this->dynamicBars[enum_GUI::enum_ExpBar].setSize(Vector2f(200 * ((float)player->xp / player->xpNext), 10));

	//Reload Bar
	this->dynamicBars[enum_ReloadBar].setSize(Vector2f(-200 + (200*(player->inhand->reload.current/player->inhand->reload.maximum)),20));
	
	//Player ammo Text
	textFields[0].setString(to_string(player->ammo[player->inhand->ammoType]));
	//Health Text
	textFields[1].setString(to_string(player->health.current)+"/"+to_string(player->health.maximum));
	//Weapon ammo Text
	textFields[3].setString(to_string(player->inhand->magazine.current) + "/" + to_string(player->inhand->magazine.maximum));
	//Lvl Text
	textFields[4].setString("Lvl: " + to_string(player->level));
	textFields[4].setPosition(10, winsize.y - 65);
	//Health
	textFields[1].setPosition(SetOnMidle(staticBars[0].getGlobalBounds(), textFields[1]).x,
		staticBars[0].getPosition().y-2);
	//Ammo
	textFields[3].setPosition(SetOnMidle(staticBars[1].getGlobalBounds(), textFields[3]).x,
		staticBars[1].getPosition().y - 2);

	//Time Text
	textFields[5].setPosition((winsize.x / 2) - (textFields[5].getLocalBounds().width / 2), 12);

	//Weapons Icons
	for (size_t i = 0; i < player->weapons.size(); i++)
	{
		if (i == player->weaponsIndex)
		{
			player->weapons[i]->sprite.setColor(Color(0, 255, 0, 255));
			player->weapons[i]->sprite.setScale(1.2, 1.2);
			player->weapons[i]->sprite.setPosition(winsize.x - player->weapons[i]->sprite.getGlobalBounds().width-45, winsize.y-75);
		}
		else
		{
			
			player->weapons[i]->sprite.setScale(0.8, 0.8);
			player->weapons[i]->sprite.setColor(Color::White);
			player->weapons[i]->sprite.setPosition(winsize.x - player->weapons[i]->sprite.getGlobalBounds().width - 10, winsize.y - 125);
		}
	}
	
	//Check that player stay on Weapon bonus
	if (Weapons::weapons.size() > 0)
		for (size_t i = 0; i < Weapons::weapons.size(); i++)
		{
			if (player->Intersects(Weapons::weapons[i]->GetBound()))
			{
				onWeapon = true;
				break;
			}
			else
				onWeapon = false;
		}
	else
		onWeapon = false;
}
void GUI::Draw(Player * player,RenderTarget & target)
{
	//Circles 
	target.draw(test1);
	
	for (size_t i = 0; i < player->weapons.size(); i++)
	{
		target.draw(player->weapons[i]->sprite);
	}

	for (size_t i = 0; i < this->staticBars.size(); i++)
	{
		target.draw(this->staticBars[i]);
	}
	for (size_t i = 0; i < this->dynamicBars.size(); i++)
	{
		target.draw(this->dynamicBars[i]);
	}
	/*for (size_t i = 0; i < this->textFields.size(); i++)
	{
		target.draw(this->textFields[i]);
	}*/

	//Ammo text
	target.draw(this->textFields[0]);
	//Health text
	target.draw(this->textFields[1]);
	//Weapon ammo text
	target.draw(this->textFields[3]);
	target.draw(this->textFields[4]);
	target.draw(this->textFields[5]);

	//Press to take text
	if (onWeapon)
		target.draw(this->textFields[2]);

}
void GUI::UpdateGameTime(const float gametime[])
{
	if(gametime[0]<10)
	textFields[5].setString(to_string((int)gametime[1]) + ":0" + to_string((int)gametime[0]));
	else
	textFields[5].setString(to_string((int)gametime[1]) + ":" + to_string((int)gametime[0]));
}
