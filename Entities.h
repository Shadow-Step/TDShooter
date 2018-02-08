#pragma once
#include "Weapons.h"

namespace perk
{
	enum enum_Perks
	{
		enum_Melle,
		enum_FastReload,
		enum_Vampirism,
		SecondLife,
		enum_Ricochet,
		enum_Evasion
	};
}
enum _Animation
{
	_Move,
	_Reload,
	_Shoot,
	_Melle
};

class Entities
{
public:
	Entities();

	//Funtions
	virtual void Update(const float &time) = 0;
	virtual void Animation(const float &time);
	virtual void Draw(RenderTarget &target);
	
	//Setters
	virtual void TakeDamage(int damage);
	inline void SetRotation(int angle) { sprite.setRotation(angle); }
	inline void TakeHeal(int healcount) { this->health.current + healcount > health.maximum ? health.current = health.maximum : health.current += healcount; }
	
	//Getters
	inline const bool Intersects(FloatRect target) const { return this->GetBound().intersects(target); }
	inline const FloatRect GetBound() const { return this->hitBox.getGlobalBounds(); }
	inline const Vector2f GetPosition()const { return this->sprite.getPosition(); }
	inline const Vector2f GetCenter()const { return Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); }

	//#return health.current > health.max
	inline const bool IsAlive()const { return health.current > 0; }
	

	inline const int GetDamage()const { return this->damage; }

protected:
	Sprite sprite;
	RectangleShape hitBox;

	container <int> health;

	Vector2f movecount;

	int damage;
	int speed;
	bool alive;

	float blinkTimer;
	float blinkTimerMax = 0.08;

	float Xframe = 0;
	float Yframe = 0;
};

class Player : public Entities
{
private:
	Sprite feets;
	_Animation currentAnimation;

	float animTime;
	float animTimeMax;
	float startFrame;
	float currentFrame;
	float endFrame;
	float animspeed;

	float speedmod = 1;
	float reloadmod = 1;
	float hitTamer;
	float hitTamerMax;
	

	int xp = 0;
	int xpNext;
	int level = 1;
	int perkpoints = 0;

	bool shoot;
	bool perk[6];

	


	int ammo[4]{ 200,200,200,200 };

	int weaponsIndex;
	vector <Weapons*> weapons;
	Weapons *inhand;
	Vector2f movement;
public:

	Player();

	//Functions
	void Update(const float &time)override;
	void Animation(const float &time)override;
	void Draw(RenderTarget &target)override;
	void ReloadWeapon();
	void Shoot(Vector2i mouse);
	void LevelUp();
	void SwitchAmination(_Animation animation);

	//Getters
	inline const bool PerkExist(int number)const { return this->perk[number]; }
	inline const bool HitTimerReady()const { return this->hitTamer >= this->hitTamerMax; }
	inline const int GetPerkPoints()const { return this->perkpoints; }

	//Setters
	void TakeWeapon(Weapons *weapon);
	void SwitchWeapon(int iterator);
	void GainXp(int xp);
	void TakeDamage(int damage)override;
	inline void AddPerk(perk::enum_Perks perkname) { this->perk[perkname] = true; }
	void TakeAmmo();
	inline void SetSpeedMod(float speedmod) { this->speedmod = speedmod; }
	
	//std::vector<Effect*>effects;	
	friend class GUI;
	friend class GameLoop;
	friend class StatScreen;
};

//Abstract AI
class AI : public Entities
{
public:
	void Draw(RenderTarget &target)override;
	~AI();
protected:
	
	void SelectTarget();
	void Move(Vector2f targetPosition, const float &time);
	virtual void Shoot(Weapons*weapon, Vector2f target);
	RectangleShape durbarmax;
	RectangleShape durbarcurr;
	Entities * target = 0;
};
//Abstract Enemy
class Enemy : public AI
{
protected:
	float animspeed;

	_Animation currentAnimation;
	Color owncolor;
	container<float>hitrate;

	bool boss;
	int id;
	int xpMod;
public:
	//Getters
	inline const int GetId()const { return this->id; }
	inline const int CountXp()const { return (health.maximum + (damage / hitrate.maximum) + (speed / 2))*xpMod;}
	inline const bool ReadyToAttack()const { return this->hitrate.current >= this->hitrate.maximum; }
	inline const _Animation GetCurrentAnimation()const { return this->currentAnimation; }
	inline const bool IsBoss()const { return this->boss; }
	//Setters
	inline void ResetHitrate() { this->hitrate.current = 0; }
	virtual void SwitchAnimation(_Animation animation);

	static int StaticId;
	static vector<Enemy*>enemy;
};

//Start Enemies
class Zombie : public Enemy
{
public:
	Zombie(Vector2f position,Entities *target);
	void Update(const float &time)override;
	void Animation(const float &time)override;
	void SwitchAnimation(_Animation animation)override;
};

class Bug : public Enemy
{
public:
	Bug(Vector2f position,Entities *target);
	void Update(const float &time)override;
	void Animation(const float &time)override;
	void SwitchAnimation(_Animation animation)override;
};

class Insectoid : public Enemy
{
private:
	Weapons * primary;
	Vector2f path;
	bool pathfinded;
public:
	Insectoid(Vector2f position,Entities *target);
	~Insectoid();

	//Functions
	void Update(const float &time)override;
	void Animation(const float &time)override;
	void Shoot(Vector2f target);
	


	
};
//End Enemies

//Allies
class Allies : public AI
{

};
class Dron : public Allies
{
private:
	RectangleShape box;
	Weapons * primary = 0;
	Weapons * secondary = 0;
	float duration = 40;
public:
	Dron(Vector2f position);
	~Dron();
	void Update(const float &time);
	void Draw(RenderTarget & target)override;
	void Shoot(Weapons * weapon, Vector2f target)override;

	//Getters
	inline const bool TargetSelected()const { return this->target != nullptr; }
	inline const bool GetDurationLife()const { return this->alive; }
	//Setters
	inline void SetTarget(Entities * target) { this->target = target; }
	//Static
	static vector<Dron*>dron;
};