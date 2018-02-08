#include "Weapons.h"
//Static
vector<Weapons*>Weapons::weapons;

Weapons::Weapons()
{
	sprite.setTexture(Resources::weaponsTextures[0]);
	icon.setTexture(Resources::weaponsTextures[0]);
	this->lifeTimeMax = 30;
	this->lifeTime = 0;
}
void Weapons::Update(const float & time)
{
	if (this->lifeTime < this->lifeTimeMax)
		this->lifeTime += time;

	this->icon.rotate(150 * time);
}

Pistol::Pistol(Vector2f position,int model)
{
	this->ammoType = weap::ammo_pistol;
	switch (model)
	{
	case weap::p_Beretta:
		//Textures
		this->sprite.setTextureRect(IntRect(69, 1, 55, 37)); 
		this->icon.setTextureRect(IntRect(69, 1, 55, 37));
		this->icon.setPosition(position);
		this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
		this->icon.setScale(0.7, 0.7);

		//Stats
		this->damage = 12;
		this->firerate.Set(0.2);
		this->magazine.Set(15);
		this->reload.Set(2);
		this->bulletspeed = 1000;
		this->accuracy = 2;

	break;

	case weap::p_Glock17:
		//Textures
		this->sprite.setTextureRect(IntRect(135, 0, 61, 34));
		this->icon.setTextureRect(IntRect(135, 0, 61, 34));
		this->icon.setPosition(position);
		this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
		this->icon.setScale(0.7, 0.7);

		//Stats
		this->damage = 9;
		this->firerate.Set(0.08);
		this->magazine.Set(15);
		this->reload.Set(2);
		this->bulletspeed = 800;
		this->accuracy = 6;
		break;

	case weap::p_Makarov:
		//Textures
		this->sprite.setTextureRect(IntRect(269, 2, 51, 32));
		this->icon.setTextureRect(IntRect(269, 2, 51, 32));
		this->icon.setPosition(position);
		this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
		this->icon.setScale(0.7, 0.7);

		//Stats
		this->damage = 18;
		this->firerate.Set(0.12);
		this->magazine.Set(12);
		this->reload.Set(2);
		this->bulletspeed = 1200;
		this->accuracy = 6;
		break;
	case weap::p_DesertEagle:
		//Textures
		this->sprite.setTextureRect(IntRect(203, 69, 51, 34));
		this->icon.setTextureRect(IntRect(203, 69, 51, 34));
		this->icon.setPosition(position);
		this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
		this->icon.setScale(0.7, 0.7);

		//Stats
		this->damage = 37;
		this->firerate.Set(0.3);
		this->magazine.Set(7);
		this->reload.Set(2);
		this->bulletspeed = 1400;
		this->accuracy = 12;
		break;
	case weap::p_AK47:
		//Textures
		this->sprite.setTextureRect(IntRect(1, 75, 59, 25));
		this->icon.setTextureRect(IntRect(1, 75, 59, 25));
		this->icon.setPosition(position);
		this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
		this->icon.setScale(0.7, 0.7);

		//Stats
		this->damage = 25;
		this->firerate.Set(0.09);
		this->magazine.Set(30);
		this->reload.Set(1.5);
		this->bulletspeed = 1200;
		this->accuracy = 6;
		this->ammoType = weap::ammo_auto;
		break;
	case weap::p_M240:
		//Textures
		this->sprite.setTextureRect(IntRect(266, 43, 62, 24));
		this->icon.setTextureRect(IntRect(266, 43, 62, 24));
		this->icon.setPosition(position);
		this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
		this->icon.setScale(0.7, 0.7);

		//Stats
		this->damage = 23;
		this->firerate.Set(0.03);
		this->magazine.Set(200);
		this->reload.Set(4);
		this->bulletspeed = 1400;
		this->accuracy = 12;
		this->ammoType = weap::ammo_auto;
		break;
	default:
		cout << model << endl;
		throw("OUT OF WEAPONS RANGE");
		break;
	}
}//Îøèáêà Out of weapon range
void Pistol::Shoot(Vector2f target, Vector2f shooter)
{
	Vector2f movecount;
	float distance = sqrt(pow((target.x - shooter.x), 2) + pow((target.y - shooter.y), 2));
	float angle = (atan2f(target.x - shooter.x, target.y - shooter.y) * 180 / 3.14) + rand() % accuracy - (accuracy / 2);
	movecount.x = (distance * sin(angle*3.14 / 180)) / (distance / bulletspeed);
	movecount.y = (distance * cos(angle*3.14 / 180)) / (distance / bulletspeed);
	
	DynamicObjects::dynamic.push_back(new Bullet(damage, movecount, shooter, angle,bulletspeed));
	magazine.current -= 1;
}

ShotGun::ShotGun(Vector2f position,int model)
{
	this->ammoType = weap::ammo_shotgun;
	switch (model)
	{
	case weap::s_Striker:
		//Textures Striker
		this->sprite.setTextureRect(IntRect(264, 78, 58, 18));
		this->icon.setTextureRect(IntRect(264, 78, 58, 18));
		this->icon.setPosition(position);
		this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
		this->icon.setScale(0.9, 0.9);

		//Stats
		this->damage = 12;
		this->firerate.Set(0.4);
		this->magazine.Set(7);
		this->reload.Set(3);
		this->bulletspeed = 1000;
		this->accuracy = 20;
		this->charges = 12;
		break;
	case weap::s_Shotgun:
		//Textures Shotgun
		this->sprite.setTextureRect(IntRect(0, 46, 66, 17));
		this->icon.setTextureRect(IntRect(0, 46, 66, 17));
		this->icon.setPosition(position);
		this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
		this->icon.setScale(0.8, 0.8);

		//Stats
		this->damage = 15;
		this->firerate.Set(0.2);
		this->magazine.Set(2);
		this->reload.Set(3);
		this->bulletspeed = 1200;
		this->accuracy = 30;
		this->charges = 20;
		break;
	default:
		cout << model << endl;
		throw("OUT OF WEAPONS RANGE");
		break;
	}
	
}
void ShotGun::Shoot(Vector2f target, Vector2f shooter)
{
	for (size_t i = 0; i < charges; i++)
	{
		Vector2f movecount;
		float distance = sqrt(pow((target.x - shooter.x), 2) + pow((target.y - shooter.y), 2));
		float angle = (atan2f(target.x - shooter.x, target.y - shooter.y) * 180 / 3.14) + rand() % accuracy - (accuracy / 2);
		movecount.x = (distance * sin(angle*3.14 / 180)) / (distance / bulletspeed);
		movecount.y = (distance * cos(angle*3.14 / 180)) / (distance / bulletspeed);
		DynamicObjects::dynamic.push_back(new Bullet(damage, movecount, shooter, angle, bulletspeed));
	}
	magazine.current -= 1;
}

Bazzoka::Bazzoka(Vector2f position,int model, int damage, float firerate, int magazine)
{
	this->sprite.setTextureRect(IntRect(4, 107, 65, 22));
	this->icon.setTextureRect(IntRect(4, 107, 65, 22));
	this->icon.setPosition(position);
	this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
	this->icon.setScale(0.8, 0.8);

	reload.Set(1);
	ammoType = weap::ammo_rocket;
	this->damage = damage;
	this->firerate.Set(firerate);
	this->magazine.Set(magazine);
	bulletspeed = 300;
	accuracy = 1;
}
void Bazzoka::Shoot(Vector2f target, Vector2f shooter)
{
	Vector2f movecount;
	float distance = sqrt(pow((target.x - shooter.x), 2) + pow((target.y - shooter.y), 2));
	float angle = (atan2f(target.x - shooter.x, target.y - shooter.y) * 180 / 3.14) + rand() % accuracy - (accuracy / 2);
	movecount.x = (distance * sin(angle*3.14 / 180)) / (distance / bulletspeed);
	movecount.y = (distance * cos(angle*3.14 / 180)) / (distance / bulletspeed);
	Rocket::rocket.push_back(new Rocket(movecount, shooter,this->damage,this->bulletspeed,angle));
	magazine.current -= 1;
}

HealGun::HealGun(int damage, float firerate, int bulletspeed)
{
	ammoType = weap::ammo_pistol;

	this->damage = damage;
	this->firerate.Set(firerate);
	this->magazine.Set(999);

	accuracy = 1;
	this->bulletspeed = bulletspeed;
}
void HealGun::Shoot(Vector2f target, Vector2f shooter)
{
	if (firerate.current >= firerate.maximum)
	{
		Vector2f movecount;
		float distance = sqrt(pow((target.x - shooter.x), 2) + pow((target.y - shooter.y), 2));
		float angle = (atan2f(target.x - shooter.x, target.y - shooter.y) * 180 / 3.14) + rand() % accuracy - (accuracy / 2);
		movecount.x = (distance * sin(angle*3.14 / 180)) / (distance / bulletspeed);
		movecount.y = (distance * cos(angle*3.14 / 180)) / (distance / bulletspeed);
		//dynamic.push_back(new HealBall(damage, movecount, shooter));
		firerate.current = 0;
	}
}

TeslaGun::TeslaGun(int damage, float firerate)
{
	this->damage = damage;
	this->firerate.Set(firerate);
	this->magazine.Set(999);
}
void TeslaGun::Shoot(Vector2f target, Vector2f shooter)
{
	if (firerate.current >= firerate.maximum)
	{
		//dynamic.push_back(new ElecticWave(damage, 0.4, shooter));
		firerate.current = 0;
	}
}

AIMachineGun::AIMachineGun(Vector2f position,int model, int damage, float firerate, int magazine)
{
	this->sprite.setTextureRect(IntRect(470, 64, 62, 24));
	this->icon.setTextureRect(IntRect(470, 64, 62, 24));
	this->icon.setPosition(position);
	this->icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
	this->icon.setScale(0.8, 0.8);


	this->damage = damage;
	this->firerate.Set(firerate);
	this->magazine.Set(magazine);
	this->reload.Set(7);
	this->ammoType = weap::ammo_auto;
	this->bulletspeed = 1000;
	this->accuracy = 20;
	
}
void AIMachineGun::Shoot(Vector2f target, Vector2f shooter)
{
	Vector2f movecount;
	float distance = sqrt(pow((target.x - shooter.x), 2) + pow((target.y - shooter.y), 2));
	float angle = (atan2f(target.x - shooter.x, target.y - shooter.y) * 180 / 3.14) + rand() % accuracy - (accuracy / 2);
	movecount.x = (distance * sin(angle*3.14 / 180)) / (distance / bulletspeed);
	movecount.y = (distance * cos(angle*3.14 / 180)) / (distance / bulletspeed);
	AIBullet::aibullet.push_back(new AIBullet(movecount, shooter,damage,bulletspeed,angle));
	magazine.current -= 1;
}

PoisonGun::PoisonGun(int damage, float firerate)
{
	this->damage = damage;
	this->firerate.Set(firerate);
	this->magazine.Set(999);

	accuracy = 1;
	bulletspeed = 150;
}
void PoisonGun::Shoot(Vector2f target, Vector2f shooter)
{
	if (firerate.current >= firerate.maximum)
	{
		Vector2f movecount;
		float distance = sqrt(pow((target.x - shooter.x), 2) + pow((target.y - shooter.y), 2));
		float angle = (atan2f(target.x - shooter.x, target.y - shooter.y) * 180 / 3.14) + rand() % accuracy - (accuracy / 2);
		movecount.x = (distance * sin(angle*3.14 / 180)) / (distance / bulletspeed);
		movecount.y = (distance * cos(angle*3.14 / 180)) / (distance / bulletspeed);
		EnemyBullet::enemybullet.push_back(new EnemyBullet(movecount, shooter, damage, bulletspeed, angle));
		firerate.current = 0;
	}
}
