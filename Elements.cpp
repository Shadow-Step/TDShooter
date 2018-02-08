#include "Elements.h"



Elements::Elements()
{
}
Elements::~Elements()
{
}
//Button
Button::Button(string buttontext, Color textcolor, Vector2f buttsize, Vector2f buttposition, Texture & butttexture, int textsize, int id)
{
	this->button.setSize(buttsize);
	this->button.setPosition(buttposition);
	this->id = id;
	this->button.setTexture(&butttexture);

	this->buttontext.setFont(Resources::font);
	this->buttontext.setCharacterSize(textsize);
	this->buttontext.setFillColor(textcolor);
	this->buttontext.setString(buttontext);
	this->ResetTextPosition();
}
Button::Button(string buttontext, Color textcolor, Vector2f buttsize, Vector2f buttposition, Texture & butttexture, int textsize, int id, ToolTip * tooltip)
{
	this->button.setSize(buttsize);
	this->button.setPosition(buttposition);
	this->id = id;
	this->button.setTexture(&butttexture);

	this->buttontext.setFont(Resources::font);
	this->buttontext.setCharacterSize(textsize);
	this->buttontext.setFillColor(textcolor);
	this->buttontext.setString(buttontext);
	this->ResetTextPosition();

	this->tooltip = tooltip;
	this->tooltip->SetPosition(Vector2f(button.getPosition().x,button.getPosition().y - 1 - tooltip->GetBounds().height));
}
Button::Button(Vector2f buttsize, Vector2f buttposition, Texture &butttexture, IntRect intrect, int id)
{
	this->button.setSize(buttsize);
	this->button.setPosition(buttposition);
	this->button.setTexture(&butttexture);
	this->button.setTextureRect(intrect);
	this->button.setOutlineThickness(1);
	this->id = id;
}
Button::~Button()
{
	delete tooltip;
}
void Button::Update(Vector2i mouse, const float & time)
{
	clicktimer += time;
	if (!button.getGlobalBounds().contains((Vector2f)mouse))
	{
		this->instance = elem::idle;
	}
	else if (button.getGlobalBounds().contains((Vector2f)mouse))
	{
		if (Mouse::isButtonPressed(Mouse::Left) && clicktimer > 0.1)
		{
			this->instance = elem::onclick;
			clicktimer = 0;
		}
		else
			this->instance = elem::hover;
	}

}
void Button::Draw(RenderTarget & target)
{
	target.draw(this->button);
	target.draw(this->buttontext);
	if (this->tooltip != nullptr && this->tooltip->IsActive())
		this->tooltip->Draw(target);
}
void Button::SetButtonText(string buttontext, Color color, int size)
{
	this->buttontext.setString(buttontext);
	this->buttontext.setFont(Resources::font);
	this->buttontext.setCharacterSize(size);
	this->buttontext.setFillColor(color);
	this->ResetTextPosition();
}
void Button::ResetTextPosition()
{
	this->buttontext.setOrigin(0, 2 + (this->buttontext.getCharacterSize() - this->buttontext.getLocalBounds().height));
	this->buttontext.setPosition(this->button.getPosition().x + (this->button.getGlobalBounds().width - this->buttontext.getGlobalBounds().width) / 2,
		this->button.getPosition().y + (this->button.getGlobalBounds().height - this->buttontext.getGlobalBounds().height) / 2);
}

//Bar
Bar::Bar(Vector2f size, Vector2f position, Texture idleTex, Texture dynamTex, int id)
{
	this->idlebar.setSize(size);
	this->idlebar.setPosition(position);
	this->idlebar.setFillColor(Color::Black);//temp
	this->dynambar.setSize(size);
	this->dynambar.setPosition(position);
	this->dynambar.setFillColor(Color::Red);//temp
	this->id = id;
}
void Bar::Update(Vector2i mouse, const float & time)
{
	if (!idlebar.getGlobalBounds().contains((Vector2f)mouse))
	{
		this->instance = elem::idle;
	}
	else if (idlebar.getGlobalBounds().contains((Vector2f)mouse))
	{
		if (Mouse::isButtonPressed(Mouse::Left))
			this->instance = elem::onclick;
		else
			this->instance = elem::hover;
	}

	this->dynambar.setSize(Vector2f(this->idlebar.getSize().x*((float)*this->args[0] / (float)*this->args[1]), this->idlebar.getSize().y));
	this->bartext.setString(this->barname + to_string(*args[0]) + "/" + to_string(*args[1]));
	this->ResetTextPosition();
}
void Bar::Draw(RenderTarget & target)
{
	target.draw(this->idlebar);
	target.draw(this->dynambar);
	target.draw(this->bartext);
}
void Bar::SetBarText(string buttontext, Color color, int size)
{
	this->bartext.setFont(Resources::font);
	this->bartext.setCharacterSize(size);
	this->bartext.setFillColor(color);
	this->barname = buttontext;
	this->ResetTextPosition();
}
void Bar::ResetTextPosition()
{
	this->bartext.setOrigin(0, 2 + (this->bartext.getCharacterSize() - this->bartext.getLocalBounds().height));
	this->bartext.setPosition(this->idlebar.getPosition().x + (this->idlebar.getGlobalBounds().width - this->bartext.getGlobalBounds().width) / 2,
		this->idlebar.getPosition().y + (this->idlebar.getGlobalBounds().height - this->bartext.getGlobalBounds().height) / 2);
}

//Независимый конструктор
ToolTip::ToolTip(string tiptext,Color textcolor, Vector2f size, Vector2f position, Texture tiptexture,int textsize, int id)
{
	this->tipboard.setSize(size);
	this->tipboard.setPosition(position);

	this->tipText.setFont(Resources::font);
	this->tipText.setCharacterSize(textsize);
	this->tipText.setFillColor(textcolor);
	this->tipText.setString(tiptext);

	this->ResetTextPosition();
}
//Привязанный конструктор
ToolTip::ToolTip(string tiptext, Color textcolor, Vector2f size, Texture tiptexture, int textsize, int id)
{
	this->tipboard.setSize(size);

	this->tipText.setFont(Resources::font);
	this->tipText.setCharacterSize(textsize);
	this->tipText.setFillColor(textcolor);
	this->tipText.setString(tiptext);

	this->ResetTextPosition();
}
ToolTip::ToolTip(string tiptext, Color textcolor, int textsize)
{
	this->tipText.setFont(Resources::font);
	this->tipText.setCharacterSize(textsize);
	this->tipText.setFillColor(textcolor);
	this->tipText.setString(tiptext);

	this->tipboard.setSize(Vector2f(this->tipText.getGlobalBounds().width+6,this->tipText.getGlobalBounds().height+6));
	this->ResetTextPosition();
}
void ToolTip::Draw(RenderTarget & target)
{
	if (this->active == true)
	{
		target.draw(this->tipboard);
		target.draw(this->tipText);
	}
}
void ToolTip::ResetTextPosition()
{
	/*this->tipText.setOrigin(0, 2 + (this->tipText.getCharacterSize() - this->tipText.getLocalBounds().height));*/
	this->tipText.setPosition(this->tipboard.getPosition().x+3,this->tipboard.getPosition().y+3);
}

ListBox::ListBox(Vector2f position,float outline,float space,int itemsOnScreen)
{
	this->board.setPosition(position);
	this->outline = outline;
	this->space = space;
	this->itemsOnScreen = itemsOnScreen;
	this->startitem = this->enditem = 0;
}
void ListBox::Update(Vector2i mouse,const float & time)
{
	int index = 0;
	for (size_t i = startitem; i < enditem; i++)
	{
		this->item[i]->ButtonSetPosition(Vector2f(board.getPosition().x+outline,
			board.getPosition().y + outline + (space*index) + item[i]->GetBound().height*index));
		this->item[i]->Update(mouse,time);
		index++;
	}
}
void ListBox::Draw(RenderTarget & target)
{
	target.draw(this->board);
	for (size_t i = startitem; i < enditem; i++)
	{
		this->item[i]->Draw(target);
	}
}
void ListBox::ScrollItem(int dir)
{
	if (item.size() < itemsOnScreen)
		startitem = 0;
	else
	{
		if (startitem + dir < 0)
			startitem = 0;
		else if (startitem + dir > this->item.size() - itemsOnScreen)
			startitem = this->item.size() - itemsOnScreen;
		else
			startitem += dir;
	}

	if (item.size() < itemsOnScreen)
		enditem = item.size();
	else
	{
		if (enditem + dir < itemsOnScreen)
			enditem = itemsOnScreen;
		else if (enditem + dir > item.size())
			enditem = item.size();
		else
			enditem += dir;
	}
}
void ListBox::push_back(Button * item)
{
	this->item.push_back(item);

	Vector2f boardsize;
	if (autosize)
	{
		boardsize = board.getSize();
		if (boardsize.x < item->GetBound().width)
			boardsize.x = item->GetBound().width + outline * 2;
		boardsize.y = 0;
		for (size_t i = 0; i < this->item.size(); i++)
		{
			boardsize.y += this->item[i]->GetBound().height;
		}
		boardsize.y += (outline * 2) + ((this->item.size() - 1)*space);
		board.setSize(boardsize);
	}
	else
	{
		if (boardsize.x < item->GetBound().width || this->item.size() == 0)
			boardsize.x = item->GetBound().width + outline*2;
		boardsize.y = (item->GetBound().height * itemsOnScreen) + (outline * 2) + space * (itemsOnScreen - 1);
		board.setSize(boardsize);
	}

	if (this->item.size() < itemsOnScreen)
	{
		enditem = this->item.size();
	}
	else
	{
		enditem = itemsOnScreen;
	}
}
void ListBox::erase(int index)
{
	delete this->item[index];
	this->item.erase(this->item.begin() + index);
}

//Label

Label::Label(string text, Color color, Vector2f position, int charsize,int id)
{
	this->text.setFont(Resources::font);
	this->text.setString(text);
	this->text.setCharacterSize(charsize);
	this->text.setFillColor(color);
	this->text.setPosition(position);
	this->id = id;
}
Label::Label(string text, Color color, Vector2f position, int charsize, int id, ToolTip * tooltip)
{
	this->text.setFont(Resources::font);
	this->text.setString(text);
	this->text.setFillColor(color);
	this->text.setPosition(position);
	this->id = id;
	this->tooltip = tooltip;
}
Label::~Label()
{
	delete this->tooltip;
}

void Label::Update(Vector2i mouse, const float & time)
{
	if (!text.getGlobalBounds().contains((Vector2f)mouse))
	{
		this->instance = elem::idle;
	}
	else if (text.getGlobalBounds().contains((Vector2f)mouse))
	{
		if (Mouse::isButtonPressed(Mouse::Left))
			this->instance = elem::onclick;
		else
			this->instance = elem::hover;
	}
}
void Label::Draw(RenderTarget & target)
{
	target.draw(this->text);
}
