#pragma once
#include "Container.h"

enum enumMobTextures
{
	ZOMBIE,
	BUG,
	MOONMAN
};
enum enum_Strings
{
str_LevelUp,
str_HealthPack,
str_AmmoPack,
str_Avoid,
str_PerkPoints,
str_Press_to_take,
str_CuttingBullets,
str_SpeedBooster,
str_dronSpawner,
str_NewGame,
str_Options,
str_Leaders,
str_Exit
};


class Resources
{
private:
	
public:
	Resources();
	virtual ~Resources();

	//Funtions
	static void InitTextures();
	static void InitImages();
	static void InitFont();
	static void InitStrings();
	static void InitPlayerTextures();
	//Static Images
	static vector<Image>mobImage;
	static vector<Image>playerFeetImage;
	static vector<Image>weaponsImage;
	static vector<Image>iconsImage;
	static vector<Image>bulletImage;
	static vector<vector<Image>> playerTImg;
	//Static Textures
	static vector<Texture>bulletTextures;
	static vector<Texture>mobTextures;
	static vector<Texture>playerFeetTextures;
	static vector<Texture>weaponsTextures;
	static vector<Texture>iconsTextures;
	static vector<vector<Texture>> playerTTex;
	static vector<Texture>otherTextures;
	//Static Font
	static Font font;
	static vector <string> strings;
	static vector <string> perksInfo;
	static vector <string> perksNames;
};

