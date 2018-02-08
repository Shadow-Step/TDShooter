#pragma once
#include "Bonuses.h"



class DynamicObjects
{
protected:
	RectangleShape hitBox;
	Sprite sprite;

	std::vector <int> targets;

	Vector2f target;
	Vector2f movecount;

	float distance;
	float speedmod;
	int bulletspeed;

	float lifetime;
	float lifetimeMax;

	
	bool life = true;
	

	int ricochetCharges = 3;
	int damage;
	static Color color;

public:
	DynamicObjects();
	virtual ~DynamicObjects();
	//Functions
	virtual void Update(const float &time);
	virtual void Draw(RenderTarget &target);
	void Spawn(int dmg, Vector2f target, Vector2f shooter);
	void ChangeTarget(Vector2f target);
	bool CheckTargetId(int id);
	void OutOfScreen(Vector2u windowsize);

	//Getters
	inline const FloatRect GetBound() const { return sprite.getGlobalBounds(); }
	inline const Vector2f GetPosition()const { return sprite.getPosition(); }
	inline const Vector2f GetCenter()const { return Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); }
	inline const bool Intersects(FloatRect target)const { return hitBox.getGlobalBounds().intersects(target); }
	inline const int GetDamage()const { return damage; }
	inline const bool IsAlive()const { return this->life; }
	inline const Vector2f GetCurrentSpeed()const { return this->movecount; }
	inline const Vector2f GetCurrentDirection()const { return Vector2f(this->GetCurrentSpeed().x / this->GetBulletSpeed(), this->GetCurrentSpeed().y / this->GetBulletSpeed()); }
	inline const int GetBulletSpeed()const { return this->bulletspeed; }
	inline const int GetRicCharges()const { return this->ricochetCharges; }
	//Setters
	inline void AddTargetId(int id) { targets.push_back(id); }
	inline void SetAlive(bool life) { this->life = life; }
	inline void SetRicCharges() { this->ricochetCharges--; }
	//Static
	static bool cuttingBullets;
	static vector<DynamicObjects*>dynamic;
};

class Bullet : public DynamicObjects
{
public:
	Bullet(int damage, Vector2f movecount, Vector2f shooter,float angle,int bulletspeed);
	
};

class AIBullet : public DynamicObjects
{
private:
	
	bool targetSelected;

	int targetID;

	//Private Functions
	
public:
	AIBullet(Vector2f movecount, Vector2f shooter, int damage, int bulletspeed, float angle);

	//Functions
	void Update(const float &time) override;

	//Getters
	inline const bool TargetSelected()const { return this->targetSelected; }
	inline const int GetTargetID()const { return this->targetID; }
	inline const float GetLifeTime()const { return this->lifetime; }
	//Setters
	inline void SetTarget(int id) { this->targetID = id; this->targetSelected = true; }
	inline void NoTarget() { this->targetSelected = false; }
	void UpdateMoveCords(Vector2f targetPosition);
	//Static
	static vector<AIBullet*>aibullet;
};

class Rocket : public DynamicObjects
{
public:
	Rocket(Vector2f movecount, Vector2f shooter, int damage, int bulletspeed, float angle);

	inline const bool TimerIsEnd()const { return this->lifetime >= lifetimeMax; }

	static vector<Rocket*>rocket;
};

class Splash : public DynamicObjects
{
private:
	CircleShape wave;

	float radius;
	float Xframe = 0;
	float Yframe = 0;
	float transparent;

	int animspeed;

	Vector2f scale;//temp
public:
	Splash(Vector2f position, Vector2f scale,float radius, int damage, float lifetimeMax, int animspeed);
	void Update(const float &time) override;
	void Draw(RenderTarget &target)override;

	static vector<Splash*>splash;
};

class EnemyBullet : public DynamicObjects
{
public:
	EnemyBullet(Vector2f movecount, Vector2f shooter, int damage, int bulletspeed, float angle);
	static vector<EnemyBullet*>enemybullet;
};