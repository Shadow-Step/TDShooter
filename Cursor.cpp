#include "Cursor.h"

Cursor::Cursor(int type)
{
	cursorTexture.loadFromFile("Textures/cursor.png");

	this->cursor.setSize(Vector2f(22, 22));
	this->cursor.setOrigin(9, 9);
	this->cursor.setTexture(&cursorTexture);
	this->cursor.setTextureRect(IntRect(3, 133, 56, 56));
	 
	switch (type)
	{
	case 0:
		this->cursor.setTextureRect(IntRect(3, 133, 56, 56));
		break;
	case 1:
		this->cursor.setTextureRect(IntRect(3, 3, 58, 58));
		break;
	default:
		break;
	}
}

void Cursor::Update(Vector2i mouse)
{
	this->cursor.setPosition((Vector2f)mouse);
}

void Cursor::Draw(RenderTarget & target)
{
	target.draw(this->cursor);
}


Cursor::~Cursor()
{
}
