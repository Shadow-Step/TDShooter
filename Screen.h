#pragma once
#include "Layer.h"
enum enum_Instances
{
	enum_IDLE,
	enum_ONMOUSE,
	enum_ONCLICK,
	enum_ACTIVE
};
namespace inst
{
	enum GameStages
	{
		mainmenu,
		gameloop,
		statscreen
	};
}

class Screen
{
private:
	
	Texture texture1;//
	Texture texture2;//

	RectangleShape menu;
	RectangleShape menuBoard;
	Event event;
	
	Text text;

	bool dragMenu;
	int buttonview;
	int buttonsOnScreen;

	Vector2f rememberPos;

	float clickTimer;
	float clickTimerMax;

	class Button
	{
	private:
		RectangleShape button;
		Text text;
		Text info;
		enum_Instances instance;
		Vector2f size;
		int type;

		Texture texture;

		RectangleShape aaa;
		RectangleShape bbb;


	public:
		Button(Vector2f size,int type);
		void Draw(RenderTarget & target);
		void Update(const Vector2f &menuPosition,const int &buttonNumber);
		inline void ChangeInstance(enum_Instances new_instance) { this->instance = new_instance; }
		inline const enum_Instances GetInstance()const { return this->instance; }
		inline const bool Contains(Vector2f target)const { return this->button.getGlobalBounds().contains(target); }
		inline const int GetType()const { return this->type; }
		inline void ChangeButtonColor(Color color) { this->button.setFillColor(color); }
		inline void ChangeTextColor(Color color) { this->text.setFillColor(color); }
		inline void SetPosition(Vector2f position) { this->button.setPosition(position); }
	};

public:
	Screen();
	virtual ~Screen();

	//Functions
	void Update(Player *player,Vector2f mousePos,const float &time);
	void Draw(RenderTarget &target);
	void SetButtonsView(int iterator);
	void CheckInstances(Player *player);
	inline void CatchEvent(Event event) { this->event = event; }
	inline const bool ClickTimerReady()const { return this->clickTimer >= this->clickTimerMax; }
	//Getters
	
	static vector<Button*>button;
	
};
class Stage
{
protected:
	RenderWindow * window;
	inst::GameStages stageName;
	inst::GameStages *currentStage;
	inline void SwitchStage(inst::GameStages stage){*this->currentStage = stage; }
	Cursor *cursor = 0;
public:
	~Stage();
	virtual void Update(const float &time) = 0;
	virtual void Draw() = 0;
	virtual void Controls(Event &event) = 0;
	
	inline inst::GameStages GetStage() { return this->stageName; }
};
class GameLoop : public Stage
{
private:
	Vector2f winsize;

	GUI gui;
	Screen* perkScreen = 0;
	Sprite background;
	Texture tex;
	
	
	Player* player = 0;
	Layer * inventory = 0;

	
	bool freeze;
	bool reset;
	float gametime[3];
public:
	GameLoop(RenderWindow * window,inst::GameStages * currentStage);
	virtual ~GameLoop();

	//Funtions
	void Update(const float &time)override;
	void UpdatePlayer(const float&time);
	void UpdateEnemies(const float &time);
	void UpdateDynamicObjects(const float &time);
	void UpdateBonuses(const float &time);
	void UpdateDynamicText(const float &time);
	void UpdateParticles(const float &time);
	void UpdateAllies(const float &time);
	void UpdateBuildings(const float &time);
	void Spawner(const float &time);
	int GetNearestTargetID(Vector2f position);

	void Draw()override;
	void InitResources();
	void Controls(Event &event)override;
};
class MainMenu : public Stage
{
private:
	RectangleShape background;
	Texture backTexture;
	Texture buttonTexture;
	vector <Button*> button;
	
	
public:
	MainMenu(RenderWindow * window,inst::GameStages * currentStage);
	~MainMenu();

	//Functions
	void Update(const float &time)override;
	void Draw()override;
	void Controls(Event &event)override;
	void CheckInstances();
};

