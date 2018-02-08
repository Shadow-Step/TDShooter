#include "DynamicText.h"

vector<DynamicText*> DynamicText::dynamictext;


DynamicText::DynamicText(std::string text,
	Vector2f position,
	Vector2f direction,
	Color color,
	int size,
	float speed,
	float slowdown,
	float lifetime,
	float hidingtime)
{
	this->color = color;
	this->transparent = 255;

	this->text.setFont(Resources::font);
	this->text.setString(text);
	this->text.setCharacterSize(size);
	this->text.setFillColor(this->color);
	this->text.setPosition(position);


	this->direction = direction;
	this->lifetimeMax = lifetime;
	this->lifetime = 0;
	this->hidingtime = hidingtime;
	this->speed = speed;
	this->slowdown = slowdown;
	this->alive = true;
}

DynamicText::~DynamicText()
{
}

void DynamicText::Update(const float &time)
{

	if (this->lifetime < this->lifetimeMax)
		this->lifetime += time;

	if (speed>0)
		speed -= slowdown * time;
	if (speed <= 0)
		speed = 0;
	if (this->lifetime > lifetimeMax - hidingtime)
	{
		if (transparent > 0)
			transparent -= (255 / hidingtime)*time;
		if (transparent <= 0)
			transparent = 0;

		color.a = transparent;
		text.setFillColor(color);
	}
	if (this->lifetime < this->lifetimeMax)
	{
		text.move(direction.x*speed*time, (direction.y*speed)*time);
	}
	else
	{
		alive = false;
	}
}

void DynamicText::Draw(RenderTarget &target)
{
	target.draw(this->text);
}