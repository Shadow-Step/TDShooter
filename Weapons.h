#pragma once

#include "DynamicObjects.h"

namespace weap
{
	enum pistols
	{
		p_Beretta,
		p_Glock17,
		p_Makarov,
		p_DesertEagle,
		p_AK47,
		p_M240
	};
	enum shotguns
	{
		s_Striker,
		s_Shotgun
	};
	enum ammoType
	{
		ammo_pistol,
		ammo_auto,
		ammo_shotgun,
		ammo_rocket
	};
}

enum Magazine
{
	CURRENT,
	MAX
};


class Weapons
{
protected:
	Sprite icon;
	float lifeTime;
	float lifeTimeMax;
public:
	Weapons();
	//Functions
	virtual void Shoot(Vector2f target, Vector2f shooter) = 0;
	inline void Draw(RenderTarget&target) { target.draw(this->icon); }
	void Update(const float &time);

	//Getters
	inline const FloatRect GetBound()const { return this->icon.getGlobalBounds(); }
	inline const bool IsAlive()const { return this->lifeTime < this->lifeTimeMax; }
	//Setters
	inline void SetIconPosition(Vector2f position) { this->icon.setPosition(position); }

	Sprite sprite;

	int bulletspeed;
	int accuracy;
	float reloadtime = 1;
	int damage;
	bool RELOAD;
	weap::ammoType ammoType;
	container <float> reload;
	container <float> firerate;
	container <int> magazine;

	static vector<Weapons*>weapons;
};

class Pistol : public Weapons
{
public:
	Pistol(Vector2f position,int model);
	void Shoot(Vector2f target, Vector2f shooter) override;
};

class ShotGun : public Weapons
{
public:
	ShotGun(Vector2f position,int model);
	void Shoot(Vector2f target, Vector2f shooter) override;
	int charges;
};

class Bazzoka : public Weapons
{
public:
	Bazzoka(Vector2f position,int model, int damage, float firerate, int magazine);
	void Shoot(Vector2f target, Vector2f shooter) override;
};

class HealGun : public Weapons
{
public:
	HealGun(int damage, float firerate, int bulletspeed);
	void Shoot(Vector2f target, Vector2f shooter) override;
};

class TeslaGun : public Weapons
{
public:
	TeslaGun(int damage, float firerate);
	void Shoot(Vector2f target, Vector2f shooter) override;
};

class AIMachineGun : public Weapons
{
public:
	AIMachineGun(Vector2f position,int model, int damage, float firerate, int magazine);
	void Shoot(Vector2f target, Vector2f shooter) override;
};

class PoisonGun : public Weapons
{
public:
	PoisonGun(int damage, float firerate);
	void Shoot(Vector2f target, Vector2f shooter) override;

};
