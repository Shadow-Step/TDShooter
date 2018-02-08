#include "Screen.h"

vector<Screen::Button*>Screen::button;

Screen::Screen()
{
	for (size_t i = 0; i < 12; i++)
	{
		Screen::button.push_back(new Button(Vector2f(150, 20), i));
	}
	texture1.loadFromFile("Textures/Background/back_03.jpg");//
	texture2.loadFromFile("Textures/Background/back_01.png");//
	

	this->menuBoard.setTexture(&texture2);//
	this->menuBoard.setSize(Vector2f(560, 200));
	this->menuBoard.setPosition(290, 190);

	this->menu.setTexture(&texture1);//
	this->menu.setSize(Vector2f(menuBoard.getSize().x-11, menuBoard.getSize().y-21));
	this->menu.setFillColor(Color(255, 255, 255, 255));//
	this->menu.setPosition(menuBoard.getPosition().x+5, menuBoard.getPosition().y+11);

	text.setFont(Resources::font);
	text.setCharacterSize(16);
	text.setFillColor(Color(136,136,136,255));
	
	this->dragMenu = false;
	this->buttonview = 0;
	this->buttonsOnScreen = 8;
	this->clickTimerMax = 0.2;
	this->clickTimer = 0.2;
}
Screen::~Screen()
{
}
void Screen::Update(Player *player,Vector2f mousePos,const float & time)
{
	if (menuBoard.getGlobalBounds().contains(mousePos) && !menu.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left) && dragMenu == false && ClickTimerReady())
	{
		dragMenu = true;
		rememberPos = mousePos;
		clickTimer = 0;
	}
	if (dragMenu)
	{
		if (Mouse::isButtonPressed(Mouse::Left) && ClickTimerReady())
		{
			dragMenu = false;
			clickTimer = 0;
		}
		menuBoard.setPosition(menuBoard.getPosition().x + (mousePos.x - rememberPos.x), menuBoard.getPosition().y + (mousePos.y - rememberPos.y));
		menu.setPosition(menuBoard.getPosition().x + 5, menuBoard.getPosition().y + 11);
		text.setPosition(menu.getPosition().x + menu.getLocalBounds().width - 150, menu.getPosition().y + menu.getLocalBounds().height - 20);
		rememberPos = mousePos;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down) && ClickTimerReady())
	{
		SetButtonsView(1);
		this->clickTimer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && ClickTimerReady())
	{
		SetButtonsView(-1);
		this->clickTimer = 0;
	}
	//End temp

	clickTimer += time;
	int temp = this->buttonview + this->buttonsOnScreen;
	int tempindex = 0;
	for (size_t i = buttonview; i < temp; i++)
	{
		Screen::button[i]->Update(menu.getPosition(), tempindex);

		if (Screen::button[i]->Contains(mousePos))
			Screen::button[i]->ChangeInstance(enum_Instances::enum_ONMOUSE);
		else if (!Screen::button[i]->Contains(mousePos))
			Screen::button[i]->ChangeInstance(enum_Instances::enum_IDLE);
		
		if (Screen::button[i]->Contains(mousePos) && Mouse::isButtonPressed(Mouse::Left) && this->ClickTimerReady())
			Screen::button[i]->ChangeInstance(enum_Instances::enum_ONCLICK);
		tempindex++;
	}
	CheckInstances(player);

	
	//Static Text
	text.setString(Resources::strings[str_PerkPoints] + to_string(player->GetPerkPoints()));
	text.setPosition(menu.getPosition().x + menu.getLocalBounds().width - text.getLocalBounds().width - 5, 
					 menu.getPosition().y + menu.getLocalBounds().height - text.getLocalBounds().height-5);
}
void Screen::Draw(RenderTarget & target)
{
	
	target.draw(menuBoard);
	target.draw(menu);
	target.draw(text);
	int temp = this->buttonview + this->buttonsOnScreen;
	for (size_t i = buttonview; i < temp ; i++)
	{
		Screen::button[i]->Draw(target);
	}
}
void Screen::SetButtonsView(int iterator)
{
	cout << iterator << endl;
	this->buttonview += iterator;
	if (this->buttonview + this->buttonsOnScreen > Screen::button.size())
	{
		this->buttonview = Screen::button.size() - this->buttonsOnScreen;
	}
	else if (this->buttonview < 0)
		this->buttonview = 0;
}
void Screen::CheckInstances(Player *player)
{
	for (size_t i = 0; i < Screen::button.size(); i++)
	{
		if (Screen::button[i]->GetInstance() == enum_Instances::enum_ONCLICK)
		{
			switch (Screen::button[i]->GetType())
			{
			case 0:
				player->AddPerk(perk::enum_Evasion);
				this->clickTimer = 0;
				Screen::button[i]->ChangeInstance(enum_Instances::enum_ONMOUSE);
				
				break;
			case 1:
				player->AddPerk(perk::enum_FastReload);
				this->clickTimer = 0;
				Screen::button[i]->ChangeInstance(enum_Instances::enum_ONMOUSE);
				
				break;
			case 2:
				player->AddPerk(perk::enum_Ricochet);
				this->clickTimer = 0;
				Screen::button[i]->ChangeInstance(enum_Instances::enum_ONMOUSE);
				
				break;
			case 3:
				player->AddPerk(perk::enum_Melle);
				this->clickTimer = 0;
				Screen::button[i]->ChangeInstance(enum_Instances::enum_ONMOUSE);
				
				break;
			case 4:
				player->AddPerk(perk::enum_Vampirism);
				this->clickTimer = 0;
				Screen::button[i]->ChangeInstance(enum_Instances::enum_ONMOUSE);
				
				break;

			default:
				break;
			}
		}
		else if (Screen::button[i]->GetInstance() == enum_Instances::enum_ONMOUSE)
		{
			Screen::button[i]->ChangeTextColor(Color::White);
		}
		else if (Screen::button[i]->GetInstance() == enum_Instances::enum_IDLE)
		{
			Screen::button[i]->ChangeTextColor(Color(136,136,136,255));
		}
		
	}
}

//Buttons
Screen::Button::Button(Vector2f size,int type)
{
	texture.loadFromFile("Textures/Background/back_01.png");//
	this->button.setTexture(&texture);//

	this->size = size;
	text.setFont(Resources::font);
	text.setCharacterSize(14);
	text.setFillColor(Color::Blue);

	info.setFont(Resources::font);
	info.setCharacterSize(12);
	info.setFillColor(Color(200,200,200,255));

	this->button.setSize(size);
	this->type = type;

	if(type<Resources::perksNames.size())
	this->text.setString(Resources::perksNames[type]);
	if (type<Resources::perksInfo.size())
	this->info.setString(Resources::perksInfo[type]);

}
void Screen::Button::Draw(RenderTarget & target)
{
	target.draw(this->button);
	target.draw(this->text);
	target.draw(aaa);
	target.draw(bbb);
	if(this->instance == enum_Instances::enum_ONMOUSE)
	target.draw(this->info);
}
void Screen::Button::Update(const Vector2f & menuPosition,const int &buttonNumber)
{
	this->button.setPosition(menuPosition.x, menuPosition.y+(buttonNumber * 22)+3);
	this->text.setPosition(button.getPosition().x+5, button.getPosition().y);
	//this->text.setPosition(menuPosition.x+5, menuPosition.y+(buttonNumber*22)+3);
	this->info.setPosition(menuPosition.x + this->size.x+5, menuPosition.y);
}

/////////////////////////////////////////////
GameLoop::GameLoop(RenderWindow * window,inst::GameStages * currentStage)
{
	this->window = window;
	this->cursor = new Cursor(0);

	this->winsize = (Vector2f)window->getSize();
	this->currentStage = currentStage;
	
	InitResources();

	Objects::InitTextures();

	gui.InitGUI(window->getSize());
	player = new Player();
	perkScreen = new Screen();

	this->stageName = inst::gameloop;

	this->tex.loadFromFile("Textures/Background/back_04.jpg");//temp
	this->background.setTexture(tex);//temp
	this->background.setTextureRect(IntRect(0, 0, window->getSize().x, window->getSize().y));//temp

	this->gametime[0] = 0;
	this->gametime[1] = 0;
	this->gametime[2] = 0;
	this->reset = false;
	this->inventory = new BuildScreen();
	Building::building.push_back(new Mine(Vector2f(150, 150), obj::Type::Mine_Gold));
	
}
GameLoop::~GameLoop()
{
	delete player;
	delete cursor;
}
void GameLoop::Update(const float &time)
{
	cursor->Update(Mouse::getPosition(*window));
	if (!freeze && reset && !inventory->IsActive())//reset timer after constructor
	{
		IncTime(this->gametime, time);
		UpdatePlayer(time);
		UpdateEnemies(time);
		UpdateDynamicObjects(time);
		UpdateParticles(time);
		UpdateBonuses(time);
		
		UpdateAllies(time);
		UpdateBuildings(time);

		gui.UpdateGameTime(this->gametime);
		gui.Update(player, window->getSize(), time);
		Spawner(time);
	}
	reset = true;
	
	UpdateDynamicText(time);

	if (freeze)
		perkScreen->Update(player, (Vector2f)Mouse::getPosition(*window), time);
	if(inventory->IsActive())
	inventory->Update((Vector2f)Mouse::getPosition(*window), time);

#ifdef DEBUG
	cout << Enemy::enemy.size() << " "
		<< DynamicObjects::dynamic.size() << " "
		<< Particles::particles.size() << " "
		<< Bonuses::bonuses.size() << " "
		<< DynamicText::dynamictext.size() << endl;
#endif // DEBUG

}
void GameLoop::UpdatePlayer(const float & time)
{
	player->Update(time);

	if (player->GetPosition().x > winsize.x)
		player->sprite.setPosition(winsize.x - player->GetBound().width, player->GetPosition().y);
	else if (player->GetPosition().x < 0)
		player->sprite.setPosition(0 + player->GetBound().width, player->GetPosition().y);
	if (player->GetPosition().y > winsize.y)
		player->sprite.setPosition(player->GetPosition().x, winsize.y - player->GetBound().height);
	else if (player->GetPosition().y < 0)
		player->sprite.setPosition(player->GetPosition().x, 0 + player->GetBound().height);



	if (player->shoot)
		player->Shoot(Mouse::getPosition(*window));

	player->SetRotation(-CountAngle((Vector2f)Mouse::getPosition(*window),
		player->GetPosition()) + 270);
	player->feets.setRotation(-CountAngle((Vector2f)Mouse::getPosition(*window),
		player->GetPosition()) + 270);

	//Enemy collision
	for (size_t i = 0; i < Enemy::enemy.size(); i++)
	{
		if (player->Intersects(Enemy::enemy[i]->GetBound()))
		{
			if (Enemy::enemy[i]->ReadyToAttack() && player->HitTimerReady())
			{
				if (Enemy::enemy[i]->GetCurrentAnimation() != _Melle)
					Enemy::enemy[i]->SwitchAnimation(_Melle);

				player->TakeDamage(Enemy::enemy[i]->GetDamage());
				Enemy::enemy[i]->ResetHitrate();

				if (player->PerkExist(perk::enum_Melle))
				{
					Enemy::enemy[i]->TakeDamage(player->GetDamage());
					DynamicText::dynamictext.push_back(new DynamicText("-" + to_string(player->GetDamage()),
						Enemy::enemy[i]->GetPosition(),
						Vector2f(0, -1),
						Color::Cyan,
						16,
						200.f,
						300.f,
						1.f,
						1.f));
				}
			}
		}

	}

	//Bonuses collision
	for (size_t i = 0; i < Bonuses::bonuses.size(); i++)
	{
		if (Bonuses::bonuses[i]->IsAlive())
			if (player->Intersects(Bonuses::bonuses[i]->GetBounds()))
			{
				switch (Bonuses::bonuses[i]->GetType())
				{
				case bonus::health_pack:
					player->TakeHeal(25);
					Bonuses::bonuses[i]->PickUp();
					break;
				case bonus::ammo_pack:
					player->TakeAmmo();
					Bonuses::bonuses[i]->PickUp();
					break;
				case bonus::speedBooster:
					Bonuses::bonuses[i]->PickUp();
					player->SetSpeedMod(2);
					break;
				case bonus::cuttingBullets:
					Bonuses::bonuses[i]->PickUp();
					DynamicObjects::cuttingBullets = true;
					break;
				case bonus::dronSpawner:
					Bonuses::bonuses[i]->PickUp();
					Dron::dron.push_back(new Dron(player->GetPosition()));
					
					break;
				default:
					break;
				}
			}
	}

	//Weapons collision
	for (size_t i = 0; i < Weapons::weapons.size(); i++)
	{
		if (Weapons::weapons[i]->IsAlive())
		{
			if (player->Intersects(Weapons::weapons[i]->GetBound()) && Keyboard::isKeyPressed(Keyboard::Z))
			{
				player->TakeWeapon(Weapons::weapons[i]);
				Weapons::weapons.erase(Weapons::weapons.begin() + i);
			}
		}
		else
		{
			delete Weapons::weapons[i];
			Weapons::weapons.erase(Weapons::weapons.begin() + i);
		}
	}
}
void GameLoop::UpdateEnemies(const float & time)
{
	for (size_t i = 0; i < Enemy::enemy.size(); i++)
	{
		Enemy::enemy[i]->Update(time);
		if (!Enemy::enemy[i]->IsAlive())
		{
			player->GainXp(Enemy::enemy[i]->CountXp());
			if (Enemy::enemy[i]->IsBoss())
			{
				for (size_t i = 0; i < 3; i++)
				{
					switch (rand() % 5 + 1)
					{
					case 1:
						Bonuses::bonuses.push_back(new MedPack());
						break;
					case 2:
						Bonuses::bonuses.push_back(new AmmoPack());
						break;
					case 3:
						Bonuses::bonuses.push_back(new CuttingBullets());
						break;
					case 4:
						Bonuses::bonuses.push_back(new SpeedBooster());
						break;
					case 5:
						Bonuses::bonuses.push_back(new DronSpawner());
						break;
					default:
						throw("Out of bonus spawn range!");
						break;
					}
				}
			}
			delete Enemy::enemy[i];
			Enemy::enemy.erase(Enemy::enemy.begin() + i);
		}

	}
}
void GameLoop::UpdateDynamicObjects(const float & time)
{
	//Bullets
	for (size_t i = 0; i < DynamicObjects::dynamic.size(); i++)
	{
		if (DynamicObjects::dynamic[i]->IsAlive())
		{
			DynamicObjects::dynamic[i]->Update(time);


			for (size_t k = 0; k < Enemy::enemy.size(); k++)
			{
				if (DynamicObjects::dynamic[i]->Intersects(Enemy::enemy[k]->GetBound()) &&
					!DynamicObjects::dynamic[i]->CheckTargetId(Enemy::enemy[k]->GetId()))
				{
					DynamicObjects::dynamic[i]->AddTargetId(Enemy::enemy[k]->GetId());
					Enemy::enemy[k]->TakeDamage(DynamicObjects::dynamic[i]->GetDamage());
					if (player->PerkExist(perk::enum_Vampirism))
						player->TakeHeal(DynamicObjects::dynamic[i]->GetDamage() / 10);

					Particles::Generate(DynamicObjects::dynamic[i]->GetPosition(),
						DynamicObjects::dynamic[i]->GetCurrentSpeed(),
						1,
						10,
						0.7);
					if (player->PerkExist(perk::enum_Ricochet) && DynamicObjects::dynamic[i]->GetRicCharges() > 0 && DynamicObjects::cuttingBullets == false)
					{
						DynamicObjects::dynamic[i]->SetRicCharges();
						DynamicObjects::dynamic[i]->ChangeTarget(Vector2f(rand() % window->getSize().x, rand() % window->getSize().y));
					}
					else
					{
						if (DynamicObjects::cuttingBullets == false)
						{
							DynamicObjects::dynamic[i]->SetAlive(false);
							break; // BREAK!!!!!!
						}
					}
				}
			}
		}
		else
		{
			delete DynamicObjects::dynamic[i];
			DynamicObjects::dynamic.erase(DynamicObjects::dynamic.begin() + i);
		}
	}

	//AIBullets
	for (size_t i = 0; i < AIBullet::aibullet.size(); i++)
	{
		if (AIBullet::aibullet[i]->IsAlive())
		{
			if (!AIBullet::aibullet[i]->TargetSelected() && Enemy::enemy.size() > 0 && AIBullet::aibullet[i]->GetLifeTime() > 0.3)
			{
				AIBullet::aibullet[i]->SetTarget(GetNearestTargetID(AIBullet::aibullet[i]->GetPosition()));
			}
			AIBullet::aibullet[i]->Update(time);

			for (size_t k = 0; k < Enemy::enemy.size(); k++)
			{
				if (Enemy::enemy[k]->GetId() == AIBullet::aibullet[i]->GetTargetID() &&
					Enemy::enemy[k]->IsAlive())
				{
					AIBullet::aibullet[i]->UpdateMoveCords(Enemy::enemy[k]->GetPosition());
				}
				else
				{
					AIBullet::aibullet[i]->NoTarget();
				}

				if (AIBullet::aibullet[i]->Intersects(Enemy::enemy[k]->GetBound()) &&
					!AIBullet::aibullet[i]->CheckTargetId(Enemy::enemy[k]->GetId()))
				{
					AIBullet::aibullet[i]->AddTargetId(Enemy::enemy[k]->GetId());
					Enemy::enemy[k]->TakeDamage(AIBullet::aibullet[i]->GetDamage());

					Particles::Generate(AIBullet::aibullet[i]->GetPosition(),
						AIBullet::aibullet[i]->GetCurrentSpeed(),
						1,
						10,
						0.7);

					AIBullet::aibullet[i]->SetAlive(false);
					break; //BREAK!!!!!
				}
			}
		}
		else if (!AIBullet::aibullet[i]->IsAlive())
		{
			delete AIBullet::aibullet[i];
			AIBullet::aibullet.erase(AIBullet::aibullet.begin() + i);
		}
	}

	//Rockets
	for (size_t i = 0; i < Rocket::rocket.size(); i++)
	{
		if (Rocket::rocket[i]->IsAlive())
		{
			Rocket::rocket[i]->Update(time);
			for (size_t k = 0; k < Enemy::enemy.size(); k++)
			{
				if (Rocket::rocket[i]->Intersects(Enemy::enemy[k]->GetBound()))
				{
					Splash::splash.push_back(new Splash(Rocket::rocket[i]->GetPosition(), Vector2f(1.3, 1.3), 150.f, Rocket::rocket[i]->GetDamage(), 0.5, 28));
					Rocket::rocket[i]->SetAlive(false);
					break; //BREAK!!!
				}
			}
		}
		else
		{
			if (Rocket::rocket[i]->TimerIsEnd())
			{
				Splash::splash.push_back(new Splash(Rocket::rocket[i]->GetPosition(), Vector2f(1.3, 1.3), 150.f, Rocket::rocket[i]->GetDamage(), 0.5, 28));
			}
			delete Rocket::rocket[i];
			Rocket::rocket.erase(Rocket::rocket.begin() + i);
		}
	}

	//Splash
	for (size_t i = 0; i < Splash::splash.size(); i++)
	{
		if (Splash::splash[i]->IsAlive())
		{
			Splash::splash[i]->Update(time);
			for (size_t k = 0; k < Enemy::enemy.size(); k++)
			{
				if (Splash::splash[i]->Intersects(Enemy::enemy[k]->GetBound()) &&
					!Splash::splash[i]->CheckTargetId(Enemy::enemy[k]->GetId()))
				{
					Splash::splash[i]->AddTargetId(Enemy::enemy[k]->GetId());
					Enemy::enemy[k]->TakeDamage(Splash::splash[i]->GetDamage());
				}
			}
		}
		else
		{
			delete Splash::splash[i];
			Splash::splash.erase(Splash::splash.begin() + i);
		}
	}

	//Enemy bullets
	for (size_t i = 0; i < EnemyBullet::enemybullet.size(); i++)
	{
		EnemyBullet::enemybullet[i]->Update(time);
		if (EnemyBullet::enemybullet[i]->IsAlive())
		{
			if (EnemyBullet::enemybullet[i]->Intersects(player->GetBound()))
			{
				player->TakeDamage(EnemyBullet::enemybullet[i]->GetDamage());
				EnemyBullet::enemybullet[i]->SetAlive(false);
			}
		}
		else
		{
			delete EnemyBullet::enemybullet[i];
			EnemyBullet::enemybullet.erase(EnemyBullet::enemybullet.begin() + i);
		}
	}
}
void GameLoop::UpdateBonuses(const float &time)
{
	for (size_t i = 0; i < Bonuses::bonuses.size(); i++)
	{
		if (Bonuses::bonuses[i]->IsAlive() || !Bonuses::bonuses[i]->LifeTimeIsEnd())
		{
			Bonuses::bonuses[i]->Update(time);
		}
		else if (!Bonuses::bonuses[i]->IsAlive() && Bonuses::bonuses[i]->LifeTimeIsEnd())
		{
			if (Bonuses::bonuses[i]->GetType() == bonus::cuttingBullets)
				DynamicObjects::cuttingBullets = false;
			if (Bonuses::bonuses[i]->GetType() == bonus::speedBooster)
				player->SetSpeedMod(1);

			delete Bonuses::bonuses[i];
			Bonuses::bonuses.erase(Bonuses::bonuses.begin() + i);
		}
	}
	for (size_t i = 0; i < Weapons::weapons.size(); i++)
	{
		Weapons::weapons[i]->Update(time);
	}
}
void GameLoop::UpdateDynamicText(const float &time)
{
	for (size_t i = 0; i < DynamicText::dynamictext.size(); i++)
	{
		if (DynamicText::dynamictext[i]->IsAlive())
			DynamicText::dynamictext[i]->Update(time);
		else
		{
			delete DynamicText::dynamictext[i];
			DynamicText::dynamictext.erase(DynamicText::dynamictext.begin() + i);
		}
	}
}
void GameLoop::UpdateParticles(const float & time)
{
	for (size_t i = 0; i < Particles::particles.size(); i++)
	{
		if (Particles::particles[i]->IsAlive())
			Particles::particles[i]->Update(time);
		else
		{
			delete Particles::particles[i];
			Particles::particles.erase(Particles::particles.begin() + i);
		}
	}
}
void GameLoop::UpdateAllies(const float & time)
{
	for (size_t i = 0; i < Dron::dron.size(); i++)
	{
		if (Dron::dron[i]->GetDurationLife())
		{
			if (!Dron::dron[i]->TargetSelected() && Enemy::enemy.size() > 0)
			{
				int id = this->GetNearestTargetID(Dron::dron[i]->GetPosition());
				for (size_t k = 0; k < Enemy::enemy.size(); k++)
				{
					if (Enemy::enemy[k]->GetId() == id)
					{
						Dron::dron[i]->SetTarget(Enemy::enemy[k]);
					}
				}
			}
			else
			{
				Dron::dron[i]->Update(time);
			}
		}
		else
		{
			delete Dron::dron[i];
			Dron::dron.erase(Dron::dron.begin() + i);
		}
	}
}
void GameLoop::UpdateBuildings(const float & time)
{
	for (size_t i = 0; i < Building::building.size(); i++)
	{
		Building::building[i]->Update((Vector2f)Mouse::getPosition(*window),time);
	}
	for (size_t i = 0; i < Unit::unit.size(); i++)
	{
		Unit::unit[i]->Update((Vector2f)Mouse::getPosition(*window), time);
	}
}
void GameLoop::Spawner(const float & time)
{
	static Vector2f position;
	static float bonustimer;
	static float weapontimer;

	static float bugtimer;
	static float zombietimer;
	static float insectoidtimer;
	static float bugtimerMax = 4;
	static float zombietimerMax = 2;
	static float insectoidtimerMax = 5;

	zombietimer += time;
	bugtimer += time;
	insectoidtimer += time;
	bonustimer += time;
	weapontimer += time;


	switch (rand() % 4 + 1)
	{
	case 1:
		position.x = 0;
		position.y = rand() % window->getSize().y;
		break;
	case 2:
		position.x = window->getSize().x;
		position.y = rand() % window->getSize().y;
		break;
	case 3:
		position.x = rand() % window->getSize().x;
		position.y = 0;
		break;
	case 4:
		position.x = rand() % window->getSize().y;
		position.y = window->getSize().y;
		break;
	default:
		break;
	}

	//Enemy
	if (zombietimer>zombietimerMax)
	{
		Enemy::enemy.push_back(new Zombie(position, player));
		zombietimer = 0;
		if (zombietimerMax > 0.3)
			zombietimerMax -= 0.05;
	}
	if (bugtimer > bugtimerMax)
	{
		Enemy::enemy.push_back(new Bug(position, player));
		bugtimer = 0;
		if (bugtimerMax > 0.6)
			bugtimerMax -= 0.02;
	}
	if (insectoidtimer > insectoidtimerMax)
	{
		Enemy::enemy.push_back(new Insectoid(position, player));
		insectoidtimer = 0;
		if (insectoidtimerMax > 0.07)
			insectoidtimerMax -= 0.02;
	}

	//Bonuses
	if (bonustimer > 10)
	{
		switch (rand() % 5 + 1)
		{
		case 1:
			Bonuses::bonuses.push_back(new MedPack());
			break;
		case 2:
			Bonuses::bonuses.push_back(new AmmoPack());
			break;
		case 3:
			Bonuses::bonuses.push_back(new CuttingBullets());
			break;
		case 4:
			Bonuses::bonuses.push_back(new SpeedBooster());
			break;
		case 5:
			Bonuses::bonuses.push_back(new DronSpawner());
			break;
		default:
			throw("Out of bonus spawn range!");
			break;
		}
		bonustimer = 0;
	}
	//Weapons
	if (weapontimer > 20)
	{
		switch (int x = rand() % 4)
		{
		case 0:
			Weapons::weapons.push_back(new Pistol(Vector2f(rand() % 1000, rand() % 500), rand() % 6));
			break;
		case 1:
			Weapons::weapons.push_back(new ShotGun(Vector2f(rand() % 1000, rand() % 500), rand() % 2));
			break;
		case 2:
			Weapons::weapons.push_back(new Bazzoka(Vector2f(rand() % 1000, rand() % 500), 1, 75, 1, 1));
			break;
		case 3:
			Weapons::weapons.push_back(new AIMachineGun(Vector2f(rand() % 1000, rand() % 500), 1, 18, 0.05, 100));
			break;
		default:
			cout << x << endl;
			throw("OUT OF WEAPONS SPAWN RANGE");
			break;
		}
		weapontimer = 0;
	}
}
int GameLoop::GetNearestTargetID(Vector2f position)
{
	int globaldist = 0;
	int ID = 0;


	for (size_t i = 0; i < Enemy::enemy.size(); i++)
	{
		int posX = Enemy::enemy[i]->GetPosition().x - position.x;
		int posY = Enemy::enemy[i]->GetPosition().y - position.y;
		int distance = sqrt(pow(posX, 2) + pow(posY, 2));
		if (globaldist == 0)
		{
			ID = Enemy::enemy[i]->GetId();
			globaldist = distance;
		}
		if (distance < globaldist)
		{
			globaldist = distance;
			ID = Enemy::enemy[i]->GetId();
		}
	}
	return ID;
}
void GameLoop::Draw()
{
	//Clear
	window->clear(Color::Green);

	//Background draw
	window->draw(this->background);
	//Player draw
	player->Draw(*window);

	//Particles draw
	for (size_t i = 0; i < Particles::particles.size(); i++)
	{
		Particles::particles[i]->Draw(*window);
	}

	//Enemy draw
	for (size_t i = 0; i < Enemy::enemy.size(); i++)
	{
		Enemy::enemy[i]->Draw(*window);
	}

	//Allier draw
	for (size_t i = 0; i < Dron::dron.size(); i++)
	{
		Dron::dron[i]->Draw(*window);
	}

	//Dynamic Objects draw
	for (size_t i = 0; i < DynamicObjects::dynamic.size(); i++)
	{
		DynamicObjects::dynamic[i]->Draw(*window);
	}

	//AIBullet draw
	for (size_t i = 0; i < AIBullet::aibullet.size(); i++)
	{
		AIBullet::aibullet[i]->Draw(*window);
	}

	//Rocket draw
	for (size_t i = 0; i < Rocket::rocket.size(); i++)
	{
		Rocket::rocket[i]->Draw(*window);
	}

	//Splash draw
	for (size_t i = 0; i < Splash::splash.size(); i++)
	{
		Splash::splash[i]->Draw(*window);
	}

	//Enemy bullets draw
	for (size_t i = 0; i < EnemyBullet::enemybullet.size(); i++)
	{
		EnemyBullet::enemybullet[i]->Draw(*window);
	}

	//Bonuses draw
	for (size_t i = 0; i < Bonuses::bonuses.size(); i++)
	{
		if (Bonuses::bonuses[i]->IsAlive())
			Bonuses::bonuses[i]->Draw(*window);
	}

	//Weapons draw
	for (size_t i = 0; i < Weapons::weapons.size(); i++)
	{
		Weapons::weapons[i]->Draw(*window);
	}

	//DynamicText draw
	for (size_t i = 0; i < DynamicText::dynamictext.size(); i++)
	{
		DynamicText::dynamictext[i]->Draw(*window);
	}

	//Buildings draw
	for (size_t i = 0; i < Building::building.size(); i++)
	{
		Building::building[i]->Draw(*window);
	}
	//Units draw
	for (size_t i = 0; i < Unit::unit.size(); i++)
	{
		Unit::unit[i]->Draw(*window);
	}


	//GUI
	if(!inventory->IsActive())
	gui.Draw(player, *window);

	if (freeze)
		perkScreen->Draw(*window);

	if (inventory->IsActive())
		inventory->Draw(*window);

	cursor->Draw(*window);
	//Display
	window->display();
}
void GameLoop::Controls(Event &event)
{
	if (inventory->IsActive())
		inventory->Controls((Vector2f)Mouse::getPosition(*window), event);
	else
	{
		//Mouse
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Mouse::getPosition(*window).y > 0 && Mouse::getPosition(*window).y < window->getSize().y &&
				Mouse::getPosition(*window).x>0 && Mouse::getPosition(*window).x < window->getSize().x)
				player->shoot = true;
		}

		if (event.type == Event::MouseButtonReleased)
		{
			if (event.key.code == Mouse::Left)
				player->shoot = false;
		}
		//Keyboard
		if (event.type == Event::KeyPressed)
		{
			if (Keyboard::isKeyPressed(Keyboard::W))
				player->movement.y = -100;
			if (Keyboard::isKeyPressed(Keyboard::S))
				player->movement.y = 100;
			if (Keyboard::isKeyPressed(Keyboard::A))
				player->movement.x = -100;
			if (Keyboard::isKeyPressed(Keyboard::D))
				player->movement.x = 100;
			if (Keyboard::isKeyPressed(Keyboard::Q))
				player->SwitchWeapon(-1);
			if (Keyboard::isKeyPressed(Keyboard::E))
				player->SwitchWeapon(1);
			if (Keyboard::isKeyPressed(Keyboard::R))
				player->ReloadWeapon();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				SwitchStage(inst::mainmenu);
		}

		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::W)
				player->movement.y = 0;
			if (event.key.code == Keyboard::S)
				player->movement.y = 0;
			if (event.key.code == Keyboard::A)
				player->movement.x = 0;
			if (event.key.code == Keyboard::D)
				player->movement.x = 0;
		}


		//Debug buttons - DELETE after
		if (event.type == Event::KeyPressed)
		{
			if (Keyboard::isKeyPressed(Keyboard::Numpad1))
				player->SwitchAmination(_Move);
			if (Keyboard::isKeyPressed(Keyboard::Numpad2))
				player->SwitchAmination(_Reload);
			if (Keyboard::isKeyPressed(Keyboard::Numpad3))
				player->SwitchAmination(_Shoot);
			if (Keyboard::isKeyPressed(Keyboard::Numpad4))
				player->SwitchAmination(_Melle);
			/*if (Keyboard::isKeyPressed(Keyboard::Num1))
			Enemy::enemy.push_back(new Zombie(player));
			if (Keyboard::isKeyPressed(Keyboard::Num2))
			Enemy::enemy.push_back(new Bug(player));
			if (Keyboard::isKeyPressed(Keyboard::Num3))
			Enemy::enemy.push_back(new Insectoid(player));*/
			if (Keyboard::isKeyPressed(Keyboard::C))
			{
				inventory->ChangeActivity();
				/*if (inventory->IsActive())
					freeze = true;
				else
					freeze = false;*/
			}
			if (Keyboard::isKeyPressed(Keyboard::F))
				Dron::dron.push_back(new Dron(player->GetPosition()));
			if (Keyboard::isKeyPressed(Keyboard::G))
				Bonuses::bonuses.push_back(new AmmoPack());
			if (Keyboard::isKeyPressed(Keyboard::X))
				Bonuses::bonuses.push_back(new CuttingBullets());
			if (Keyboard::isKeyPressed(Keyboard::F2))
			{
				if (freeze == false)
				{
					freeze = true;
					cursor = new Cursor(1);
				}
				else
				{
					freeze = false;
					cursor = new Cursor(0);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				switch (int x = rand() % 4)
				{
				case 0:
					Weapons::weapons.push_back(new Pistol(Vector2f(rand() % 1000, rand() % 500), rand() % 4));
					break;
				case 1:
					Weapons::weapons.push_back(new ShotGun(Vector2f(rand() % 1000, rand() % 500), rand() % 2));
					break;
				case 2:
					Weapons::weapons.push_back(new Bazzoka(Vector2f(rand() % 1000, rand() % 500), 1, 75, 1, 1));
					break;
				case 3:
					Weapons::weapons.push_back(new AIMachineGun(Vector2f(rand() % 1000, rand() % 500), 1, 18, 0.05, 100));
					break;
				default:
					cout << x << endl;
					throw("OUT OF WEAPONS SPAWN RANGE");
					break;
				}

			}
		}
	}
}
void GameLoop::InitResources()
{
	this->tex.loadFromFile("Textures/Background/back_00.jpg");//temp
	this->background.setTexture(tex);//temp
	this->background.setTextureRect(IntRect(0, 0, window->getSize().x, window->getSize().y));//temp
	RectangleShape loading;//
	loading.setPosition(window->getSize().x / 2 - 250, window->getSize().y - 200);//
	loading.setFillColor(Color::Red);//

	RectangleShape loadingback;
	loadingback.setSize(Vector2f(500, 20));
	loadingback.setPosition(window->getSize().x / 2 - 250, window->getSize().y - 200);
	loadingback.setFillColor(Color::Transparent);
	loadingback.setOutlineThickness(5);
	loadingback.setOutlineColor(Color::Black);

	window->draw(background);
	window->draw(loadingback);
	window->draw(loading);
	window->display();


	
	loading.setSize(Vector2f(100, 20));
	window->clear();
	window->draw(background);
	window->draw(loadingback);
	window->draw(loading);
	window->display();

	Resources::InitImages();
	loading.setSize(Vector2f(200, 20));
	window->clear();
	window->draw(background);
	window->draw(loadingback);
	window->draw(loading);
	window->display();

	Resources::InitPlayerTextures();
	loading.setSize(Vector2f(300, 20));
	window->clear();
	window->draw(background);
	window->draw(loadingback);
	window->draw(loading);
	window->display();

	Resources::InitTextures();
	loading.setSize(Vector2f(400, 20));
	window->clear();
	window->draw(background);
	window->draw(loadingback);
	window->draw(loading);
	window->display();

	
	loading.setSize(Vector2f(500, 20));
	window->clear();
	window->draw(background);
	window->draw(loadingback);
	window->draw(loading);
	window->display();

}

///////////////////////////////////////////////
MainMenu::MainMenu(RenderWindow *window, inst::GameStages * currentStage)
{
	this->window = window;
	this->cursor = new Cursor(1);
	this->currentStage = currentStage;
	this->stageName = inst::mainmenu;

	backTexture.loadFromFile("Textures/Background/back_00.jpg");
	buttonTexture.loadFromFile("Textures/Background/back_01.png");//
	background.setSize((Vector2f)window->getSize());
	background.setTexture(&backTexture);

	Resources::InitImages();//temp
	Resources::InitTextures();//temp

	Vector2f middle;
	middle.x = (window->getSize().x - 250) / 2;

	button.push_back(new Button(Resources::strings[str_NewGame], Color::Cyan, Vector2f(250, 50), Vector2f(middle.x, 300), this->buttonTexture, 24, 0));
	button.push_back(new Button(Resources::strings[str_Options], Color::Cyan, Vector2f(250, 50), Vector2f(middle.x, 355), this->buttonTexture, 24, 1));
	button.push_back(new Button(Resources::strings[str_Leaders], Color::Cyan, Vector2f(250, 50), Vector2f(middle.x, 410), this->buttonTexture, 24, 2));
	button.push_back(new Button(Resources::strings[str_Exit], Color::Cyan, Vector2f(250, 50), Vector2f(middle.x, 465), this->buttonTexture, 24, 3));

	
}
MainMenu::~MainMenu()
{
	for (size_t i = 0; i < button.size(); i++)
	{
		delete button[i];
	}
}
void MainMenu::Update(const float & time)
{
	this->cursor->Update(Mouse::getPosition(*window));
	for (size_t i = 0; i < button.size(); i++)
	{
		button[i]->Update(Mouse::getPosition(*window), time);
	}
	CheckInstances();
	
}
void MainMenu::Draw()
{
	this->window->clear();

	//backgroud
	this->window->draw(background);
	//buttons
	for (size_t i = 0; i < this->button.size(); i++)
	{
		this->button[i]->Draw(*window);
	}
	//Layers
	
	this->cursor->Draw(*window);
	this->window->display();
}
void MainMenu::Controls(Event &event)
{
	
}
void MainMenu::CheckInstances()
{
	for (size_t i = 0; i < button.size(); i++)
	{
		switch (button[i]->GetButtonInstance())
		{
		case elem::idle:
			button[i]->TextSetColor(Color::Cyan);
			if(this->button[i]->ToolTipExist())
			this->button[i]->ShowToolTip(false);
			break;
		case elem::hover:
			button[i]->TextSetColor(Color::White);
			if (this->button[i]->ToolTipExist())
			button[i]->ShowToolTip(true);
			break;
		case elem::onclick:
			switch (button[i]->GetButtonId())
			{
			case 0:
				this->SwitchStage(inst::gameloop);
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				this->window->close();
				break;
			default:
				//throw("Out of range");
				break;
			}
			break;
		default:
			break;
		}
	}
}

Stage::~Stage()
{
	delete cursor;
}
