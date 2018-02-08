#pragma once
#include "GUI.h"

namespace obj
{
	enum resources
	{
		Iron,
		Stone,
		Wood,
		Gold
	};
	enum Type
	{
		Mine_Iron,
		Mine_Stone,
		Mine_Wood,
		Mine_Gold,
		Barrack,
		EMPTY = 999
	};
	enum ButtonsId
	{
		b_Mine_Iron,
		b_Mine_Stone,
		b_Mine_Wood,
		b_Mine_Gold,
		b_Barrack,
		b_Delete,
		b_Create_Peasant,
		b_Create_Marine
	};
}
namespace sel
{
	enum commands
	{
		None,
		Build,
		Move,
		Repair,
		EMPTY = 999
	};
}
namespace unit
{
	enum AI
	{
		Idle,
		Move,
		Shoot
	};
}

class Shell
{
public:
	static int resources[4];
	static int ID;
	static Vector2f portPos;
	static Vector2f buttPos;
	static Vector2f iconPos;

	static bool blockselector;
	static bool commandReady;

	static void SwitchCommand(obj::Type type);
	static void SwitchCommand(sel::commands command);

	static obj::Type type;
	static sel::commands command;
};

class Objects
{
protected:
	RectangleShape sprite;
	RectangleShape icon;
	RectangleShape portret;
	Texture spriteTex;

	RectangleShape healthbarMax;
	RectangleShape healthbar;

	int id;
	bool selected;
	bool life = true;
	vector<Button*>button;
	float health;
	float healthMax;

public:
	Objects();
	virtual ~Objects();

	//Functions
	virtual void Update(Vector2f mouse, const float &time) = 0;
	virtual void Draw(RenderTarget &target) = 0;
	virtual void Command(Vector2f position,int index) = 0;

	inline void DrawIcon(RenderTarget & target) { target.draw(icon); }
	inline void DrawPortret(RenderTarget & target) { target.draw(portret); }
	void Select(bool select);
	void DrawButtons(RenderTarget & target);
	obj::ButtonsId UpdateButtons(Vector2f mouse, const float &time);
	//Setter
	inline void SetIconPosition(Vector2f position) { icon.setPosition(position); }
	//Getter
	inline const int GetId()const { return this->id; }
	inline const bool Contains(Vector2f mouse)const { return this->sprite.getGlobalBounds().contains(mouse); }
	inline const FloatRect GetBounds()const { return sprite.getGlobalBounds(); }
	//
	
	static void InitTextures();
	
};
//Units
class Unit : public Objects
{
protected:
	float speed;
	float rotAngle;
	float hitrate;
	float hitrateMax;
	float hitrange;
	Vector2f movecount;
	Vector2f moveposition;
	RectangleShape movemarker;
	unit::AI ai = unit::AI::Idle;

	Weapons * weapon = 0;
	Enemy * target = 0;//temp,change to Object* target
	//Private Functions
public:
	void Command(Vector2f position,int index)override;
	void Move(Vector2f position, const float &time);
	void Shoot();
	void SelectTarget();
	static vector<Unit*>unit;
};
class Peasant : public Unit
{
public:
	Peasant(Vector2f position);
	void Update(Vector2f mouse, const float &time)override;
	void Draw(RenderTarget & target)override;
};
class Marine : public Unit
{
public:
	Marine(Vector2f position);
	void Update(Vector2f mouse, const float &time)override;
	void Draw(RenderTarget & target)override;
};
//Buildings
class Building : public Objects
{
protected:
	RectangleShape buildbar;
	RectangleShape buildbaridle;
	RectangleShape spawnsprite;
	elem::ElemInstance instance;
	
	bool blocked;
	bool constructed;
	bool spawnpoint;
	float buildTime;
	float buildTimeMax;
	
	obj::Type type;

public:
	//Functions
	void Command(Vector2f position,int index)override;
	inline void DrawIcon(RenderTarget & target) { target.draw(this->icon); }
	void UpdateIcon(Vector2f mouse, const float &time);
	const bool CanBePlaced()const;
	//Getters
	inline const int GetPrice()const { return *this->price; }
	inline const elem::ElemInstance GetInstance()const { return this->instance; }
	inline const obj::Type GetType()const { return this->type; }
	inline const bool IsBlocked()const { return blocked; }
	
	
	//Setters
	inline void SetInstance(elem::ElemInstance instance) { this->instance = instance; }
	inline void SetIconColor(Color color) { this->icon.setFillColor(color); }
	
	int price[4];

	friend class BuildScreen;
	static vector<Building*>building;
	
};
class Mine : public Building
{
private:
	float productTime;
	float productTimeMax;
	int productivity;
	obj::resources resource;
public:
	Mine();
	Mine(Vector2f position, obj::Type type);
	
	//Functions
	void Update(Vector2f mouse, const float &time)override;
	void Draw(RenderTarget & target)override;
	//Getters
	
	//Static
	static Texture mineTexture;
};
class Barrack : public Building
{
private:
	float productTime;
	float productTimeMax;
	vector<obj::ButtonsId> action;
public:
	Barrack(Vector2f position,obj::Type type);
	void Update(Vector2f mouse, const float &time)override;
	void Draw(RenderTarget & target)override;
};
////////////////////////////////////
class Selector
{
private:
	vector<Objects*>selector;
	RectangleShape dragbox;
	RectangleShape buildSprite;

	sel::commands command;
	obj::Type buildingtype;

	Vector2f clickposition;

	int capacity;
	float dragtimer = 0;

	bool buildmode;
	bool empty;
	bool blocked;

	bool dragmode;
	bool dragOn;

	//Private Functions
	void Build(Vector2f mouse);
	void Select(Vector2f mouse);
public:
	Selector();
	//Functions
	void Update(Vector2f mouse,const float &time);
	void Draw(RenderTarget &target);

	//Actions
	void LeftAction(Vector2f mouse);
	void RightAction(Vector2f mouse);
	void SwitchCommand(sel::commands command) { this->command = command; }
	void SwitchCommand(obj::Type buildingtype);
	
	//Setters
	inline void DragOn(Vector2f mouse, bool drag) { this->dragOn = drag; clickposition = mouse; }
	//Getters
	inline const bool GetDragOn()const { return this->dragOn; }

	//Selector accessors
	void Add(Objects* target);
	void Clear();
	void Clear(int id);
	
	friend class BuildScreen;
};
