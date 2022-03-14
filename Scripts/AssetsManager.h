#pragma once
#include<SFML/Graphics.hpp>
#include<map>
using namespace std;
using namespace sf;
class AssetsManager{
private:
	 map<String, Texture>_textures;
	 map<String, Font>_fonts;
public:
	  AssetsManager();
	 void LoadTexture(string name, string FileName);
	 void LoadFont(string name, string FileName);
	 Texture& GetTexture(string name);//returns the respective textures
	 Font& GetFont(string name);//returns the respective font
};

class TextureManager :public AssetsManager {
public:
	TextureManager() :AssetsManager() {};
	Texture& operator[](string name) {//returns the respective textures
		return GetTexture(name);
	}
};

class FontManager :public AssetsManager {
public:
	FontManager() :AssetsManager() {};
	Font& operator[](string name) {//returns the respective font
		return GetFont(name);
	}
};
