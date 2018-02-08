#pragma once
#include "Entities.h"
class GUI
{
private:
	vector <RectangleShape> staticBars;
	vector <RectangleShape> dynamicBars;
	vector <Text> textFields;
	
	CircleShape test1;
	Texture testtex1;

	bool onWeapon;
public:
	GUI();
	
	virtual ~GUI();

	//Functions
	void InitGUI(Vector2u winsize);
	void Update(const Player*player,Vector2u winsize,const float &time);
	void Draw(Player * player,RenderTarget &target);
	void UpdateGameTime(const float gametime[]);
};

