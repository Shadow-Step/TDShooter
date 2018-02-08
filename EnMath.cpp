#include "EnMath.h"

extern int params[3];

namespace times
{
	enum Time
	{
		seconds,
		minutes,
		hours
	};
}

float CountDistance(Vector2f target, Vector2f position)
{
	return sqrt(pow(target.x - position.x, 2)
		+ pow(target.y - position.y, 2));
}

float CountAngle(Vector2f target, Vector2f position)
{
	float angle = 180+(-(atan2f(target.x - position.x, 
		target.y - position.y) * 180 / PI));
	return -angle;
}

Color ChangeColor(Color & color)
{
	static float timer;
	if (Keyboard::isKeyPressed(Keyboard::Numpad9))
	{
		color.r--;
		color.g--;
		color.b--;
	}

	if (Keyboard::isKeyPressed(Keyboard::Numpad1))
		color.r--;
	if (Keyboard::isKeyPressed(Keyboard::Numpad4))
		color.r++;
	if (Keyboard::isKeyPressed(Keyboard::Numpad2))
		color.g--;
	if (Keyboard::isKeyPressed(Keyboard::Numpad5))
		color.g++;
	if (Keyboard::isKeyPressed(Keyboard::Numpad3))
		color.b--;
	if (Keyboard::isKeyPressed(Keyboard::Numpad6))
		color.b++;

	cout << (int)color.r << " " << (int)color.g << " " << (int)color.b << " " << (int)color.a << endl;
	return Color();
}

Vector2f SetOnMidle(FloatRect button, FloatRect text)
{
	Vector2f position;

	position.x = button.left + (button.width - text.width)/2;
	position.y = button.top + (button.height - text.height)/2;


	return position;
}
Vector2f SetOnMidle(FloatRect button, Text text)
{
	Vector2f position;

	position.x = button.left + (button.width - text.getLocalBounds().width) / 2;
	position.y = button.top + (button.height - text.getLocalBounds().height) / 2;


	return position;
}

float CountAngle(Vector2f target, Vector2f position, int randomMode)
{
	float angle = atan2f(target.x - position.x,
		target.y - position.y) * 180 / PI;
	return -(angle+rand()%randomMode-randomMode/2);

}
//Vector2f CountPosByAngle(Vector2f target, Vector2f position, int speed)
//{
//	return Vector2f((CountDistance(target, position)
//		* sin(CountAngle(target, position) * 3.14 / 180))
//		/ (CountDistance(target, position) / speed),
//		((CountDistance(target, position)
//			* cos((CountAngle(target, position)*3.14 / 180))
//			/ ((CountDistance(target, position) / speed)))));
//}

Vector2f CountRandomPos(Vector2f target, Vector2f position, float randomMode)
	{
	Vector2f temp;
	temp.x = (CountDistance(target, position) * sin(CountAngle(target, position,randomMode)*3.14 / 180));
	temp.y = (CountDistance(target, position) * cos(CountAngle(target, position,randomMode)*3.14 / 180));
	return temp;
	}

void InitConfig()
{
	ifstream load;
	string temp;
	string tparam;
	int x = 0;
	load.open("config.txt");
	while (getline(load, temp))
	{
		for (size_t i = 0; i < temp.size(); i++)
		{
			if (temp[i] == '=')
			{
				for (size_t k = i + 1; k < temp.size(); k++, i++)
				{
					if (temp[k] != '/' && temp[k] != ';')
					{
						tparam += temp[k];
					}
					else
					{
						params[x] = atoi(tparam.c_str());
						x++;
						tparam = "";
					}
				}

			}
		}

	}
}

void IncTime(float gametime[], const float & time)
{
	gametime[times::seconds] += time;
	if (gametime[times::seconds] >= 60)
	{
		gametime[times::minutes]++;
		gametime[times::seconds] -= 60;
	}
	if (gametime[times::minutes] >= 60)
	{
		gametime[times::minutes] -= 60;
		gametime[times::hours]++;
	}
}

Vector2f math::Buttpos(Vector2f startposition, int Nbuttons,int rows)
{
	int x = 0;
	int y = 0;
	for (size_t i = 0; i < Nbuttons; i++)
	{
		x++;
		if (x == rows)
		{
			x = 0;
			y++;
		}
	}
	startposition.x += 54 * x;
	startposition.y += 54 * y;
	return startposition;
}
