#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include"Button.h";
#include"AssetsManager.h"
#include"Player.h"
using namespace std;
using namespace sf;
class Dice
{
	TextureManager T;
	RectangleShape** DiceBoxes;
	Texture* sides;
	Button DiceButton;
	Text name;
	FontManager font;
public:
	Dice(Vector2f coord);
	void Draw(RenderWindow& window);//draws the dices and dice  button onto the screen
	int RollDice(const Player& p);//rolls the dice and gives random results
	void DiceUpdate(Vector2f mousePos);//updates the status of dice button
	bool getDiceStatus();//checks if dice button is pressed
	void SetPlayerTurn(const Player& p);//sets the name of the player to be displayed on the dice button
	~Dice();
};

