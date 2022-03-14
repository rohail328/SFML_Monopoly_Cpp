#include "Dice.h"
#include <stdlib.h>
#include <time.h>

Dice::Dice(Vector2f coord):DiceButton(&T["roll"], Vector2f(coord.x + 650.0f, coord.y), Vector2f(200, 90), Color::White, Color(120,200,235), Color::Cyan)
{
	sides = new Texture[6];
	sides[0] = T["dice1"];
	sides[1] = T["dice2"];
	sides[2] = T["dice3"];
	sides[3] = T["dice4"];
	sides[4] = T["dice5"];
	sides[5] = T["dice6"];
	DiceBoxes = new RectangleShape * [2];
	for (int i = 0; i < 2; i++) {
		DiceBoxes[i] = new RectangleShape(Vector2f(90.0f, 90.0f));
		DiceBoxes[i]->setTexture(&(sides[0]));
		DiceBoxes[i]->setOrigin(45.0f, 45.0f);
	}
	DiceBoxes[0]->setPosition(coord);
	DiceBoxes[1]->setPosition(coord.x+100.0f,coord.y);
	name.setFont(font["BoldItalic"]);
	name.setCharacterSize(20);
	name.setPosition(Vector2f(coord.x + 633.0f, coord.y-33.0f));
	name.setString("PLAYER 1");
	name.setOutlineThickness(2.0f);
	name.setOutlineColor(Color::Black);
}

void Dice::Draw(RenderWindow& window)
{
	window.draw(*DiceBoxes[0]);
	window.draw(*DiceBoxes[1]);
	DiceButton.DrawButton(window);
	window.draw(name);
}

int Dice::RollDice(const Player& p)
{
	name.setString(p.getplayername());
	srand(time(NULL));
	int dice1 = 0;
	int dice2 = 0;
	dice1 = rand() % 6 + 1;
	dice2 = rand() % 6 + 1;
	DiceBoxes[0]->setTexture(&(sides[dice1 - 1]));
	DiceBoxes[1]->setTexture(&(sides[dice2 - 1]));
	return dice1+dice2;
}

void Dice::DiceUpdate(Vector2f mousePos)
{
	DiceButton.StatusUpdate(mousePos);
}

bool Dice::getDiceStatus()
{
	if (DiceButton.ButtonClicked() == true) {
		return true;
	}
	return false;
}

void Dice::SetPlayerTurn(const Player& p)
{
	name.setString(p.getplayername());
}

Dice::~Dice()
{
	for (int i = 0; i < 2; i++) {
		delete[] DiceBoxes[i];
	}
	delete[]DiceBoxes;
	DiceBoxes = nullptr;
	delete[]sides;
	sides = nullptr;
}
