#include "Resources.h"

Font Resources::font;

vector <string> Resources::strings;
vector <string> Resources::perksInfo;
vector <string> Resources::perksNames;

vector<Image>Resources::mobImage;
vector<Texture>Resources::mobTextures;

vector<vector<Image>>Resources::playerTImg;
vector<vector<Texture>> Resources::playerTTex;
vector<Image>Resources::playerFeetImage;
vector<Texture>Resources::playerFeetTextures;

vector<Texture>Resources::bulletTextures;
vector<Image>Resources::bulletImage;

vector<Texture>Resources::weaponsTextures;
vector<Texture>Resources::iconsTextures;

vector<Texture>Resources::otherTextures;

Resources::Resources()
{
}


Resources::~Resources()
{
}

void Resources::InitTextures()
{
	Texture temp;
	
	//Enemy Textures
	temp.loadFromImage(Resources::mobImage[ZOMBIE]); //Zombie
	Resources::mobTextures.push_back(temp);

	temp.loadFromImage(Resources::mobImage[BUG]); //Bug and MoonMan
	Resources::mobTextures.push_back(temp);

	temp.loadFromImage(Resources::mobImage[2]); //Bug and MoonMan
	Resources::mobTextures.push_back(temp);

	//Bullets Texture
	temp.loadFromFile("Textures/Bullets/bullet.png");//Bullet
	Resources::bulletTextures.push_back(temp);
	
	temp.loadFromFile("Textures/Bullets/explosion.png");//Bullet
	Resources::bulletTextures.push_back(temp);

	temp.loadFromFile("Textures/Bullets/bullet_02.png");//Bullet
	Resources::bulletTextures.push_back(temp);

	//Weapons Texture
	temp.loadFromFile("Textures/Weapons/weapons.png");
	Resources::weaponsTextures.push_back(temp);

	temp.loadFromFile("Textures/Weapons/weapons.png");
	Resources::weaponsTextures.push_back(temp);

	//OtherTextures
	temp.loadFromFile("Textures/Background/back_01.png");
	Resources::otherTextures.push_back(temp);
}

void Resources::InitPlayerTextures()
{
	string tempstr;
	ifstream ifstr;
	Image tempImg;
	Texture tempTex;

	Resources::playerTImg.resize(4);
	Resources::playerTTex.resize(4);
	//Images
	ifstr.open("Textures/Player/handgun/strings.txt");
	while (getline(ifstr, tempstr))
	{
		tempImg.loadFromFile(tempstr);
		tempImg.createMaskFromColor(Color::White);
		Resources::playerTImg[0].push_back(tempImg);
	}
	ifstr.close();
	for (size_t i = 0; i < Resources::playerTImg[0].size(); i++)
	{
		tempTex.loadFromImage(Resources::playerTImg[0][i]);
		Resources::playerTTex[0].push_back(tempTex);
	}

	ifstr.open("Textures/Player/rifle/strings.txt");
	while (getline(ifstr, tempstr))
	{
		tempImg.loadFromFile(tempstr);
		tempImg.createMaskFromColor(Color::White);
		Resources::playerTImg[1].push_back(tempImg);
	}
	ifstr.close();
	for (size_t i = 0; i < Resources::playerTImg[1].size(); i++)
	{
		tempTex.loadFromImage(Resources::playerTImg[1][i]);
		Resources::playerTTex[1].push_back(tempTex);
	}

	ifstr.open("Textures/Player/shotgun/strings.txt");
	while (getline(ifstr, tempstr))
	{
		tempImg.loadFromFile(tempstr);
		tempImg.createMaskFromColor(Color::White);
		Resources::playerTImg[2].push_back(tempImg);
	}
	ifstr.close();
	for (size_t i = 0; i < Resources::playerTImg[2].size(); i++)
	{
		tempTex.loadFromImage(Resources::playerTImg[2][i]);
		Resources::playerTTex[2].push_back(tempTex);
	}

	ifstr.open("Textures/Player/knife/strings.txt");
	while (getline(ifstr, tempstr))
	{
		tempImg.loadFromFile(tempstr);
		tempImg.createMaskFromColor(Color::White);
		Resources::playerTImg[3].push_back(tempImg);
	}
	ifstr.close();
	for (size_t i = 0; i < Resources::playerTImg[3].size(); i++)
	{
		tempTex.loadFromImage(Resources::playerTImg[3][i]);
		Resources::playerTTex[3].push_back(tempTex);
	}


	ifstr.open("Textures/Player/feet/strings.txt");
	while (getline(ifstr, tempstr))
	{
		tempImg.loadFromFile(tempstr);
		tempImg.createMaskFromColor(Color::White);
		Resources::playerFeetImage.push_back(tempImg);
	}
	ifstr.close();
	for (size_t i = 0; i < Resources::playerFeetImage.size(); i++)
	{
		tempTex.loadFromImage(Resources::playerFeetImage[i]);
		Resources::playerFeetTextures.push_back(tempTex);
	}
}

void Resources::InitFont()
{
	font.loadFromFile("Font/ben_krush.ttf");
}

void Resources::InitStrings()
{
	ifstream ifstr;

	string temp;
	Resources::perksNames.resize(10);
	Resources::perksInfo.resize(10);

	int i = 0;
	int k = 0;
	

	ifstr.open("Localisation/RUS/perk_strings.txt");
	while (getline(ifstr, temp))
	{
		if (temp.size() > 0 && temp.size() < 15)
		{
			Resources::perksNames[k] = temp;
			k++;
		}
		if (temp.size() > 30)
		{
			temp += "\n\n";
			Resources::perksInfo[i] += temp;
		}
		else if (temp.size() == 0)
			i++;
	}
	ifstr.close();

	while (Resources::perksInfo[Resources::perksInfo.size() - 1] == "")
	{
		Resources::perksInfo.pop_back();
	}
	while (Resources::perksNames[Resources::perksNames.size() - 1] == "")
	{
		Resources::perksNames.pop_back();
	}

	i = 0;
	ifstr.open("Localisation/RUS/strings.txt");
	while (getline(ifstr, temp))
	{
		if (temp.size() > 0);
		{
			Resources::strings.resize(1 + i);
			Resources::strings[i] += temp;
			i++;
		}
	}
	ifstr.close();

}

void Resources::InitImages()
{
	string tempstr;
	ifstream ifstr;

	Image temp;
	
	//Enemy images
	temp.loadFromFile("Textures/Enemy/enemy01.png"); //Zombie
	temp.createMaskFromColor(Color::White);
	Resources::mobImage.push_back(temp);

	temp.loadFromFile("Textures/Enemy/enemy02.png"); //Bug and MoonMan
	temp.createMaskFromColor(Color::White);
	Resources::mobImage.push_back(temp);

	temp.loadFromFile("Textures/Enemy/dron.png"); //Bug and MoonMan
	temp.createMaskFromColor(Color::White);
	Resources::mobImage.push_back(temp);

}

