#pragma once
#include "DynamicText.h"

//Enum
namespace bonus
{
	enum BonusTypes
	{
		health_pack,
		ammo_pack,
		recharger,
		cuttingBullets,
		speedBooster,
		dronSpawner
	};
}


class Bonuses
{
protected:

	RectangleShape sprite;
	bonus::BonusTypes type;

	float rotationSpeed;
	float lifetime;
	float lifetimeMax;
	bool life;

public:
	Bonuses();

	//Functions
	virtual void Update(const float &time);
	void Draw(RenderTarget &target);

	//Getters
	inline const Vector2f GetPosition()const { return this->sprite.getPosition(); }
	inline const Vector2f GetCenter()const { return Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); }
	inline const FloatRect GetBounds()const { return this->sprite.getGlobalBounds(); }
	inline const bonus::BonusTypes GetType()const { return this->type; }
	inline const bool IsAlive()const { return this->life; }
	inline const bool LifeTimeIsEnd()const { return this->lifetime > lifetimeMax; }
	//Virtual
	virtual void PickUp() = 0;

	//Static
	static vector<Bonuses*>bonuses;

	~Bonuses();
};

class MedPack : public Bonuses
{
public:
	MedPack();
	void PickUp() override;
};

class AmmoPack : public Bonuses
{
public:
	AmmoPack();
	void PickUp() override;
};

class Recharger : public Bonuses
{
public:
	Recharger();
	void PickUp() override;
};

class CuttingBullets : public Bonuses
{
public:
	CuttingBullets();
	void PickUp()override;
};

class SpeedBooster : public Bonuses
{
public:
	SpeedBooster();
	void PickUp()override;
};

class DronSpawner : public Bonuses
{
public:
	DronSpawner();
	void PickUp()override;
};