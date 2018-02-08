#include "Bonuses.h"
//Static
vector<Bonuses*>Bonuses::bonuses;

//Bonuses base class
Bonuses::Bonuses()
{
	this->rotationSpeed = 60;
}
void Bonuses::Update(const float &time)
{
	if (lifetime < lifetimeMax)
		this->lifetime += time;

	sprite.rotate(rotationSpeed * time);
}
void Bonuses::Draw(RenderTarget &target)
{
	target.draw(this->sprite);
}
Bonuses::~Bonuses()
{
}

//////
//Med Pack

MedPack::MedPack()
{
	this->sprite.setSize(Vector2f(20, 20));
	this->sprite.setFillColor(Color::Blue);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setPosition(rand() % 1380, rand() % 780);

	this->type = bonus::health_pack;
	this->life = true;
	this->lifetimeMax = this->lifetime = 0;
}
void MedPack::PickUp()
{
	DynamicText::dynamictext.push_back(new DynamicText(Resources::strings[str_HealthPack],
		GetPosition(),
		Vector2f(0, -1),
		Color::Cyan,
		18,
		250.f,
		300.f,
		2.f,
		1.f));

	this->life = false;
}

//////
//Ammo Pack
AmmoPack::AmmoPack()
{
	this->sprite.setSize(Vector2f(20, 20));
	this->sprite.setFillColor(Color::Yellow);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setPosition(rand() % 1380, rand() % 780);

	this->type = bonus::ammo_pack;
	this->life = true;
	this->lifetimeMax = this->lifetime = 0;
}
void AmmoPack::PickUp()
{
	/*if (player.ammo[player.inhand->ammoType] + player.inhand->magazine.maximum > 999)
		player.ammo[player.inhand->ammoType] = 999;
	else
		player.ammo[player.inhand->ammoType] += player.inhand->magazine.maximum;
*/
	DynamicText::dynamictext.push_back(new DynamicText(Resources::strings[str_AmmoPack],
		GetPosition(),
		Vector2f(0, -1),
		Color::Cyan,
		18,
		250.f,
		300.f,
		2.f,
		1.f));

	life = false;
}

//////
//Recharger
Recharger::Recharger()
{
	this->sprite.setSize(Vector2f(20, 20));
	this->sprite.setFillColor(Color::Green);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setPosition(rand() % 1380, rand() % 780);

	this->type = bonus::recharger;
	this->life = true;
	this->lifetimeMax = this->lifetime = 0;
}
void Recharger::PickUp()
{
	/*for (size_t i = 0; i < spellbook.size(); i++)
	{
		spellbook[i]->currenttime = spellbook[i]->reloadtime;
	}*/

	DynamicText::dynamictext.push_back(new DynamicText("Spell Recharge",
		GetPosition(),
		Vector2f(0, -1),
		Color::Cyan,
		18,
		250.f,
		300.f,
		2.f,
		1.f));

	life = false;
}

//////
//Global bonuses base class

CuttingBullets::CuttingBullets()
{
	this->sprite.setSize(Vector2f(20, 20));
	this->sprite.setFillColor(Color::White);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setPosition(rand() % 1380, rand() % 780);

	this->type = bonus::cuttingBullets;
	this->lifetimeMax = 10;
	this->lifetime = 0;
	this->life = true;
}
void CuttingBullets::PickUp()
{
		DynamicText::dynamictext.push_back(new DynamicText(Resources::strings[str_CuttingBullets],
			GetPosition(),
			Vector2f(0, -1),
			Color::Cyan,
			18,
			250.f,
			300.f,
			2.f,
			1.f));

		this->life = false;
		this->lifetime = 0;
}

SpeedBooster::SpeedBooster()
{
	this->sprite.setSize(Vector2f(20, 20));
	this->sprite.setFillColor(Color::Black);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setPosition(rand() % 1380, rand() % 780);

	this->type = bonus::speedBooster;
	this->lifetimeMax = 20;
	this->lifetime = 0;
	this->life = true;
}
void SpeedBooster::PickUp()
{
	DynamicText::dynamictext.push_back(new DynamicText(Resources::strings[str_SpeedBooster],
		GetPosition(),
		Vector2f(0, -1),
		Color::Cyan,
		18,
		250.f,
		300.f,
		2.f,
		1.f));

	this->life = false;
	this->lifetime = 0;
}

DronSpawner::DronSpawner()
{
	this->sprite.setSize(Vector2f(20, 20));
	this->sprite.setFillColor(Color::Cyan);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setPosition(rand() % 1380, rand() % 780);

	this->type = bonus::dronSpawner;
	this->lifetimeMax = 20;
	this->lifetime = 0;
	this->life = true;
}

void DronSpawner::PickUp()
{
	DynamicText::dynamictext.push_back(new DynamicText(Resources::strings[str_dronSpawner],
		GetPosition(),
		Vector2f(0, -1),
		Color::Cyan,
		18,
		250.f,
		300.f,
		2.f,
		1.f));

	this->life = false;
	this->lifetime = 0;
}
