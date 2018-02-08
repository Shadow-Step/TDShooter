#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#define PI 3.1415926535
#define DEBUG1

using namespace sf;
using namespace std;

class Cursor
{
private:
	int type;
	RectangleShape cursor;
	Texture cursorTexture;
public:
	Cursor(int type);
	void Update(Vector2i mouse);
	void Draw(RenderTarget & target);
	~Cursor();
};

