#include "Particles.h"

//Static
vector<Particles*>Particles::particles;

Particles::Particles(Vector2f position,
	Vector2f movecount,
	int slowdown,
	float lifetimeMax)
{
	this->color = Color::Red;
	this->transparent = 255;

	this->sprite.setSize(Vector2f(8, 8));
	this->sprite.setFillColor(color);
	this->sprite.setPosition(position);
	
	this->slowdown = slowdown;
	this->lifetimeMax = lifetimeMax;
	this->lifetime = 0;

	this->movecount.x = movecount.x / slowdown;
	this->movecount.y = movecount.y / slowdown;
	
}

void Particles::Update(const float &time)
{


	this->lifetime < this->lifetimeMax ? lifetime += time : this->alive = false;

	if (transparent > 0)
		transparent -= (255 / lifetimeMax)*time;
	if (transparent <= 0)
		transparent = 0;

	color.a = transparent;
	sprite.setFillColor(color);

	if (this->alive)
		this->sprite.move(this->movecount.x*time, this->movecount.y*time);
}
void Particles::Draw(RenderTarget&target)
{
	target.draw(this->sprite);
}

void Particles::Generate(Vector2f position,
	Vector2f movecount,
	int ammount,
	int slowdown,
	float lifetimeMax)
{
	for (size_t i = 0; i < ammount; i++)
	{
		particles.push_back(new Particles(position, movecount , slowdown, lifetimeMax));
	}
}

Particles::~Particles()
{
}