#pragma once
#include "Objects.h"

class Layer
{
protected:
	RectangleShape window;
	RectangleShape boarder;
	bool activity;
	float clicktimer;
public:
	Layer();
	~Layer();
	//Functions
	virtual void Update(Vector2f mouse,const float &time) = 0;
	virtual void Draw(RenderTarget & target) = 0;
	virtual void CheckButtonInst(Button & button) = 0;
	virtual void Controls(Vector2f mouse, Event &event) = 0;
	//Getters
	inline const bool IsActive()const { return this->activity; }
	//Setters
	inline void ChangeActivity() { activity == false ? activity = true : activity = false; }
};

class StatScreen : public Layer
{
private:
	Texture winTex;
	Texture boardTex;
	vector<Button*>buttons;
	vector<Label*>label;
	const Player *player = 0;

	void UpdateLabels();
	void CheckButtonInst(Button & button);
public:
	StatScreen(Player * player);
	~StatScreen();
	//Functions
	void Update(Vector2i mouse, const float &time);
	void Draw(RenderTarget &target);
	
};

class BuildScreen : public Layer
{
private:
	//Building * selector = 0;
	RectangleShape portret;
	vector<Button*> button;
	Texture background;
	Text resourcesText;
	Text priceText;

	/*RectangleShape minimap;
	RectangleShape selsprite;
	RectangleShape selectorbar;
	RectangleShape commandbar;*/

	float clicktimer;
	float clicktimerMax = 0.3;
	
	vector<RectangleShape>modules;
	vector<Building*> building;
public:
	BuildScreen();
	void Update(Vector2f mouse,const float &time)override;
	void Draw(RenderTarget & target)override;
	void CheckButtonInst(Button & button)override;
	void CheckIconsInst(Building & building);
	void Controls(Vector2f mouse,Event &event)override;

	void SpawnBuilding(Vector2f mouse, obj::Type);

	static Selector selector;
};
