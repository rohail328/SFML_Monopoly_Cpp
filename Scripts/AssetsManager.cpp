#include "AssetsManager.h"
#include<fstream>
#include<iostream>

void AssetsManager::LoadTexture(string name, string FileName) {
	Texture texture;
	if (texture.loadFromFile(FileName)) {
		this->_textures[name] = texture;
	}
}

 void AssetsManager::LoadFont(string name, string FileName) {
	 Font font;
	if (font.loadFromFile(FileName)) {
		this->_fonts[name] = font;
	}
}

 Texture& AssetsManager::GetTexture(string name) {
	return this->_textures[name];
}

Font& AssetsManager::GetFont(string name) {
	return this->_fonts[name];
}

AssetsManager::AssetsManager() {
	int no_of_files;
	string name, fileName;
	ifstream fin;
	fin.open("Assets/BoardTextures.txt");
	fin >> no_of_files;
	for (int i = 0; i < no_of_files; i++) {
		fin >> fileName;
		fin >> name;
		LoadTexture(name, fileName);
	}
	fin.close();
	fin.open("Assets/PlayerTextures.txt");
	fin >> no_of_files;
	for (int i = 0; i < no_of_files; i++) {
		fin >> fileName;
		fin >> name;
		LoadTexture(name, fileName);
	}
	fin.close();
	fin.open("Assets/BackgroundTextures.txt");
	fin >> no_of_files;
	for (int i = 0; i < no_of_files; i++) {
		fin >> fileName;
		fin >> name;
		LoadTexture(name, fileName);
	}
	fin.close();
	fin.open("Assets/BackgroundTextures.txt");
	fin >> no_of_files;
	for (int i = 0; i < no_of_files; i++) {
		fin >> fileName;
		fin >> name;
		LoadTexture(name, fileName);
	}
	fin.close();
	fin.open("Assets/ButtonTextures.txt");
	fin >> no_of_files;
	for (int i = 0; i < no_of_files; i++) {
		fin >> fileName;
		fin >> name;
		LoadTexture(name, fileName);
	}
	fin.close();
	fin.open("Assets/CardTextures.txt");
	fin >> no_of_files;
	for (int i = 0; i < no_of_files; i++) {
		fin >> fileName;
		fin >> name;
		LoadTexture(name, fileName);
	}
	fin.close();
	fin.open("Assets/AnimationTextures.txt");
	fin >> no_of_files;
	for (int i = 0; i < no_of_files; i++) {
		fin >> fileName;
		fin >> name;
		LoadTexture(name, fileName);
	}
	fin.close();
	fin.open("Assets/GameFonts.txt");
	fin >> no_of_files;
	for (int i = 0; i < no_of_files; i++) {
		fin >> fileName;
		fin >> name;
		LoadFont(name, fileName);
	}
	fin.close();


}