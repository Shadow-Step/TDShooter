#pragma once
#include "Cursor.h"

namespace math
{
	Vector2f Buttpos(Vector2f startposition,int Nbuttons,int rows);
}



void InitConfig();
void IncTime(float gametime[], const float &time);
float CountDistance(Vector2f target, Vector2f position);
float CountAngle(Vector2f target, Vector2f position);
Color ChangeColor(Color &color);
Vector2f SetOnMidle(FloatRect button,FloatRect text);
Vector2f SetOnMidle(FloatRect button, Text text);
float CountAngle(Vector2f target, Vector2f position,int randomMode);
//Vector2f CountPosByAngle(Vector2f target, Vector2f position, int speed);
Vector2f CountRandomPos(Vector2f target, Vector2f position, float randomMode);