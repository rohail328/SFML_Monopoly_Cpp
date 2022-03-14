#include "Player.h"
#include<string.h>

Player::Player(Font f, Color p,Texture* PlayerTexture, Vector2f Playercood, const char* Name, Texture* Tokentexture, Vector2f Tokencood):Turn(12.5f,12.5f),font(f),PlayerColor(p)
{
	PlayerBody.setSize(Vector2f(350.0f, 140.0f));
	PlayerBody.setTexture(PlayerTexture);
	PlayerBody.setOrigin(PlayerBody.getSize() / 2.0f);
	PlayerBody.setPosition(Playercood);

	PlayerToken.setSize(Vector2f(59.0f, 59.0f));
	PlayerToken.setTexture(Tokentexture);
	PlayerToken.setOrigin(29.5f, 29.5f);
	PlayerToken.setPosition(Tokencood);

	Turn.setPosition(Playercood.x + 137.0f, Playercood.y +30.0f);
	Turn.setFillColor(Color::Red);
	Turn.setOutlineThickness(2.0f);
	Turn.setOutlineColor(Color::White);
	active = false;
	BankBalance = 400;
	Status = new String* [4];
	Status[0] = new String("SOLVENT");
	Status[1] = new String("BANKRUPT");
	Status[2] = new String("IN JAIL");
	Status[3] = new String("WINNER");
	STATUS = 0;
	Properties = 0;
	name = new char[strlen(Name)];
	int I = 0;
	for (I = 0; Name[I] != '\0'; I++) {
		name[I] = Name[I];
	}
	name[I] = '\0';
	displaytext = new Text[9];
	for (int i = 0; i < 9; i++) {
		displaytext[i].setFont(font);
		displaytext[i].setOutlineThickness(2.0f);
		displaytext[i].setOutlineColor(Color::Black);
	}
	displaytext[0].setString(name);
	displaytext[0].setCharacterSize(25);
	displaytext[0].setPosition(Playercood.x-47.0f,Playercood.y-56.0f);
	for (int i = 1; i < 9; i++) {
		displaytext[i].setCharacterSize(16);
	}
	currentStatus = *Status[0];
	displaytext[1].setString("PKR.");
	displaytext[2].setString("STATUS:");
	displaytext[3].setString("PROPERTIES:");
	displaytext[4].setString(IntToChar(BankBalance));
	displaytext[5].setString(currentStatus);
	displaytext[6].setString(IntToChar(Properties));
	float k = Playercood.y - 17.0f;
	for (int i = 1; i < 4; i++) {
		displaytext[i].setPosition(Playercood.x - 40.0f, k);
		k += 25.0f;
	}
	k= Playercood.y - 17.0f;
	int c = 1;
	for (int i = 4; i < 7; i++) {
		displaytext[i].setPosition(displaytext[c].getPosition().x+displaytext[c].getLocalBounds().width+5.0f, k);
		k += 25.0f;
		c++;
	}
	chJailCard = false;
	cmJailCard = false;
	debt = 0;
	HouseWealth = 0;
	HotelWealth = 0;
	ShopWealth = 0;
	netWorth = 0;
}


bool Player::MoveToken(float deltatime, float speed, Vector2f pos) {
	Vector2f movement(0.0f, 0.0f);
	if (PlayerToken.getPosition().x <= 824.0f && PlayerToken.getPosition().y == 118.0f) {
		if (PlayerToken.getPosition().x <= pos.x) {
			movement.x = speed * deltatime;
		}
	}
	if (PlayerToken.getPosition().x == 825.0f && PlayerToken.getPosition().y <= 824.0f) {
		if (PlayerToken.getPosition().y <= pos.y) {
			movement.y = speed * deltatime;
		}
	}
	if (PlayerToken.getPosition().x >= 118.0f && PlayerToken.getPosition().y == 825.0f) {
		if (PlayerToken.getPosition().x >= pos.x) {
			movement.x = -speed * deltatime;
		}
	}
	if (PlayerToken.getPosition().x == 117.0f && PlayerToken.getPosition().y >= 118.0f) {
		if (PlayerToken.getPosition().y >= pos.y) {
			movement.y = -speed * deltatime;
		}
	}
	PlayerToken.move(movement);
	if (PlayerToken.getPosition() == pos) {
		return true;
	}
	return false;
}

void Player::PlayerDraw(RenderWindow& window) {
	window.draw(PlayerBody);
	window.draw(Turn);
	window.draw(displaytext[0]);
	window.draw(displaytext[1]);
	window.draw(displaytext[2]);
	window.draw(displaytext[3]);
	window.draw(displaytext[4]);
	window.draw(displaytext[5]);
	window.draw(displaytext[6]);
}

void Player::TokenDraw(RenderWindow& window)
{
	window.draw(PlayerToken);
}

Vector2f Player::getPos() {
	return PlayerToken.getPosition();
}

void Player::setPos(Vector2f pos)
{
	PlayerToken.setPosition(pos);
}

void Player::resetloop(Vector2f pos) {
		PlayerToken.setPosition(pos);
}

char* Player::IntToChar(int a){
	int count = 0;
	int number = a;
	while (a > 0) {
		a = a / 10;
		count++;
	}
	char* arr = new char[count + 1];
	int i = 0;
	while (number > 0) {
		arr[i] = (number % 10) + 48;
		number = number / 10;
		i++;
	}
	arr[i] = '\0';
	char* str = new char[strlen(arr)];
	int k = strlen(arr)-1;
	int j = 0;
	for (j=0; arr[j] != '\0'; j++) {
		str[j] = arr[k];
		k--;
	}
	str[j] = '\0';
	return str;
}

void Player::setPlayerTurn(bool v)
{
	if (v == false) {
		Turn.setFillColor(Color::Red);
	}
	if (v == true) {
		Turn.setFillColor(Color::Green);
	}
}

char* Player::getplayername()const
{
	return this->name;
}

float Player::getBalance()
{
	return BankBalance;
}

void Player::setBalance(float value)
{
	BankBalance = value;
	setNetworth();
	displaytext[4].setString(IntToChar(BankBalance));
}

void Player::incrementBalance(float value)
{
	BankBalance += value;
	if (debt <= BankBalance) {
		BankBalance -= debt;
		debt = 0;
	}
	setBalance(BankBalance);
	setNetworth();
}

void Player::decrementBalance(float value)
{
	BankBalance -= value;
	setBalance(BankBalance);
	setNetworth();
}

void Player::setStatus(int a)
{
	if (a >= 0 && a < 4) {
		STATUS = a;
		currentStatus = *Status[a];
		displaytext[5].setString(currentStatus);
		if (currentStatus == "IN JAIL") {
			PlayerToken.setFillColor(Color(186, 181, 181));
		}
		if (currentStatus == "SOLVENT") {
			PlayerToken.setFillColor(Color::White);
			PlayerBody.setFillColor(Color::White);
		}
		if (currentStatus == "BANKRUPT") {
			PlayerToken.setFillColor(Color::Transparent);
			PlayerBody.setFillColor(Color(186, 181, 181));
		}

	}
}

String Player::getStatus()
{
	return currentStatus;
}

void Player::addproperty(float a)
{
	LandWealth += a;
	Properties++;
	displaytext[6].setString(IntToChar(Properties));
	setNetworth();
}

int Player::getProperties()
{
	return Properties;
}

void Player::removeproperty(float a)
{
	LandWealth -= a;
	Properties--;
	displaytext[6].setString(IntToChar(Properties));
	setNetworth();
}

void Player::setchJailCard(bool owned)
{
	chJailCard = owned;
	if (chJailCard == true) {
		netWorth += 500;
	}
	if (chJailCard == false) {
		netWorth -= 500;
	}
	setNetworth();
}

void Player::setcmJailCard(bool owned)
{
	cmJailCard = owned;
	if (cmJailCard == true) {
		netWorth += 500;
	}
	if (cmJailCard == false) {
		netWorth -= 500;
	}
	setNetworth();
}

bool Player::getchJailCard()
{
	return chJailCard;
}

bool Player::getcmJailCard()
{
	return cmJailCard;
}

Color Player::getColor()
{
	return this->PlayerColor;
}

void Player::setdebt(float a)
{
	debt += a;
}

void Player::addHouse(int a)
{
	HouseWealth += a;
	setNetworth();
}

void Player::addHotel(int a)
{
	HotelWealth += a;
	setNetworth();
}

void Player::addShop(int a)
{
	ShopWealth += a;
	setNetworth();
}

void Player::subHouse(int a)
{
	if (HouseWealth - a >= 0) {
		HouseWealth -= a;
		setNetworth();
	}
}

void Player::subHotel(int a)
{
	if (HotelWealth - a >= 0) {
		HotelWealth -= a;
		setNetworth();
	}
}

void Player::subShop(int a)
{
	if (ShopWealth - a >= 0) {
		ShopWealth -= a;
		setNetworth();
	}
}

float Player::getHouseWealth()
{
	return HouseWealth;
}

float Player::getHotelWealth()
{
	return HotelWealth;
}

float Player::getShopWealth()
{
	return ShopWealth;
}

float Player::getLandWealth()
{
	return LandWealth;
}

float Player::getNetWorth()
{
	return netWorth;
}

ofstream& Player::savegame(ofstream& fout)
{
	fout << STATUS << endl;
	fout << netWorth << endl;
	fout << HouseWealth << endl;
	fout << HotelWealth << endl;
	fout << ShopWealth << endl;
	fout << LandWealth << endl;
	fout << BankBalance << endl;
	fout << Properties << endl;
	fout << totalAssets << endl;
	fout <<  chJailCard<< endl;
	fout << cmJailCard << endl;
	fout << debt << endl;
	return fout;
}

ifstream& Player::loadgame(ifstream& fin)
{
	fin >> STATUS;
	fin >> netWorth;
	fin >> HouseWealth;
	fin >> HotelWealth;
	fin >> ShopWealth;
	fin >> LandWealth;
	fin >> BankBalance;
	fin >> Properties;
	fin >> totalAssets;
	fin >> chJailCard;
	fin >> cmJailCard;
	fin >> debt;
	setBalance(BankBalance);
	setNetworth();
	displaytext[6].setString(IntToChar(Properties));
	setStatus(STATUS);
	return fin;
}

void Player::setNetworth()
{
	netWorth = LandWealth + BankBalance + HotelWealth + HouseWealth + ShopWealth;
	if (chJailCard == true) {
		netWorth = netWorth + 500;
	}
	if (cmJailCard == true) {
		netWorth = netWorth + 500;
	}
}

Player::~Player()
{
	for (int i = 0; i < 4; i++) {
		delete Status[i];
	}
	delete Status;
	Status = nullptr;
	delete[] displaytext;
	displaytext = nullptr;
	name = nullptr;
	delete name;
}



