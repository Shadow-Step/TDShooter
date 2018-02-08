#include "Objects.h"

vector<Building*>Building::building;
vector<Unit*>Unit::unit;
Texture Mine::mineTexture;

//STATIC SHELL
int Shell::resources[4] = {100,100,100,100};
int Shell::ID = 0;
Vector2f Shell::portPos = Vector2f(204, 768 - 162);
Vector2f Shell::buttPos = Vector2f(689, 768 - 160);
Vector2f Shell::iconPos = Vector2f(366, 768 - 108);
bool Shell::blockselector = false;
bool Shell::commandReady = false;
obj::Type Shell::type = obj::EMPTY;
sel::commands Shell::command = sel::EMPTY;
//Functions
void Shell::SwitchCommand(obj::Type type)
{
	Shell::type = type;
	Shell::command = sel::EMPTY;
	Shell::commandReady = true;
}
void Shell::SwitchCommand(sel::commands command)
{
	Shell::type = obj::EMPTY;
	Shell::command = command;
	Shell::commandReady = true;
}
//END STATIC SHELL

Selector::Selector()
{
	this->capacity = 12;
	this->selector.resize(capacity);
	this->empty = true;

	this->dragbox.setFillColor(Color::Transparent);
	this->dragbox.setOutlineThickness(1);
	this->dragbox.setOutlineColor(Color::Green);
}
void Selector::Update(Vector2f mouse,const float &time)
{
	//Запуск Dragmode
	if (!dragOn)
	{
		dragmode = false;
	}
	if (dragOn && !dragmode)
	{
		if (CountDistance(mouse, clickposition) > 5)
		{
			dragmode = true;
			dragbox.setPosition(clickposition);
		}
	}
	if (dragmode && dragOn)
	{
		dragbox.setSize(Vector2f(mouse.x - clickposition.x, mouse.y - clickposition.y));
		for (size_t i = 0; i < Unit::unit.size(); i++)
		{
			if (dragbox.getGlobalBounds().intersects(Unit::unit[i]->GetBounds()))
				Add(Unit::unit[i]);
		}
	}
	
	//Проверка очереди комманд
	if (Shell::commandReady)
	{
		if (Shell::command != sel::EMPTY)
			SwitchCommand(Shell::command);
		else
			SwitchCommand(Shell::type);
		Shell::commandReady = false;
	}

	//Обновление состояния строительста
	if (command == sel::Build)
	{
		buildSprite.setPosition(mouse);
		for (size_t i = 0; i < Building::building.size(); i++)
		{
			if (buildSprite.getGlobalBounds().intersects(Building::building[i]->GetBounds()))
			{
				buildSprite.setFillColor(Color::Red);
				blocked = true;
				break;//Break!!!
			}
			else
			{
				buildSprite.setFillColor(Color::Green);
				blocked = false;
			}
		}
	}

	//Обновление если в селекторе есть объект
	if (!empty)
	{
		for (size_t i = 0; i < selector.size(); i++)
		{
			if(selector[i]!=0)
			selector[i]->SetIconPosition(math::Buttpos(Shell::iconPos,i,6));
		}
	}
}
void Selector::Draw(RenderTarget &target)
{
	//Прорисовка спрайта во время строительства
	if (command == sel::Build)
		target.draw(buildSprite);

	//Прорисовка DragBox'a
	if (dragmode)
		target.draw(dragbox);

	//Прорисовка содержимого selector
	if (!empty)
	{
		for (size_t i = 0; i < selector.size(); i++)
		{
			if(selector[i]!=0)
			selector[i]->DrawIcon(target);
		}
		if (selector[0] != 0)
		{
			selector[0]->DrawPortret(target);
			selector[0]->DrawButtons(target);
		}
	}

}
void Selector::LeftAction(Vector2f mouse)
{

	if(!Shell::blockselector)
	switch (command)
	{
	case sel::Build:
		if(!blocked)
		Build(mouse);
		break;
	case sel::None:
		Clear();
		Select(mouse);
		break;
	case sel::Move:
		Clear();
		Select(mouse);
		break;
	}
}
void Selector::RightAction(Vector2f mouse)
{
	if(!Shell::blockselector)
	switch (command)
	{
	case sel::None:
		Clear();
		break;
	case sel::Build:
		SwitchCommand(sel::None);
		break;
	case sel::Move:
		for (size_t i = 0; i < selector.size(); i++)
		{
			if(selector[i]!=0)
			selector[i]->Command(mouse,i);
		}
		break;
	case sel::Repair:
		break;
	}
}
void Selector::SwitchCommand(obj::Type buildingtype)
{
	this->command = sel::Build; 
	this->buildingtype = buildingtype;

	switch (buildingtype)
	{
	case obj::Mine_Iron:
		this->buildSprite.setSize(Vector2f(74, 66));
		this->buildSprite.setOrigin(37, 33);
		this->buildSprite.setTexture(&Mine::mineTexture);
		this->buildSprite.setTextureRect(IntRect(496, 43, 220, 200));

		break;
	case obj::Mine_Stone:
		this->buildSprite.setSize(Vector2f(74, 66));
		this->buildSprite.setOrigin(37, 33);
		this->buildSprite.setTexture(&Mine::mineTexture);
		this->buildSprite.setTextureRect(IntRect(261, 43, 220, 200));

		break;
	case obj::Mine_Wood:
		this->buildSprite.setSize(Vector2f(74, 66));
		this->buildSprite.setOrigin(37, 33);
		this->buildSprite.setTexture(&Mine::mineTexture);
		this->buildSprite.setTextureRect(IntRect(29, 43, 220, 200));

		break;
	case obj::Mine_Gold:
		this->buildSprite.setSize(Vector2f(74, 66));
		this->buildSprite.setOrigin(37, 33);
		this->buildSprite.setTexture(&Mine::mineTexture);
		this->buildSprite.setTextureRect(IntRect(120, 262, 220, 200));

		break;
	case obj::Barrack:
		this->buildSprite.setTexture(NULL);
		this->buildSprite.setSize(Vector2f(140, 70));
		this->buildSprite.setOrigin(70, 35);
		break;
	}
}
void Selector::Add(Objects * target)
{
	bool check = false;
	if(!empty)
	for (size_t i = 0; i < selector.size(); i++)
	{
		if (selector[i]!= 0 && selector[i]->GetId() == target->GetId())
		check = true;
	}

	if (check == false)
	{
		for (size_t i = 0; i < selector.size(); i++)
		{
			if (selector[i] == 0)
			{
				selector[i] = target;
				selector[i]->Select(true);
				SwitchCommand(sel::Move);
				break;
			}
		}
		empty = false;
	}
}

void Selector::Clear()
{
	if(!empty)
	for (size_t i = 0; i < selector.size(); i++)
	{
		if (selector[i] != 0)
		{
			selector[i]->Select(false);
			selector[i] = 0;
		}
	}
	empty = true;
}
void Selector::Clear(int id)
{
	if(!empty)
		for (size_t i = 0; i < selector.size(); i++)
		{
			if (selector[i] !=0 && selector[i]->GetId() == id)
			{
				selector[i]->Select(false);
				selector[i] = 0;
			}
		}
}
////
void Selector::Build(Vector2f mouse)
{
	switch (buildingtype)
	{
	case obj::Mine_Iron:
		Building::building.push_back(new Mine(mouse, buildingtype));
			break;
	case obj::Mine_Stone:
		Building::building.push_back(new Mine(mouse, buildingtype));
		break;
	case obj::Mine_Wood:
		Building::building.push_back(new Mine(mouse, buildingtype));
		break;
	case obj::Mine_Gold:
		Building::building.push_back(new Mine(mouse, buildingtype));
		break;
	case obj::Barrack:
		Building::building.push_back(new Barrack(mouse, buildingtype));
		break;
	}
	SwitchCommand(sel::None);
}
void Selector::Select(Vector2f mouse)
{
	for (size_t i = 0; i < Unit::unit.size(); i++)
	{
		if (Unit::unit[i]->Contains(mouse))
		{
			Add(Unit::unit[i]);
			break;
		}
	}
	for (size_t i = 0; i < Building::building.size(); i++)
	{
		if (Building::building[i]->Contains(mouse))
		{
			Add(Building::building[i]);
			break;
		}
	}
	
}
////

Objects::Objects()
{
	Shell::ID++;
	this->id = Shell::ID;
	this->button.resize(12);
}
Objects::~Objects()
{
	for (size_t i = 0; i < button.size(); i++)
	{
		delete button[i];
	}
	button.resize(0);
}
void Objects::Select(bool select)
{
	this->selected = select;
	if (selected)
	{
		sprite.setOutlineThickness(1);
		sprite.setOutlineColor(Color(0,255,0,100));
	}
	else
	{
		sprite.setOutlineThickness(0);
	}
}
void Objects::InitTextures()
{
	Image image;
	image.loadFromFile("Textures/Buildings/mines.png");
	image.createMaskFromColor(Color::White);
	Mine::mineTexture.loadFromImage(image);
}
void Objects::DrawButtons(RenderTarget &target)
{
	if (selected)
	{
		for (size_t i = 0; i < button.size(); i++)
		{
			if(button[i]!=0)
			button[i]->Draw(target);
		}
	}
}
obj::ButtonsId Objects::UpdateButtons(Vector2f mouse, const float &time)
{
	int hovered = 0;
	for (size_t i = 0; i < button.size(); i++)
	{
		if (button[i]!= 0)
		{
			button[i]->Update((Vector2i)mouse, time);
			switch (button[i]->GetButtonInstance())
			{
			case elem::idle:
				button[i]->ButtonSetColor(Color::White);
				break;
			case elem::hover:
				hovered++;
				button[i]->ButtonSetColor(Color::Green);
				break;
			case elem::onclick:
				switch (button[i]->GetButtonId())
				{
				case obj::ButtonsId::b_Mine_Iron:
					Shell::SwitchCommand(obj::Type::Mine_Iron);
					break;
				case obj::ButtonsId::b_Mine_Stone:
					Shell::SwitchCommand(obj::Type::Mine_Stone);
					break;
				case obj::ButtonsId::b_Mine_Wood:
					Shell::SwitchCommand(obj::Type::Mine_Wood);
					break;
				case obj::ButtonsId::b_Mine_Gold:
					Shell::SwitchCommand(obj::Type::Mine_Gold);
					break;
				case obj::ButtonsId::b_Barrack:
					Shell::SwitchCommand(obj::Type::Barrack);
					break;
				case obj::ButtonsId::b_Delete:
					this->life = false;
					break;
				case obj::ButtonsId::b_Create_Peasant:
					Unit::unit.push_back(new Peasant(sprite.getPosition()));
					break;
				case obj::ButtonsId::b_Create_Marine:
					//Unit::unit.push_back(new Marine(sprite.getPosition()));
					return obj::ButtonsId::b_Create_Marine;//
					break;
				}
				button[i]->ButtonSetInstance(elem::ElemInstance::hover);
				break;
			}
		}
	}
	if (hovered > 0)
		Shell::blockselector = true;
	else
		Shell::blockselector = false;
}

void Building::Command(Vector2f position,int index)
{
	this->spawnsprite.setSize(Vector2f(8, 8));
	this->spawnsprite.setFillColor(Color::Red);
	this->spawnsprite.setPosition(position);
	this->spawnpoint = true;
}
void Building::UpdateIcon(Vector2f mouse, const float & time)
{
	if (!icon.getGlobalBounds().contains(mouse))
	{
		this->instance = elem::idle;
	}
	else if (icon.getGlobalBounds().contains(mouse))
	{
		if (Mouse::isButtonPressed(Mouse::Left))
			this->instance = elem::onclick;
		else
			this->instance = elem::hover;
	}
}
const bool Building::CanBePlaced() const
{
	for (size_t i = 0; i < 4; i++)
	{
		if (Shell::resources[i] < this->price[i])
			return false;
	}
	return true;
}

Mine::Mine()
{
	this->sprite.setSize(Vector2f(64, 64));
	this->sprite.setTexture(&mineTexture);
	this->sprite.setTextureRect(IntRect(29,43,220,200));
	this->sprite.setOrigin(32, 32);
	this->sprite.setPosition(300, 300);

	this->productTimeMax = 5;
	this->productTime = 0;
	this->resource = obj::Iron;
	this->productivity = 10;

	this->buildTime = 30;
	this->constructed = false;

	this->sprite.setFillColor(Color::Green);
	this->blocked = false;

	this->price[obj::Iron] = 0;
	this->price[obj::Stone] = 0;
	this->price[obj::Wood] = 100;
	this->price[obj::Gold] = 50;
	
}
Mine::Mine(Vector2f position,obj::Type type)
{
	this->sprite.setSize(Vector2f(74, 66));//64x64
	this->sprite.setOrigin(37, 33);
	this->sprite.setPosition(position);
	this->sprite.setFillColor(Color(100, 100, 100, 230));

	this->portret.setSize(Vector2f(160, 160));
	this->portret.setPosition(Shell::portPos);

	this->icon.setSize(Vector2f(50, 50));
	this->icon.setPosition(position.x+32,position.y);
	this->icon.setOutlineThickness(2);
	this->icon.setFillColor(Color::Green);

	switch (type)
	{
	case obj::Type::Mine_Iron:

		this->type = obj::Mine_Iron;
		this->sprite.setTexture(&mineTexture);
		this->sprite.setTextureRect(IntRect(496, 43, 220, 200));

		this->portret.setTexture(&mineTexture);
		this->portret.setTextureRect(IntRect(496, 43, 220, 200));
		

		this->icon.setTexture(&mineTexture);
		this->icon.setTextureRect(IntRect(496, 43, 220, 200));

		this->resource = obj::Iron;

		this->price[obj::Iron] = 0;
		this->price[obj::Stone] = 50;
		this->price[obj::Wood] = 50;
		this->price[obj::Gold] = 0;
		break;
	case obj::Type::Mine_Stone:
		this->type = obj::Mine_Stone;

		this->sprite.setTexture(&mineTexture);
		this->sprite.setTextureRect(IntRect(261, 43, 220, 200));

		this->portret.setTexture(&mineTexture);
		this->portret.setTextureRect(IntRect(261, 43, 220, 200));


		this->icon.setTexture(&mineTexture);
		this->icon.setTextureRect(IntRect(261, 43, 220, 200));

		this->resource = obj::Stone;

		this->price[obj::Iron] = 0;
		this->price[obj::Stone] = 0;
		this->price[obj::Wood] = 50;
		this->price[obj::Gold] = 0;
		break;
	case obj::Type::Mine_Wood:
		this->type = obj::Mine_Wood;
		this->sprite.setTexture(&mineTexture);
		this->sprite.setTextureRect(IntRect(29, 43, 220, 200));

		this->portret.setTexture(&mineTexture);
		this->portret.setTextureRect(IntRect(29, 43, 220, 200));


		this->icon.setTexture(&mineTexture);
		this->icon.setTextureRect(IntRect(29, 43, 220, 200));

		this->resource = obj::Wood;

		this->price[obj::Iron] = 0;
		this->price[obj::Stone] = 0;
		this->price[obj::Wood] = 0;
		this->price[obj::Gold] = 50;
		break;
	case obj::Type::Mine_Gold:
		this->type = obj::Mine_Gold;
		this->sprite.setTexture(&mineTexture);
		this->sprite.setTextureRect(IntRect(120, 262, 220, 200));

		this->portret.setTexture(&mineTexture);
		this->portret.setTextureRect(IntRect(120, 262, 220, 200));

		this->icon.setTexture(&mineTexture);
		this->icon.setTextureRect(IntRect(120, 262, 220, 200));

		this->resource = obj::Gold;

		this->price[obj::Iron] = 110;
		this->price[obj::Stone] = 110;
		this->price[obj::Wood] = 110;
		this->price[obj::Gold] = 0;
		break;
	}

	this->productTimeMax = 5;
	this->productTime = 0;
	this->productivity = 10;

	this->buildTimeMax = 30;
	this->buildTime = 0;
	this->constructed = false;

	this->buildbaridle.setSize(Vector2f(74, 5));
	this->buildbaridle.setFillColor(Color::Black);
	this->buildbaridle.setPosition(position.x-37, position.y + 33);
	this->buildbar.setFillColor(Color::Yellow);
	this->buildbar.setPosition(position.x-37, position.y + 33);


	//970 + (54*x), 302 + (54*y)
	button[0] = (new Button(Vector2f(50, 50), math::Buttpos(Shell::buttPos, 0, 3), Mine::mineTexture, IntRect(29, 43, 220, 200), obj::ButtonsId::b_Barrack));
	button[1] = (new Button(Vector2f(50, 50), math::Buttpos(Shell::buttPos, 1, 3), Mine::mineTexture, IntRect(29, 43, 220, 200), obj::ButtonsId::b_Mine_Wood));
	button[2] = (new Button(Vector2f(50, 50), math::Buttpos(Shell::buttPos, 2, 3), Mine::mineTexture, IntRect(29, 43, 220, 200), obj::ButtonsId::b_Mine_Stone));
	button[3] = (new Button(Vector2f(50, 50), math::Buttpos(Shell::buttPos, 3, 3), Mine::mineTexture, IntRect(29, 43, 220, 200), obj::ButtonsId::b_Mine_Gold));
	button[8] = (new Button(Vector2f(50, 50), math::Buttpos(Shell::buttPos, 8, 3), Mine::mineTexture, IntRect(29, 43, 220, 200), obj::ButtonsId::b_Delete));
}
void Mine::Update(Vector2f mouse, const float & time)
{
	if (selected)
		UpdateButtons(mouse,time );

	if (!constructed)
	{
		sprite.setFillColor(Color(100, 100, 100, 230));
		buildTime += time;
		buildbar.setSize(Vector2f(74*(buildTime/buildTimeMax),5));
		if (buildTime >= buildTimeMax)
		{
			constructed = true;
			sprite.setFillColor(Color::White);
		}
	}
	else
	{
		productTime += time;
		if (productTime >= productTimeMax)
		{
			productTime = 0;
			Shell::resources[resource] += productivity;

			DynamicText::dynamictext.push_back(new DynamicText(to_string(productivity),
				sprite.getPosition(),
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
void Mine::Draw(RenderTarget & target)
{
	target.draw(sprite);
	if (!constructed)
	{
		target.draw(buildbaridle);
		target.draw(buildbar);
	}
	
}

//Units
Peasant::Peasant(Vector2f position)
{
	
}
void Peasant::Update(Vector2f mouse, const float & time)
{
	
}
void Peasant::Draw(RenderTarget & target)
{
	
}

void Unit::Command(Vector2f position,int index)
{
	
	static int contained;
	contained = 0;
	bool pathfinded = false;
	this->ai = unit::AI::Move;
	
	while (!pathfinded)
	{
		for (size_t i = 0; i < Unit::unit.size(); i++)
		{
			if (Unit::unit[i]->Contains(position))
			{
				contained++;
				switch (rand() % 4)
				{
				case 0:
					position.x -= 32;
					break;
				case 1:
					position.x += 32;
					break;
				case 2:
					position.y -= 32;
					break;
				case 3:
					position.y += 32;
					break;
				}
			}
				
		}
		if (contained == 0)
		{
			this->moveposition.x = position.x - (32 * index);
			this->moveposition.y = position.y;
			this->movemarker.setPosition(moveposition);
			pathfinded = true;
			break;//Break!!!
		}
		contained = 0;
	}
}
void Unit::Move(Vector2f position,const float &time)
{
	if ((int)CountDistance(position, sprite.getPosition()) != 0)
	{
		movecount.x = speed * time * (position.x - sprite.getPosition().x) / CountDistance(position, sprite.getPosition());
		movecount.y = speed * time * (position.y - sprite.getPosition().y) / CountDistance(position, sprite.getPosition());
		sprite.move(movecount);
		sprite.setRotation(-CountAngle(position, sprite.getPosition()) + rotAngle);
	}
	else if((int)CountDistance(position, sprite.getPosition()) == 0)
	{
		ai = unit::AI::Idle;
	}
}
void Unit::Shoot()
{
	sprite.setRotation(-CountAngle(target->GetPosition(), sprite.getPosition()) + rotAngle);
	if (hitrate > hitrateMax)
	{
		weapon->Shoot(target->GetPosition(), sprite.getPosition());
		hitrate = 0;
	}
}
void Unit::SelectTarget()
{
	int globaldist = 0;
	for (size_t i = 0; i < Enemy::enemy.size(); i++)
	{
		int posX = Enemy::enemy[i]->GetPosition().x - sprite.getPosition().x;
		int posY = Enemy::enemy[i]->GetPosition().y - sprite.getPosition().y;
		int distance = sqrt(pow(posX, 2) + pow(posY, 2));
		if (distance <= this->hitrange)
		{
			if (globaldist == 0)
			{
				globaldist = distance;
				target = Enemy::enemy[i];
			}
			if (distance < globaldist)
			{
				globaldist = distance;
				target = Enemy::enemy[i];
			}
		}
	}
}

Marine::Marine(Vector2f position)
{
	this->sprite.setSize(Vector2f(32, 32));
	this->sprite.setOrigin(16, 16);
	this->sprite.setTexture(&Resources::playerTTex[0][0]);
	this->sprite.setPosition(position.x - 50, position.y);
	this->rotAngle = -90;

	this->icon.setSize(Vector2f(50, 50));
	this->icon.setTexture(&Resources::playerTTex[0][0]);
	this->icon.setOutlineThickness(2);
	this->icon.setFillColor(Color::Green);//

	this->portret.setSize(Vector2f(160, 160));
	this->portret.setPosition(Shell::portPos);
	this->portret.setTexture(&Resources::playerTTex[0][0]);

	this->movemarker.setSize(Vector2f(8, 8));
	this->movemarker.setFillColor(Color::Green);

	this->speed = 100;
	this->hitrateMax = 2;
	this->hitrate = 0;
	this->hitrange = 300;

	this->healthMax = 100;
	this->health = 100;

	this->weapon = new Pistol(Vector2f(0, 0), weap::pistols::p_Beretta);

	this->healthbarMax.setSize(Vector2f(24, 5));
	this->healthbarMax.setFillColor(Color::Black);
	this->healthbar.setFillColor(Color::Green);
}
void Marine::Update(Vector2f mouse, const float & time)
{
	//
	healthbarMax.setPosition(sprite.getPosition().x-12, sprite.getPosition().y + 18);
	healthbar.setSize(Vector2f(24 * (health / healthMax),5));
	healthbar.setPosition(sprite.getPosition().x-12, sprite.getPosition().y + 18);
	//
	weapon->firerate.current += time;
	this->hitrate += time;

	if (selected)
		UpdateButtons(mouse, time);
	if (ai == unit::AI::Move)
		Move(moveposition, time);
	if (ai == unit::AI::Idle && target == 0)
	{
		SelectTarget();
	}
	if (ai == unit::AI::Idle && target != 0)
	{
		if (CountDistance(target->GetPosition(), sprite.getPosition()) > hitrange)
			target = 0;
		else
			Shoot();
	}

}
void Marine::Draw(RenderTarget & target)
{
	target.draw(sprite);
	if (ai == unit::AI::Move && selected)
		target.draw(movemarker);
	if (selected)
	{
		target.draw(healthbarMax);
		target.draw(healthbar);
	}
}

Barrack::Barrack(Vector2f position, obj::Type type)
{
	this->sprite.setSize(Vector2f(140, 70));//64x64
	this->sprite.setOrigin(70, 35);
	this->sprite.setPosition(position);
	this->sprite.setFillColor(Color(100, 100, 100, 230));

	this->portret.setSize(Vector2f(160, 160));
	this->portret.setPosition(Shell::portPos);

	this->icon.setSize(Vector2f(50, 50));
	this->icon.setPosition(position.x + 32, position.y);
	this->icon.setOutlineThickness(2);
	this->icon.setFillColor(Color::Green);

	//Stats
	this->productTimeMax = 3;
	this->productTime = 0;

	this->buildTimeMax = 10;
	this->buildTime = 0;
	this->constructed = false;
	//End stats
	this->buildbaridle.setSize(Vector2f(140, 5));
	this->buildbaridle.setFillColor(Color::Black);
	this->buildbaridle.setPosition(position.x - 70, position.y + 37);
	this->buildbar.setFillColor(Color::Yellow);
	this->buildbar.setPosition(position.x - 70, position.y + 37);

	button[0] = (new Button(Vector2f(50, 50), math::Buttpos(Shell::buttPos, 0, 3), Resources::playerTTex[0][0], IntRect(0, 0, 258, 220), obj::ButtonsId::b_Create_Marine));
}
void Barrack::Update(Vector2f mouse, const float & time)
{
	if (selected)
	{
		obj::ButtonsId temp = UpdateButtons(mouse, time);
		if (temp == obj::ButtonsId::b_Create_Marine)
		{
			action.push_back(obj::b_Create_Marine);
		}
	}
	if (!constructed)
	{
		sprite.setFillColor(Color(100, 100, 100, 230));
		buildTime += time;
		buildbar.setSize(Vector2f(140 * (buildTime / buildTimeMax), 5));
		if (buildTime >= buildTimeMax)
		{
			constructed = true;
			sprite.setFillColor(Color::White);
		}
	}
	if (action.size() > 0)
	{
		productTime += time;
		buildbar.setSize(Vector2f(140 * (productTime / productTimeMax), 5));
		if (productTime > productTimeMax)
		{
			switch (action[0])
			{
			case obj::b_Create_Marine:
				Unit::unit.push_back(new Marine(Vector2f(sprite.getPosition().x - 100,sprite.getPosition().y)));
				if (spawnpoint)
					Unit::unit[Unit::unit.size() - 1]->Command(spawnsprite.getPosition(), 0);
				break;
			}
			action.erase(action.begin());
			productTime = 0;
		}
	}
}
void Barrack::Draw(RenderTarget & target)
{
	target.draw(sprite);
	if (!constructed || productTime > 0)
	{
		target.draw(buildbaridle);
		target.draw(buildbar);
	}
	if (spawnpoint && selected)
		target.draw(spawnsprite);
}
