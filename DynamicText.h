#pragma once


#include "Particles.h"

class DynamicText
{
private:
	Text text;
	Font font;

	Vector2f direction;
	Color color;

	float lifetime;
	float lifetimeMax;
	float speed;
	float slowdown;
	float hidingtime;
	float transparent;
	bool alive;

public:
	//Constructor
	DynamicText(std::string text,
		Vector2f position,
		Vector2f direction,
		Color color,
		int size,
		float speed,
		float slowdown,
		float lifetime,
		float hidingtime);

	//Getters
	inline const bool IsAlive()const { return this->alive; }

	//Funtions
	void Update(const float &time);
	void Draw(RenderTarget &target);

	//Static
	static vector <DynamicText*> dynamictext;
	virtual ~DynamicText();
};

