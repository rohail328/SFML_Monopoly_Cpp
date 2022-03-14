#pragma once
#include<SFML/Graphics.hpp>
#include<fstream>
#include<iostream>
#include<sstream>
using namespace sf;
using namespace std;
class Player
{
	RectangleShape PlayerBody;
	RectangleShape PlayerToken;
	CircleShape Turn;
	int active;
	float BankBalance;
	String** Status;//solvent,bankrupt,won,in jail
	String currentStatus;
	int Properties;
	Font font;
	Text* displaytext;
	char* name;
	Color PlayerColor;
	int totalAssets;
	bool cmJailCard;
	bool chJailCard;
	float debt;
	float HouseWealth;
	float HotelWealth;
	float ShopWealth;
	float LandWealth;
	float netWorth;
	int STATUS;
public:
	Player(Font f,Color p,Texture*PlayerTexture,Vector2f Playercood,const char*Name,Texture* Tokentexture, Vector2f Tokencood);
	bool MoveToken(float deltatime, float speed, Vector2f pos);//moves the token to the respective position following the path of the board
	void PlayerDraw(RenderWindow& window);//draws the player body on the screen(i.e player details
	void TokenDraw(RenderWindow& window);//draws the token of the player
	Vector2f getPos();//returns the position of the player token
	void setPos(Vector2f pos);
	void resetloop(Vector2f pos);//resets the loop 
	char* IntToChar(int a);//converts integer into char array to be displayed onto the screen
	void setPlayerTurn(bool v);//checks if it is the player's turn, if true sets the circle indicating the turn to green, else sets it to red
	char* getplayername()const;//returns the name of the player
	float getBalance();
	void setBalance(float value);
	void incrementBalance(float value);
	void decrementBalance(float value);
	void setStatus(int a);
	String getStatus();
	void addproperty(float a);
	int getProperties();
	void removeproperty(float a);
	void setchJailCard(bool owned);
	void setcmJailCard(bool owned);
	bool getchJailCard();
	bool getcmJailCard();
	Color getColor();
	void setdebt(float a);
	void addHouse(int a);
	void addHotel(int a);
	void addShop(int a);
	void subHouse(int a);
	void subHotel(int a);
	void subShop(int a);
	float getHouseWealth();
	float getHotelWealth();
	float getShopWealth();
	float getLandWealth();
	float getNetWorth();
	ofstream& savegame(ofstream& fout);
	ifstream& loadgame(ifstream& fin);
	void setNetworth();
	~Player();
};

