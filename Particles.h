#pragma once
#include "Elements.h"

class Particles
{
private:
	RectangleShape sprite;
	Color color;
	Vector2f movecount;
	float lifetime;
	float lifetimeMax;
	float slowdown;
	float transparent;

	int speed;
	bool alive;

public:
	//Constructor
	Particles(Vector2f position,
		Vector2f movecount,
		int speed,
		float lifetimeMax);

	virtual ~Particles();
	
	//Getters
	inline const Vector2f GetPosition()const { return this->sprite.getPosition(); }
	inline const bool IsAlive()const { return this->alive; }

	//Funtions
	void Update(const float &time);
	void Draw(RenderTarget&target);
	static void Generate(Vector2f position,
		Vector2f movecount,
		int ammount,
		int speed,
		float lifetimeMax);

	

	static vector<Particles*>particles;
};

