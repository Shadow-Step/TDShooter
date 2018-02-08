#include "DynamicObjects.h"
//Static
vector<DynamicObjects*>DynamicObjects::dynamic;
vector<AIBullet*>AIBullet::aibullet;
vector<Rocket*>Rocket::rocket;
vector<Splash*>Splash::splash;
vector<EnemyBullet*>EnemyBullet::enemybullet;
bool DynamicObjects::cuttingBullets = false;

DynamicObjects::DynamicObjects()
{
#ifdef DEBUG
	this->hitBox.setFillColor(Color::Transparent);
	this->hitBox.setOutlineThickness(1);
	this->hitBox.setOutlineColor(Color::Red);
#endif // DEBUG
}
void DynamicObjects::Update(const float &time)
{
	if(this->lifetime < this->lifetimeMax)
		this->lifetime += time;
	else
		this->life = false;

	this->sprite.move(movecount.x*time, movecount.y*time);
	this->hitBox.setPosition(GetPosition());//temp
}
void DynamicObjects::Draw(RenderTarget & target)
{
	target.draw(this->sprite);
#ifdef DEBUG
	target.draw(this->hitBox);
#endif // DEBUG

}
void DynamicObjects::Spawn(int dmg, Vector2f target, Vector2f shooter)
{
	/*this->speedx = target.x - shooter.x;
	this->speedy = target.y - shooter.y;
	this->distance = sqrt(pow(speedx, 2) + pow(speedy, 2));*/
	this->speedmod = 1;
	this->life = true;
	this->damage = dmg;
	//this->dist = 0;
	targets.empty();
	sprite.setPosition(shooter);
}
void DynamicObjects::ChangeTarget(Vector2f target)
{
	Vector2f shooter = sprite.getPosition();
	float distance = sqrt(pow((target.x - shooter.x), 2) + pow((target.y - shooter.y), 2));
	float angle = (atan2f(target.x - shooter.x, target.y - shooter.y) * 180 / 3.14);
	this->movecount.x = (distance * sin(angle*3.14 / 180)) / (distance / bulletspeed);
	this->movecount.y = (distance * cos(angle*3.14 / 180)) / (distance / bulletspeed);
	this->sprite.setRotation(-angle);
}
bool DynamicObjects::CheckTargetId(int id)
{
	for (size_t i = 0; i < targets.size(); i++)
	{
		if (id == targets[i])
			return true;
	}
	return false;
}
void DynamicObjects::OutOfScreen(Vector2u windowsize)
{
	if (sprite.getPosition().x > windowsize.x ||
		sprite.getPosition().x < 0 ||
		sprite.getPosition().y>windowsize.y ||
		sprite.getPosition().y < 0)
		life = false;
}
DynamicObjects::~DynamicObjects()
{
}

////////
//Bullet
Bullet::Bullet(int damage, Vector2f movecount, Vector2f shooter,float angle,int bulletspeed)
{
	this->sprite.setTexture(Resources::bulletTextures[0]);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setScale(0.4, 0.4);
	this->sprite.setRotation(-angle);
	this->sprite.setColor(Color::Yellow);
	this->sprite.setPosition(shooter);

	this->hitBox.setSize(Vector2f(4, 4));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

	this->bulletspeed = bulletspeed;
	this->life = true;
	this->lifetimeMax = 3;
	this->lifetime = 0;
	
	this->damage = damage;
	this->movecount = movecount;
}

////////
//AIBullet
AIBullet::AIBullet(Vector2f movecount, Vector2f shooter, int damage, int bulletspeed, float angle)
{
	this->sprite.setTexture(Resources::bulletTextures[0]);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setScale(0.4, 0.4);
	this->sprite.setRotation(-angle);
	this->sprite.setColor(Color::Yellow);
	this->sprite.setPosition(shooter);

	this->hitBox.setSize(Vector2f(4, 4));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

	this->targetSelected = false;
	this->life = true;

	this->bulletspeed = bulletspeed;
	this->lifetimeMax = 3;
	this->lifetime = 0;
	this->damage = damage;
	this->movecount = movecount;

	
}
void AIBullet::Update(const float & time)
{
	if (this->lifetime < this->lifetimeMax)
		this->lifetime += time;
	else
		this->life = false;

	this->sprite.move(movecount.x * time, movecount.y*time);
	this->hitBox.setPosition(GetPosition());//temp
	
}
void AIBullet::UpdateMoveCords(Vector2f targetPosition)
{
	this->sprite.setRotation(-CountAngle(targetPosition, GetPosition())+180);
	this->movecount.x = (targetPosition.x - GetPosition().x) / (CountDistance(targetPosition, GetPosition()) / bulletspeed);
	this->movecount.y = (targetPosition.y - GetPosition().y) / (CountDistance(targetPosition, GetPosition()) / bulletspeed);
}

Rocket::Rocket(Vector2f movecount, Vector2f shooter, int damage, int bulletspeed, float angle)
{
	this->sprite.setTexture(Resources::bulletTextures[0]);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setScale(1, 1);
	this->sprite.setRotation(-angle);
	this->sprite.setColor(Color::Yellow);
	this->sprite.setPosition(shooter);

	this->hitBox.setSize(Vector2f(8, 8));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

	this->bulletspeed = bulletspeed;
	this->life = true;
	this->lifetimeMax = 2;
	this->lifetime = 0;

	this->damage = damage;
	this->movecount = movecount;
}

Splash::Splash(Vector2f position,Vector2f scale,float radius, int damage, float lifetimeMax, int animspeed)
{

	this->sprite.setTexture(Resources::bulletTextures[1]);
	this->sprite.setTextureRect(IntRect(0, 0, 64, 64));
	this->sprite.setOrigin(GetCenter());
	this->sprite.setScale(scale);
	this->sprite.setColor(Color::Yellow);
	this->sprite.setPosition(position);

	this->scale = scale;//temp
	this->transparent = 255;

	this->wave.setFillColor(Color::Transparent);
	this->wave.setOutlineThickness(22);
	this->wave.setPosition(position);



	this->hitBox.setSize(Vector2f(radius*1.5, radius*1.5));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
	this->hitBox.setPosition(GetPosition());

	this->life = true;
	this->lifetimeMax = lifetimeMax;
	this->lifetime = 0;
	this->radius = radius / lifetimeMax;

	this->damage = damage;
	this->animspeed = animspeed;
}
void Splash::Update(const float & time)
{
	if (this->lifetime < this->lifetimeMax)
		this->lifetime += time;

	if (transparent > 0)
		transparent -= (255/lifetimeMax)*time;
	if (transparent <= 0)
		transparent = 0;

	this->wave.setOutlineColor(Color(205, 76, 16, transparent));

	Xframe += time * animspeed;

	if ((int)Xframe > 4)
	{
		Xframe = 0;
		Yframe++;
	}
	if ((int)Xframe == 2 && (int)Yframe == 4)
	{
		this->life = false;
	}
	
	this->sprite.setTextureRect(IntRect((int)Xframe * 64,(int)Yframe * 64, 64, 64));
	if (this->lifetime < this->lifetimeMax)
	{
		this->wave.setRadius(radius*lifetime);
		this->wave.setOrigin(this->wave.getRadius(), this->wave.getRadius());
	}
}
void Splash::Draw(RenderTarget & target)
{
	target.draw(this->wave);
	target.draw(this->sprite);
#ifdef DEBUG
	target.draw(this->hitBox);
#endif // DEBUG
}

EnemyBullet::EnemyBullet(Vector2f movecount, Vector2f shooter, int damage, int bulletspeed, float angle)
{
	this->sprite.setTexture(Resources::bulletTextures[2]);
	this->sprite.setOrigin(GetCenter());
	this->sprite.setScale(0.20, 0.20);
	this->sprite.setRotation(-angle);
	this->sprite.setColor(Color::Yellow);
	this->sprite.setPosition(shooter);
	this->hitBox.setSize(Vector2f(4, 4));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

	this->bulletspeed = bulletspeed;
	this->life = true;
	this->lifetimeMax = 3;
	this->lifetime = 0;

	this->damage = damage;
	this->movecount = movecount;
}
