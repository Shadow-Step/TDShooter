#pragma once
#include "Resources.h"
//example
//newgame = new Button(Vector2f(200,50),Vector2f(300,300),tex,1);
//newgame->SetButtonText("New game", Color::Red, 36);
//newbar = new Bar(Vector2f(200, 20), Vector2f(500, 300), tex, tex, 1);
//newbar->SetDynamArgument(&player->health.current, &player->health.maximum);

namespace elem
{
	enum ElemInstance
	{
		idle,
		hover,
		onclick
	};
	enum Direction
	{
		left,
		right,
		top,
		down
	};
}

class Elements
{
public:
	Elements();
	~Elements();
};
class ToolTip
{
private:
	RectangleShape tipboard;
	Texture tipboardTexture;
	Text tipText;
	bool active;

public:
	ToolTip(string tiptext, Color textcolor, Vector2f size, Vector2f position, Texture tiptexture, int textsize, int id);
	ToolTip(string tiptext, Color textcolor, Vector2f size, Texture tiptexture, int textsize, int id);
	ToolTip(string tiptext, Color textcolor, int textsize);
	//Functions
	void Update(const float& time);
	void Draw(RenderTarget &target);
	void ResetTextPosition();
	//Getters
	inline const FloatRect GetBounds()const { return this->tipboard.getGlobalBounds(); }
	inline const bool IsActive()const { return this->active; }
	//Setters
	inline void ShowToolTip(bool arg) { this->active = arg; }
	inline void SetPosition(Vector2f position) { this->tipboard.setPosition(position); this->ResetTextPosition(); }
	inline void SetTipText(string text) { this->tipText.setString(text); }
};
class Button
{
private:
	RectangleShape button;
	Texture texture;
	Text buttontext;

	//Dynamic memory!!!
	ToolTip *tooltip = 0;

	int id;
	float clicktimer = 0;

	bool life = true;
	elem::ElemInstance instance;
public:
	Button(string buttontext,Color textcolor,Vector2f buttsize, Vector2f buttposition, Texture &butttexture, int textsize,int id);
	Button(string buttontext, Color textcolor, Vector2f buttsize, Vector2f buttposition, Texture &butttexture, int textsize, int id, ToolTip * tooltip);
	Button(Vector2f buttsize, Vector2f buttposition, Texture & butttexture, IntRect intrect, int id);
	~Button();
	//Functions
	void Update(Vector2i mouse, const float &time);
	void Draw(RenderTarget &target);
	void SetButtonText(string buttontext, Color color, int size);
	void ResetTextPosition();
	//Button Setters
	inline void ButtonSetSize(Vector2f size) { this->button.setSize(size); }
	inline void ButtonSetInstance(elem::ElemInstance instance) { this->instance = instance; }
	inline void ButtonSetColor(Color color) { this->button.setFillColor(color); }
	inline void ButtonSetPosition(Vector2f position) { this->button.setPosition(position); ResetTextPosition(); }
	inline void ShowToolTip(bool arg) { if(this->tooltip!=nullptr)this->tooltip->ShowToolTip(arg); }
	inline void DeleteButton() { this->life = false; }
	//Text Setters
	inline void TextSetSize(int size) { this->buttontext.setCharacterSize(size); this->ResetTextPosition(); }
	inline void TextSetColor(Color color) { this->buttontext.setFillColor(color); }
	inline void TextSetString(string str) { this->buttontext.setString(str); this->ResetTextPosition(); }
	//Button Getters
	inline const elem::ElemInstance GetButtonInstance()const { return this->instance; }
	inline const int GetButtonId()const { return this->id; }
	inline const FloatRect GetBound()const { return this->button.getGlobalBounds(); }
	inline const bool ToolTipExist()const { return this->tooltip != nullptr; }
	inline const bool IsAlive()const { return this->life; }
};
class Bar
{
private:
	RectangleShape idlebar;
	RectangleShape dynambar;
	Texture idleTexture;
	Texture dynamTexture;
	Text bartext;
	string barname;
	int id;
	int *args[2];
	elem::ElemInstance instance;
public:
	Bar(Vector2f size,Vector2f position,Texture idleTex,Texture dynamTex,int id);
	//Functions
	void Update(Vector2i mouse, const float &time);
	void Draw(RenderTarget & target);
	void SetBarText(string buttontext, Color color, int size);
	void ResetTextPosition();
	//Setters
	inline void SetDynamArgument(int *arg1, int *arg2) { this->args[0] = arg1; this->args[1] = arg2; }
};
class ListBox
{
private:
	RectangleShape board;
	Texture boatdTexture;
	vector <Button*> item;
	float outline;
	float space;

	int startitem;
	int enditem;
	int itemsOnScreen;

	bool autosize;
public:
	ListBox(Vector2f position, float outline, float space, int itemsOnScreen);
	//Functions
	void Update(Vector2i mouse,const float &time);
	void Draw(RenderTarget & target);
	void ScrollItem(int dir);
	void push_back(Button * item);
	void erase(int index);
};
class Label
{
private:
	Text text;
	ToolTip *tooltip = 0;

	int id;
	bool life = true;
	elem::ElemInstance instance;
public:
	Label(string text,Color color, Vector2f position,int charsize,int id);
	Label(string text, Color color, Vector2f position, int charsize, int id,ToolTip *tooltip);
	~Label();
	//Functions
	void Update(Vector2i mouse, const float &time);
	void Draw(RenderTarget &target);
	

	//Setters
	inline void SetText(string newstring) { this->text.setString(newstring); }
};