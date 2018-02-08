#include "Entities.h"

//Statics
int Enemy::StaticId;
vector<Enemy*>Enemy::enemy;
vector<Dron*>Dron::dron;

//Entities
Entities::Entities()
{
#ifdef DEBUG
	this->hitBox.setFillColor(Color::Transparent);
	this->hitBox.setOutlineThickness(1);
	this->hitBox.setOutlineColor(Color::Red);
#endif // DEBUG
}
void Entities::Animation(const float &time)
{
}
void Entities::Draw(RenderTarget & target)
{
	target.draw(this->sprite);
}
void Entities::TakeDamage(int damage)
{
	this->health.current - damage < 0 ? health.current = 0 : health.current -= damage; 
	this->sprite.setColor(Color::Red); 
	this->blinkTimer = 0;
}

////////
//Player
Player::Player()
{	
	this->sprite.setTexture(Resources::playerTTex[2][55]);
	this->sprite.setOrigin(102, 119);
	this->sprite.scale(0.2, 0.2);
	this->sprite.setPosition(200, 200);

	this->feets.setTexture(Resources::playerFeetTextures[5]);
	this->feets.setOrigin(feets.getLocalBounds().width / 2, feets.getLocalBounds().height / 2);
	this->feets.setScale(0.2, 0.2);

	this->hitBox.setSize(Vector2f(20, 20));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

	this->health.Set(100);
	this->damage = 10;
	this->weaponsIndex = 0;

	Pistol *temp = new Pistol(Vector2f(0,0),weap::p_M240);
	TakeWeapon(temp);
	SwitchWeapon(0);

	this->inhand->RELOAD = false; // temp

	this->level = 1;
	this->xp = 0;
	this->xpNext = this->level * 1000;

	this->hitTamerMax = 0.2;
}
void Player::Update(const float &time)
{
	
	if (inhand->RELOAD && currentAnimation != _Reload && currentAnimation != _Melle)
		SwitchAmination(_Reload);
	else if (!inhand->RELOAD && currentAnimation == _Reload)
		SwitchAmination(_Move);

	if (this->shoot && currentAnimation != _Shoot && currentAnimation != _Reload && inhand->magazine.current>0)
	{
		SwitchAmination(_Shoot);
		this->sprite.setOrigin(102, 119);
	}
	else if (!this->shoot && currentAnimation == _Shoot && currentFrame == endFrame)
		SwitchAmination(_Move);

	if (currentAnimation == _Melle && currentFrame == endFrame)
	{
		this->sprite.setOrigin(102, 119);
		SwitchAmination(_Move);
	}

	Animation(time);//temp
	if (this->blinkTimer < this->blinkTimerMax)
		this->blinkTimer += time;
	if (this->blinkTimer >= this->blinkTimerMax)
		this->sprite.setColor(Color::White);

	if (this->hitTamer < this->hitTamerMax)
		this->hitTamer += time;

	if (inhand->RELOAD)
	{
		if (perk[perk::enum_FastReload])
			this->inhand->reload.current += time * 1.25;
		else
			this->inhand->reload.current += time;
	}
	if (inhand->reload.current > inhand->reload.maximum)
	{
		this->inhand->RELOAD = false;
		this->inhand->reload.current = this->inhand->reload.maximum;
	}

	/*for (size_t i = 0; i < effects.size(); i++)
	{
		if (effects[i]->active == false)
			effects[i]->AddEffect();
		else if (effects[i]->active == true)
			effects[i]->CheckEffect(time);
		if (effects[i]->life == false)
		{
			effects[i]->EraseEffect();
			delete effects[i];
			effects.erase(effects.begin() + i);
		}
	}*/

	if (inhand->firerate.current < inhand->firerate.maximum)
		inhand->firerate.current += time;
	//colortime += time;
	//if (colortime > 0.3)
	//	sprite.setColor(Color::White);

	if (health.current < 0)
		health.current = 0;
	else if (health.current > health.maximum)
		health.current = health.maximum;

	
	//Movement
	sprite.move((this->movement.x*time)*this->speedmod,
		(this->movement.y*time)*this->speedmod);
	
	this->feets.setPosition(GetPosition());

	if (movement.x != 0 || movement.y != 0)
	{
		//Animation(time);
	}

	this->hitBox.setPosition(GetPosition());//temp Hit box
}
void Player::Draw(RenderTarget & target)
{
	target.draw(this->feets);
	target.draw(this->sprite);

#ifdef DEBUG
	RectangleShape box(Vector2f(3, 3));
	box.setFillColor(Color::Red);
	box.setPosition(sprite.getPosition());
	target.draw(box);
	target.draw(hitBox);
#endif // DEBUG
}
void Player::Shoot(Vector2i mouse)
{
	if (inhand->magazine.current > 0 && inhand->RELOAD == false)
	{
		if (inhand->firerate.current >= inhand->firerate.maximum)
		{
			inhand->Shoot((Vector2f)mouse, GetPosition());
			inhand->firerate.current = 0;
		}
	}
	else if (inhand->magazine.current <= 0 && inhand->RELOAD == false)
		ReloadWeapon();
}
void Player::LevelUp()
{
	this->perkpoints++;
	this->health.current = this->health.maximum;
}
void Player::SwitchAmination(_Animation animation)
{
	switch (animation)
	{
	case _Move:
		this->currentAnimation = animation;
		this->startFrame = 0;
		this->endFrame = 19;
		this->currentFrame = this->startFrame;
		this->animspeed = 25;
		this->animTime = 0;
		this->animTimeMax = 1/this->animspeed;
		break;
	case _Reload:
		this->currentAnimation = animation;
		this->startFrame = 20;
		this->endFrame = 39;
		if (inhand->ammoType == weap::ammo_pistol)
		{
			this->endFrame -=5;
		}
		this->currentFrame = this->startFrame;
		this->animspeed = 25;
		this->animTime = 0;
		this->animTimeMax = 1 / this->animspeed;
		break;
	case _Shoot:
		this->currentAnimation = animation;
		this->startFrame = 40;
		this->endFrame = 42;
		if (inhand->ammoType == weap::ammo_pistol)
		{
			this->startFrame -= 5;
			this->endFrame -= 5;
		}
		this->currentFrame = this->startFrame;
		this->animspeed = 5;
		this->animTime = 0;
		this->animTimeMax = this->inhand->firerate.maximum/3;
		break;
	case _Melle:
		this->currentAnimation = animation;
		this->startFrame = 43;
		this->endFrame = 57;
		this->sprite.setOrigin(115, 201);
		if (inhand->ammoType == weap::ammo_pistol)
		{
			this->startFrame -= 5;
			this->endFrame -= 5;
		}
		if (inhand->ammoType == weap::ammo_pistol || inhand->ammoType == weap::ammo_rocket)
		{
			this->sprite.setOrigin(103, 124);
		}
		this->currentFrame = this->startFrame;
		this->animspeed = 25;
		this->animTime = 0;
		this->animTimeMax = 1 / this->animspeed;
		
		break;
	default:
		break;
	}
}
void Player::ReloadWeapon()
{
	if (ammo[inhand->ammoType] > 0 && inhand->RELOAD == false && inhand->magazine.current<inhand->magazine.maximum)
	{
		inhand->RELOAD = true;
		inhand->reload.current = 0;
		int temp = inhand->magazine.maximum - inhand->magazine.current;
		if (ammo[inhand->ammoType] < temp)
		{
			temp = ammo[inhand->ammoType];
			inhand->magazine.current += temp;
			ammo[inhand->ammoType] -= temp;
		}
		else
		{
			(inhand->magazine.current) += temp;
			ammo[inhand->ammoType] -= temp;
			
		}
	}
}
void Player::Animation(const float &time)
{
	if (movement.x != 0 || movement.y != 0)
	{
		Xframe += time * 30;
		if (Xframe > 19)
			Xframe = 0;
		this->feets.setTexture(Resources::playerFeetTextures[(int)Xframe]);
		//this->feets.setOrigin(feets.getLocalBounds().width / 2, feets.getLocalBounds().height / 2);
	}

	this->animTime += time;
	if (this->animTime >= this->animTimeMax)
	{
		currentFrame++;
		animTime = 0;
		if (this->currentFrame > this->endFrame)
			this->currentFrame = this->startFrame;
	}

	this->sprite.setTexture(Resources::playerTTex[inhand->ammoType][(int)currentFrame]);
}
void Player::TakeWeapon(Weapons * weapon)
{
	if (this->weapons.size() < 2)
		this->weapons.push_back(weapon);
	else
	{
		delete this->weapons[weaponsIndex];
		this->weapons[weaponsIndex] = &(*weapon);
		inhand = &(*weapons[weaponsIndex]);
	}
	
}
void Player::SwitchWeapon(int iterator)
{
	if(this->weapons.size()>1)
	this->weaponsIndex += iterator;

	if (this->weaponsIndex > 1)
		this->weaponsIndex = 0;
	else if (this->weaponsIndex < 0)
		this->weaponsIndex = this->weapons.size() - 1;
		
	this->inhand = &(*weapons[weaponsIndex]);
	currentFrame = 0;
	
}

//Player Setters
void Player::GainXp(int xp)
{
	this->xp += xp;
	if (this->xp >= xpNext)
	{
		this->xp -= xpNext;
		this->level++;
		DynamicText::dynamictext.push_back(new DynamicText(Resources::strings[str_LevelUp],
			Vector2f(GetPosition().x - 45,
				GetPosition().y),
			Vector2f(0, -1),
			Color::Yellow,
			22,
			250.f,
			300.f,
			2.f,
			1.f));
		this->xpNext = this->level * 1000;
		LevelUp();	
	}
}
void Player::TakeDamage(int damage)
{
	if (this->perk[perk::enum_Evasion] && rand()%100+1 >=80)
	{
		DynamicText::dynamictext.push_back(new DynamicText(Resources::strings[str_Avoid],
			Vector2f(GetPosition().x - 12,
				GetPosition().y),
			Vector2f(0, -1),
			Color::Magenta,
			12,
			250.f,
			500.f,
			1.f,
			0.5));
		this->hitTamer = 0;
		SwitchAmination(_Melle);
	}
	else
	{
		this->health.current - damage < 0 ? health.current = 0 : health.current -= damage;
		this->sprite.setColor(Color::Red);
		this->blinkTimer = 0;
		this->hitTamer = 0;

		DynamicText::dynamictext.push_back(new DynamicText("-" + to_string(damage),
			Vector2f(GetPosition().x - 12, GetPosition().y),
			Vector2f(0, -1),
			Color::Red,
			16,
			200.f,
			300.f,
			1.f,
			1.f));
	}
}
void Player::TakeAmmo()
{
	ammo[weap::ammo_pistol] + 21 > 999 ? this->ammo[weap::ammo_pistol] = 999 : this->ammo[weap::ammo_pistol] += 21;
	ammo[weap::ammo_auto] + 200 > 999 ? this->ammo[weap::ammo_auto] = 999 : this->ammo[weap::ammo_auto] += 200;
	ammo[weap::ammo_shotgun] + 14 > 999 ? this->ammo[weap::ammo_shotgun] = 999 : this->ammo[weap::ammo_shotgun] += 14;
	ammo[weap::ammo_rocket] + 7 > 999 ? this->ammo[weap::ammo_rocket] = 999 : this->ammo[weap::ammo_rocket] += 7;
}

////////
//AI
void AI::Move(Vector2f targetPosition, const float &time)
{
	if (CountDistance(targetPosition,GetPosition()) != 0)
	{
		movecount.x = speed * time * (targetPosition.x - GetPosition().x) / CountDistance(targetPosition, GetPosition());
		movecount.y = speed * time * (targetPosition.y - GetPosition().y) / CountDistance(targetPosition, GetPosition());
		sprite.move(movecount);
		SetRotation(-CountAngle(targetPosition, GetPosition())+180);
	}
}
void AI::Shoot(Weapons * weapon, Vector2f target)
{
}
void AI::Draw(RenderTarget & target)
{
	target.draw(this->sprite);
	if (this->health.current < this->health.maximum)
	{
		target.draw(this->durbarmax);
		target.draw(this->durbarcurr);
	}
#ifdef DEBUG
	target.draw(this->hitBox);//temp
#endif // DEBUG

	
}
AI::~AI()
{
	
}

////////
//Enemy
void Enemy::SwitchAnimation(_Animation animation)
{
}
////////
//Zombie
Zombie::Zombie(Vector2f position,Entities *target)
{
	this->id = Enemy::StaticId;
	Enemy::StaticId++;

	this->sprite.setTexture(Resources::mobTextures[ZOMBIE]);
	this->sprite.setTextureRect(IntRect(0, 0, 128, 128));
	this->sprite.setOrigin(GetCenter());
	this->sprite.setScale(0.7, -0.7);
	this->sprite.setPosition(position);
	this->owncolor = Color::White;

	this->hitBox.setSize(Vector2f(26, 26));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
	
	this->health.Set(100);
	this->damage = 15;
	this->hitrate.Set(1);
	this->speed = 50;
	this->xpMod = 1;

	this->target = target;

	this->durbarmax.setSize(Vector2f(this->hitBox.getSize().x, 5));
	this->durbarmax.setFillColor(Color::Black);
	this->durbarcurr.setFillColor(Color::Red);

	this->animspeed = 20;

	if (int x = rand() % 100 > 96)
	{
		this->boss = true;
		this->owncolor = (Color(180, 0, 0, 255));
		this->sprite.setColor(owncolor);
		this->sprite.setScale(1.1, -1.1);
		this->hitBox.setSize(Vector2f(26, 26));
		this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

		this->health.Set(350);
		this->damage = 33;
		this->hitrate.Set(2);
		this->speed = 20;
		this->xpMod = 1;
	}
}
void Zombie::Update(const float &time)
{
	if (this->blinkTimer < this->blinkTimerMax)
		this->blinkTimer += time;
	if (this->blinkTimer >= this->blinkTimerMax)
		this->sprite.setColor(owncolor);

	if (hitrate.current<hitrate.maximum)
		hitrate.current += time;

	durbarcurr.setSize(Vector2f(durbarmax.getSize().x*((float)health.current/ (float)health.maximum), 5));
	durbarmax.setPosition(sprite.getPosition().x-hitBox.getSize().x/2, sprite.getPosition().y + 20);
	durbarcurr.setPosition(sprite.getPosition().x-hitBox.getSize().x / 2, sprite.getPosition().y + 20);
	if(currentAnimation != _Melle)
	Move(target->GetPosition(), time);

	Animation(time);

	this->hitBox.setPosition(GetPosition());//temp
}
void Zombie::Animation(const float &time)
{

	switch (this->currentAnimation)
	{
	case _Move:
		Xframe += time * animspeed;
		if (Xframe > 8)
		{
			Xframe = 0;
			Yframe++;
		}
		if ((int)Yframe >= 3 && (int)Xframe > 2)
		{
			Yframe = 0;
			Xframe = 0;
		}
		break;
	case _Melle:
		Xframe += time * animspeed;
		if (Xframe > 8)
		{
			Xframe = 0;
			Yframe++;
		}
		if ((int)Yframe >= 7 && (int)Xframe > 6)
		{
			SwitchAnimation(_Move);
		}
		break;
	default:
		break;
	}
	
	sprite.setTextureRect(IntRect(128 * (int)Xframe, 128 * (int)Yframe, 128, 128));
}
void Zombie::SwitchAnimation(_Animation animation)
{
	this->currentAnimation = animation;
	switch (animation)
	{
	case _Move:
		this->Xframe = 0;
		this->Yframe = 0;
		this->animspeed = 20;
		break;
	case _Melle:
		this->animspeed = 30;
		this->Xframe = 3;
		this->Yframe = 3;
		break;
	default:
		break;
	}
}

////////
//Bug
Bug::Bug(Vector2f position,Entities *target)
{
	this->id = Enemy::StaticId;
	Enemy::StaticId++;

	this->sprite.setTexture(Resources::mobTextures[BUG]);
	this->sprite.setTextureRect(IntRect(192, 48, 48, 48));
	this->sprite.setOrigin(GetCenter());
	this->sprite.setScale(1, 1);
	this->sprite.setPosition(position);

	this->owncolor = Color::White;

	this->hitBox.setSize(Vector2f(26, 26));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

	this->health.Set(30);
	this->hitrate.Set(0.3);
	this->damage = 7;
	this->speed = 150;
	this->xpMod = 1;

	this->target = target;

	this->durbarmax.setSize(Vector2f(this->hitBox.getSize().x, 5));
	this->durbarmax.setFillColor(Color::Black);
	this->durbarcurr.setFillColor(Color::Red);

	this->animspeed = 15;
	SwitchAnimation(_Move);

	if (int x = rand() % 100 > 95)
	{
		this->boss = true;
		this->owncolor = (Color(180, 180, 0, 255));
		this->sprite.setColor(owncolor);
		this->sprite.setScale(0.8, 0.8);
		this->hitBox.setSize(Vector2f(26, 26));
		this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

		this->animspeed = 25;

		this->health.Set(150);
		this->damage = 2;
		this->hitrate.Set(0.2);
		this->speed = 200;
		this->xpMod = 1;
	}
}
void Bug::Update(const float &time)
{
	if (this->blinkTimer < this->blinkTimerMax)
		this->blinkTimer += time;
	if (this->blinkTimer >= this->blinkTimerMax)
		this->sprite.setColor(owncolor);

	if (hitrate.current<hitrate.maximum)
		hitrate.current += time;

	durbarcurr.setSize(Vector2f(durbarmax.getSize().x*((float)health.current / (float)health.maximum), 5));
	durbarmax.setPosition(sprite.getPosition().x - hitBox.getSize().x / 2, sprite.getPosition().y + 20);
	durbarcurr.setPosition(sprite.getPosition().x - hitBox.getSize().x / 2, sprite.getPosition().y + 20);
	if(this->currentAnimation != _Melle)
	Move(target->GetPosition(), time);
	Animation(time);
	this->hitBox.setPosition(GetPosition());//temp
}
void Bug::Animation(const float &time)
{
	switch (this->currentAnimation)
	{
	case _Move:
		Xframe += time * animspeed;
		if (Xframe > 3)
		{
			Xframe = 1;
			Yframe++;
		}
		if ((int)Yframe > 4)
		{
			Yframe = 3;
			Xframe = 1;
		}
		break;
	case _Melle:
		Xframe += time * animspeed;
		if (Xframe > 5)
		{
			SwitchAnimation(_Move);
		}
		break;
	default:
		break;
	}
	sprite.setTextureRect(IntRect((48 * (int)Xframe), (48 * (int)Yframe), 48, 48));

}
void Bug::SwitchAnimation(_Animation animation)
{
	this->currentAnimation = animation;
	switch (animation)
	{
	case _Move:
		this->Xframe = 1;
		this->Yframe = 3;
		this->animspeed = 10;
		break;
	case _Melle:
		this->Xframe = 0;
		this->Yframe = 6;
		this->animspeed = 12;
		break;
	default:
		break;
	}
}

////////
//Insectoid
Insectoid::Insectoid(Vector2f position,Entities *target)
{
	this->id = Enemy::StaticId;
	Enemy::StaticId++;

	this->sprite.setTexture(Resources::mobTextures[BUG]);
	this->sprite.setTextureRect(IntRect(0, 0, 48, 48));
	this->sprite.setOrigin(GetCenter());
	this->sprite.setScale(1, 1);
	this->sprite.setPosition(position);
	this->owncolor = Color::White;

	this->hitBox.setSize(Vector2f(24, 24));
	this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
	
	this->primary = new PoisonGun(15, 5);

	this->health.Set(150);
	this->hitrate.Set(1);
	this->damage = 11;
	this->speed = 90;
	this->xpMod = 1;

	this->target = target;

	this->durbarmax.setSize(Vector2f(this->hitBox.getSize().x, 5));
	this->durbarmax.setFillColor(Color::Black);
	this->durbarcurr.setFillColor(Color::Red);

	if (int x = rand() % 100 > 95)
	{
		delete primary;
		this->primary = new PoisonGun(25, 2);
		this->boss = true;
		this->owncolor = (Color::Magenta);
		this->sprite.setColor(owncolor);
		this->sprite.setScale(1.2, 1.2);
		this->hitBox.setSize(Vector2f(26, 26));
		this->hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);

		this->health.Set(270);
		this->hitrate.Set(0.5);
		this->damage = 21;
		this->speed = 130;
		this->xpMod = 1;
	}
}
void Insectoid::Update(const float &time)
{
	if (this->blinkTimer < this->blinkTimerMax)
		this->blinkTimer += time;
	if (this->blinkTimer >= this->blinkTimerMax)
		this->sprite.setColor(owncolor);

	durbarcurr.setSize(Vector2f(durbarmax.getSize().x*((float)health.current / (float)health.maximum), 5));
	durbarmax.setPosition(sprite.getPosition().x - hitBox.getSize().x / 2, sprite.getPosition().y + 20);
	durbarcurr.setPosition(sprite.getPosition().x - hitBox.getSize().x / 2, sprite.getPosition().y + 20);

	if (hitrate.current<hitrate.maximum)
		hitrate.current += time;
	if (primary->firerate.current < primary->firerate.maximum)
		primary->firerate.current += time;

	if (primary->firerate.current >= primary->firerate.maximum)
	{
		Shoot(target->GetPosition());
		SetRotation(-CountAngle(target->GetPosition(), GetPosition()) + 180);
		
	}
	if (pathfinded == false)
	{
		path.x = rand() % 1380;
		path.y = rand() % 760;
		
		pathfinded = true;
	}
	if (pathfinded == true && primary->firerate.current>0.5)
	{
		if ((int)CountDistance(path,GetPosition()) == 0)
			pathfinded = false;
		Move(path, time);
		Animation(time);
	}
	
	
	this->hitBox.setPosition(GetPosition());//temp
}
void Insectoid::Shoot(Vector2f target)
{
	if (primary->firerate.current >= primary->firerate.maximum)
	{
		primary->Shoot(target, sprite.getPosition());
		primary->firerate.current = 0;
	}
}
void Insectoid::Animation(const float &time)
{
	Xframe += time * 15;
	if (Xframe > 3)
	{
		Xframe = 0;
		Yframe++;
	}
	if ((int)Yframe > 1)
	{
		Yframe = 0;
		Xframe = 0;
	}
	sprite.setTextureRect(IntRect(48 + (48 * (int)Xframe), 0 + (48 * (int)Yframe), 48, 48));
}
Insectoid::~Insectoid()
{
	delete this->primary;
}

Dron::Dron(Vector2f position)
{
	sprite.setTexture(Resources::mobTextures[2]);
	sprite.setTextureRect(IntRect(276, 276, 92, -92));
	sprite.setOrigin(46, 46);
	sprite.setScale(0.5, 0.5);
	sprite.setPosition(position);

	this->alive = true;
	this->speed = 300;
	this->primary = new Pistol(Vector2f(0, 0), weap::p_DesertEagle);

	durbarmax.setSize(Vector2f(duration*1, 5));
	durbarmax.setOutlineThickness(1);
	durbarmax.setOutlineColor(Color::Black);
	durbarcurr.setFillColor(Color::Yellow);
	durbarcurr.setOutlineThickness(1);
	durbarcurr.setOutlineColor(Color::Black);
}
Dron::~Dron()
{
	delete this->primary;
	delete this->secondary;
}
void Dron::Update(const float & time)
{
	//Update timers
	this->primary->firerate.current += time;
	if (duration > 0)
		this->duration -= time;
	else
		this->alive = false;

	//Update bars
	durbarcurr.setSize(Vector2f(duration*1, 5));
	durbarmax.setPosition(sprite.getPosition().x - 22, sprite.getPosition().y + 20);
	durbarcurr.setPosition(sprite.getPosition().x - 22, sprite.getPosition().y + 20);

	if (TargetSelected())
	{
		if (CountDistance(target->GetPosition(), this->GetPosition()) > 100)
			this->Move(target->GetPosition(), time);
		else
			this->Shoot(this->primary, target->GetPosition());
		if (!target->IsAlive())
			target = nullptr;
	}
}
void Dron::Draw(RenderTarget & target)
{
	target.draw(this->sprite);
	target.draw(this->durbarmax);
	target.draw(this->durbarcurr);
}
void Dron::Shoot(Weapons * weapon, Vector2f target)
{
	if (weapon->firerate.current >= weapon->firerate.maximum)
	{
		weapon->Shoot(target, GetPosition());
		weapon->firerate.current = 0;
	}
}

