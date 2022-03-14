#include "GameCells.h"
#include<iostream>

GameCells::GameCells(Vector2f cood, bool V, bool C,int i) {
	float WIDTH = 59.0f;
	float HEIGHT = 118.0f;
	status = false;
	cornenercell = C;
	vertical = V;
	right = 0;
	left = 0;
	if (i == 0) {
		right = 1;
	}
	if (i == 1) {
		left = 1;
	}
	if (cornenercell== false) {
		Cell.setSize(Vector2f(WIDTH, HEIGHT));
		if (vertical == true) {
			if (right == 1) {
				Cell.setRotation(90.0f);
			}
			if (left == 1) {
				Cell.setRotation(-90.0f);
			}
		}
	}
	if (cornenercell == true) {
		Cell.setSize(Vector2f(HEIGHT, HEIGHT));
	}
	coordinates = cood;
	Cell.setOrigin(Cell.getSize() / 2.0f);
	Cell.setPosition(coordinates);
	Cell.setOutlineThickness(3.0f);
	Cell.setOutlineColor(Color::Black);
}

void GameCells::DrawCell(RenderWindow& window) {
	window.draw(Cell);
}

bool GameCells::reachedCell(Vector2f pos)
{
	if (Cell.getGlobalBounds().contains(pos) == true) {
		return true;
	}
	return false;
}

char* GameCells::Convertstring(int a)
{
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
	int k = strlen(arr) - 1;
	int j = 0;
	for (j = 0; arr[j] != '\0'; j++) {
		str[j] = arr[k];
		k--;
	}
	str[j] = '\0';
	return str;
}

int GameCells::getPercentage(int A, int b)
{
	int percentage = 0;
	percentage = (b * A) / 100;
	return percentage;
}

Go::Go(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture) :GameCells(cood, V, C,i) {
	Cell.setTexture(texture);
}

bool Go::Method(Player& obj)
{
	obj.incrementBalance(500);
	return false;
}

GoToJail::GoToJail(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture) :GameCells(cood, V, C, i) {
	Cell.setTexture(texture);
}

bool GoToJail::Method(Player& obj)
{
	obj.setPos(Vector2f(824.0f, 118.0f));
	obj.setStatus(2);
	return false;
}

Jail::Jail(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture) :GameCells(cood, V, C,i) {
	Cell.setTexture(texture);
}

CommunityChest::CommunityChest(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture) :GameCells(cood, V, C, i) {
	Cell.setTexture(texture);
	cards = nullptr;
	cardNumber = -1;
}

void CommunityChest::setCommunityChestCards(CommunityChestCards** cards)
{
	this->cards = cards;
	for (int i = 0; i < 15; i++) {
		this->cards[i] = cards[i];
	}
}


void CommunityChest::DrawCell(RenderWindow& window)
{
	GameCells::DrawCell(window);
	if (cardNumber >= 0) {
		cards[cardNumber]->DrawCard(window);
		cout << "drawing\n";
	}
}

bool CommunityChest::Method(Player& obj)
{
	srand(time(NULL));
	cardNumber = rand() % 14 + 0;
	cout << cardNumber << endl;
	bool v=cards[cardNumber]->method(obj);
	if (v == false) {
		//cardNumber = -1;
		return false;
	}
	return true;
}

CommunityChest::~CommunityChest()
{
	cards = nullptr;
}

Chance::Chance(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture) :GameCells(cood, V, C,i) {
	Cell.setTexture(texture);
	cards = nullptr;
	cardNumber = -1;
}

void Chance::setChanceCards(ChanceCards** cards)
{
	this->cards = cards;
	for (int i = 0; i < 14; i++) {
		this->cards[i] = cards[i];
	}

}

void Chance::DrawCell(RenderWindow& window)
{
	GameCells::DrawCell(window);
	if (cardNumber >= 0) {
		cards[cardNumber]->DrawCard(window);
		cout << "drawing\n";
	}

}

bool Chance::Method(Player& obj)
{
	srand(time(NULL));
	cardNumber = rand() % 14 + 0;
	cout << cardNumber << endl;
	bool v = cards[cardNumber]->method(obj);
	if (v == false) {
		//cardNumber = -1;
		return false;
	}
	return true;
}

Chance::~Chance()
{
	cards = nullptr;
}

Parking::Parking(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture) :GameCells(cood, V, C,i) {
	Cell.setTexture(texture);
	Operator = nullptr;
}

bool Parking::Method(Player& obj)
{
	if (obj.getBalance() >= 10) {
		obj.decrementBalance(10);
	}
	if (obj.getBalance() < 10) {
		Operator->setRentWindow(*this);
		if (obj.getNetWorth() < 10) {
			obj.setStatus(1);
			Operator->Bankrupcy(nullptr, &obj);
		}
		if (obj.getNetWorth() > 10) {
			obj.setdebt(10);
		}
	}

	return false;
}

void Parking::setOperationManager(OperationManager* o)
{
	Operator = o;
}

Parking::~Parking()
{
	Operator = nullptr;
}

LandTax::LandTax(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture) :GameCells(cood, V, C,i) {
	Cell.setTexture(texture);
	Operator = nullptr;
}

bool LandTax::Method(Player& obj)
{
	float A = getPercentage(obj.getLandWealth(), 20);
	if (obj.getBalance() >= A) {
		obj.decrementBalance(A);
	}
	if (obj.getBalance() < A) {
		Operator->setRentWindow(*this);
		if (obj.getNetWorth() < A) {
			obj.setStatus(1);
			Operator->Bankrupcy(nullptr, &obj);
		}
		if (obj.getNetWorth() >= A) {
			obj.setdebt(10);
		}
	}

	return false;
}

void LandTax::setOperationManager(OperationManager* o)
{
	Operator = o;
}

LandTax::~LandTax()
{
	Operator = nullptr;
}

PropertyTax::PropertyTax(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture) :GameCells(cood, V, C,i) {
	Cell.setTexture(texture);
	Operator = nullptr;
}

bool PropertyTax::Method(Player& obj)
{
	float A = getPercentage(obj.getLandWealth(), 10) + getPercentage(obj.getHouseWealth(), 20) + getPercentage(obj.getHotelWealth(), 30) + getPercentage(obj.getShopWealth(), 30);
	if (obj.getBalance() >= A) {
		obj.decrementBalance(A);
	}
	if (obj.getBalance() < A) {
		Operator->setRentWindow(*this);
		if (obj.getNetWorth() < A) {
			obj.setStatus(1);
			Operator->Bankrupcy(nullptr, &obj);
		}
		if (obj.getNetWorth() >= A) {
			obj.setdebt(10);
		}
	}

	return false;
}

void PropertyTax::setOperationManager(OperationManager* o)
{
	Operator = o;
}

PropertyTax::~PropertyTax()
{
	Operator = nullptr;
}

Deeds::Deeds(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture, String name, String type, int price,int rent, Font f,int&cellType) :GameCells(cood, V, C,i),PurchaseableItems(name,type,price,rent,f) {
	float width = 65.0f;
	float height = 25.0f;
	Cell.setTexture(texture);
	detailWindow.setSize(Vector2f(170.0f, 210.0f));
	detailWindow.setPosition(coordinates);
	detailWindow.setTexture(windowtexture);
	details = nullptr;
	ownership.setSize(Vector2f(width, height));
	ownership.setOrigin(ownership.getSize() / 2.0f);
	if (vertical == true) {
		ownership.setRotation(90.0f);
		if (right==1) {
			ownership.setPosition(Cell.getPosition().x - 73.0f, Cell.getPosition().y);
		}
		if (left == 1) {
			ownership.setPosition(Cell.getPosition().x + 73.0f, Cell.getPosition().y);
		}
		details = new Button(nullptr, coordinates, Vector2f(118.0f, 59.0f), Color::Transparent, Color(186, 181, 181, 100), Color(186, 181, 181, 100));
	}
	if (vertical == false) {
		if (Cell.getPosition().y == 118.0f) {
			ownership.setPosition(Cell.getPosition().x, Cell.getPosition().y + 73.0f);
		}
		if (Cell.getPosition().y == 824.0f) {
			ownership.setPosition(Cell.getPosition().x, Cell.getPosition().y - 73.0f);
			detailWindow.setPosition(coordinates.x, coordinates.y - 210.0f);
		}
		details = new Button(nullptr, coordinates, Vector2f(59.0f, 118.0f), Color::Transparent, Color(186, 181, 181, 100), Color(186, 181, 181, 100));
	}
	ownership.setFillColor(Color::Transparent);
	Operator = nullptr;
	ManagerOn = false;
	Mortgage = false;
	CellType = &cellType;
}

void Deeds::DrawCell(RenderWindow& window) {
	GameCells::DrawCell(window);
	details->DrawButton(window);
	window.draw(ownership);
}

void Deeds::setActive(Color color) {
	status = true;
	Cell.setOutlineColor(color);
	ownership.setFillColor(color);
}

void Deeds::updateCell(Vector2f mousePos)
{
	details->StatusUpdate(mousePos);
	ManagerOn = Operator->getManagerstatus();
}

void Deeds::drawWindow(RenderWindow& window, bool hovered)
{
	displaytexts[0].setPosition(detailWindow.getPosition().x - 5, detailWindow.getPosition().y - 10);
	displaytexts[1].setPosition(detailWindow.getPosition().x + 35, detailWindow.getPosition().y + 23);
	displaytexts[2].setPosition(detailWindow.getPosition().x + 15, detailWindow.getPosition().y + 70);
	displaytexts[3].setPosition(detailWindow.getPosition().x + 80, detailWindow.getPosition().y + 70);
	displaytexts[4].setPosition(detailWindow.getPosition().x + 15, detailWindow.getPosition().y + 90);
	displaytexts[5].setPosition(detailWindow.getPosition().x + 80, detailWindow.getPosition().y + 90);
	displaytexts[6].setPosition(detailWindow.getPosition().x + 15, detailWindow.getPosition().y + 110);
	displaytexts[7].setPosition(detailWindow.getPosition().x + 80, detailWindow.getPosition().y + 110);
	if (hovered == true &&ManagerOn==false) {
		window.draw(detailWindow);
		window.draw(displaytexts[0]);
		window.draw(displaytexts[1]);
		window.draw(displaytexts[2]);
		window.draw(displaytexts[3]);
		window.draw(displaytexts[4]);
		window.draw(displaytexts[5]);
		window.draw(displaytexts[6]);
		window.draw(displaytexts[7]);
	}
}

bool Deeds::ButtonStatus()
{
	if (Operator->getManagerstatus() == false) {
		if (!details->ButtonClicked()) {
		   return details->ButtonHovered();
	    }
		if (details->ButtonClicked()) {
			Operator->SetManagerWindow(*this);
			ManagerOn = true;
		}
	}
	return false;
}

bool Deeds::Method(Player& obj)
{
	if (this->OwnerName=="BANK") {
		Operator->SetWindowone(obj, *this);
	}
	else
	{
		if (Mortgage == false) {
			if (Operator->checkDoubleRent(*this) == true) {
				if (this->OwnerName != obj.getplayername()) {
					if (obj.getBalance() >= this->ItemRent * 2) {
						obj.decrementBalance(this->ItemRent * 2);
						owner->incrementBalance(this->ItemRent * 2);
					}
					if (obj.getBalance() < this->ItemRent * 2) {
						Operator->setRentWindow(*this);
						if (obj.getNetWorth() < this->ItemRent*2) {
							obj.setStatus(1);
							Operator->Bankrupcy(owner, &obj);
						}
						if (obj.getNetWorth() >= this->ItemRent * 2) {
							owner->incrementBalance(this->ItemRent * 2);
							obj.setdebt(ItemRent * 2);
						}
					}
				}
			}
			else {
				if (this->OwnerName != obj.getplayername()) {
					if (obj.getBalance() >= this->ItemRent) {
						obj.decrementBalance(this->ItemRent);
						owner->incrementBalance(this->ItemRent);
					}
					if (obj.getBalance() < this->ItemRent) {
						Operator->setRentWindow(*this);
						if (obj.getNetWorth() < this->ItemRent ) {
							obj.setStatus(1);
							Operator->Bankrupcy(owner, &obj);
						}
						if (obj.getNetWorth() >= this->ItemRent) {
							obj.setdebt(ItemRent * 2);
							owner->incrementBalance(this->ItemRent * 2);
						}
					}
				}
			}
		}
	}
	return false;
}

void Deeds::setOperationManager(OperationManager*o)
{
	Operator = o;
}

Vector2f Deeds::getWindowPos()
{
	return detailWindow.getPosition();
}

Text Deeds::getPrice()
{
	return displaytexts[5];
}

Text Deeds::getPriceText()
{
	return displaytexts[4];
}

int Deeds::getItemPrice()
{
	return ItemPrice;
}

void Deeds::setowner(Player& obj)
{
	this->owner = nullptr;
	this->setOwner(&obj);
	displaytexts[3].setString(obj.getplayername());
	OwnerName = obj.getplayername();
	setActive(obj.getColor());
}

string Deeds::getItemType()
{
	return ItemType;
}

bool Deeds::getMortgageStatus()
{
	return Mortgage;
}

void Deeds::setMortgageStatus(bool m)
{
	Mortgage = m;
	if (Mortgage == true) {
		Cell.setFillColor(Color(186, 181, 181));
	}
	if (Mortgage == false) {
		Cell.setFillColor(Color::White);
		if (owner != nullptr) {
			ownership.setFillColor(this->owner->getColor());
			Cell.setOutlineColor(this->owner->getColor());
		}
		else
		{
			Cell.setOutlineColor(Color::Black);
			ownership.setFillColor(Color::Transparent);
		}
	}
}

string Deeds::getOwner()
{
	return this->OwnerName;
}

int Deeds::getCellType()
{
	return *CellType;
}

void Deeds::IncCellType(int a)
{
	if (*CellType + a <= 20) {
		*CellType += a;
	}
}

void Deeds::DecCellType(int a)
{
	if (*CellType - a >= 0) {
		*CellType -= a;
	}
}

void Deeds::sellToBank()
{
	this->setOwner(nullptr);
	status = false;
	Cell.setOutlineColor(Color::Black);
	ownership.setFillColor(Color::Transparent);
	
}

void Deeds::setCellType(int a)
{
	*CellType = 0;
}

Player* Deeds::getItemOwner()
{
	return owner;
}

int Deeds::getItemrent()
{
	return ItemRent;
}

Deeds::~Deeds()
{
	delete details;
	details = nullptr;
	Operator = nullptr;
	CellType = nullptr;
}


PrivateProperties::PrivateProperties(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture, String name, String type, int price,int rent,Font f, int&cellType) :Deeds(texture,cood, V, C,i,windowtexture,name,type,price,rent,f,cellType) {
	Cell.setTexture(texture);
	upgrades = new Text[6];
	for (int i = 0; i < 6; i++) {
		upgrades[i].setFont(font);
		upgrades[i].setOutlineThickness(2.0f);
		upgrades[i].setOutlineColor(Color::Black);
		upgrades[i].setCharacterSize(15);
	}
	upgrades[0].setString("HOUSES:");
	upgrades[1].setString("0");
	upgrades[2].setString("HOTELS:");
	upgrades[3].setString("0");
	upgrades[4].setString("SHOPS:");
	upgrades[5].setString("0");
	MAX = 20;
	filled = 0;
	houses = 0;
	hotels = 0;
	shops = 0;
	wifi = 0;
	electricity = 0;
	gas = 0;
	upgraded = false;
	UpgradeCost = 0;
}

void PrivateProperties::drawWindow(RenderWindow& window, bool hovered)
{
	Deeds::drawWindow(window, hovered);
	upgrades[0].setPosition(detailWindow.getPosition().x + 15, detailWindow.getPosition().y + 130);
	upgrades[1].setPosition(detailWindow.getPosition().x + 80, detailWindow.getPosition().y + 130);
	upgrades[2].setPosition(detailWindow.getPosition().x + 15, detailWindow.getPosition().y + 150);
	upgrades[3].setPosition(detailWindow.getPosition().x + 80, detailWindow.getPosition().y + 150);
	upgrades[4].setPosition(detailWindow.getPosition().x + 15, detailWindow.getPosition().y + 170);
	upgrades[5].setPosition(detailWindow.getPosition().x + 80, detailWindow.getPosition().y + 170);

	if (hovered == true &&ManagerOn==false) {
		window.draw(upgrades[0]);
		window.draw(upgrades[1]);
		window.draw(upgrades[2]);
		window.draw(upgrades[3]);
		window.draw(upgrades[4]);
		window.draw(upgrades[5]);

	}
}

int PrivateProperties::getFilledSlots()
{
	return filled;
}

int PrivateProperties::getHouses()
{
	return houses;
}

int PrivateProperties::getHotels()
{
	return hotels;
}

int PrivateProperties::getShops()
{
	return shops;
}

int PrivateProperties::getWifi()
{
	return wifi;
}

int PrivateProperties::getElectricity()
{
	return electricity;
}

int PrivateProperties::getGas()
{
	return gas;
}

bool PrivateProperties::getUpgradeStatus()
{
	return upgraded;
}

void PrivateProperties::IncHouses()
{
	if (filled + 1 <= MAX) {
		houses += 1;
		filled += 1;
		ItemRent += getPercentage(ItemRent, 30);
		displaytexts[7].setString(Convertstring(ItemRent));
		upgrades[1].setString(Convertstring(houses));
		UpgradeCost += 100;
	}
	if (filled > 0) {
		upgraded = true;
	}
}

void PrivateProperties::IncHotels()
{
	if (filled + 10 <= MAX) {
		hotels += 1;
		filled += 10;
		ItemRent += getPercentage(ItemRent, 80);
		displaytexts[7].setString(Convertstring(ItemRent));
		upgrades[3].setString(Convertstring(hotels));
		UpgradeCost += 1000;
	}
	if (filled > 0) {
		upgraded = true;
	}

}

void PrivateProperties::IncShops()
{
	if (filled + 3 <= MAX) {
		shops += 1;
		filled += 3;
		ItemRent += getPercentage(ItemRent, 60);
		displaytexts[7].setString(Convertstring(ItemRent));
		upgrades[5].setString(Convertstring(shops));
		UpgradeCost += 300;
	}
	if (filled > 0) {
		upgraded = true;
	}

}

void PrivateProperties::IncWifi()
{
	if (wifi + 1 <= filled) {
		wifi += 1;
		ItemRent += getPercentage(ItemRent, 10);
		displaytexts[7].setString(Convertstring(ItemRent));
		UpgradeCost += 30;
	}
	if (filled > 0) {
		upgraded = true;
	}

}

void PrivateProperties::IncElectricity()
{
	if (electricity + 1 <= filled) {
		electricity += 1;
		ItemRent += getPercentage(ItemRent, 20);
		displaytexts[7].setString(Convertstring(ItemRent));
		UpgradeCost += 50;
	}
	if (filled > 0) {
		upgraded = true;
	}

}

void PrivateProperties::IncGas()
{
	if (gas + 1 <= filled) {
		gas += 1;
		ItemRent += getPercentage(ItemRent, 20);
		displaytexts[7].setString(Convertstring(ItemRent));
		UpgradeCost += 50;
	}
	if (filled > 0) {
		upgraded = true;
	}

}

void PrivateProperties::DecHouses()
{
	if (filled - 1 >= 0) {
		houses -= 1;
		filled -= 1;
		ItemRent -= getPercentage(ItemRent, 30);
		displaytexts[7].setString(Convertstring(ItemRent));
		upgrades[1].setString(Convertstring(houses));
		UpgradeCost -= 50;
	}
	if (filled == 0) {
		upgraded = false;
	}


}

void PrivateProperties::DecHotels()
{
	if (filled - 10 >= 0) {
		hotels -= 1;
		filled -= 10;
		ItemRent -= getPercentage(ItemRent, 80);
		displaytexts[7].setString(Convertstring(ItemRent));
		upgrades[3].setString(Convertstring(hotels));
		UpgradeCost -= 1000;
	}
	if (filled == 0) {
		upgraded = false;
	}

}

void PrivateProperties::DecShops()
{
	if (filled - 3 >= 0) {
		shops -= 1;
		filled -= 3;
		ItemRent -= getPercentage(ItemRent, 60);
		displaytexts[7].setString(Convertstring(ItemRent));
		upgrades[5].setString(Convertstring(houses));
		UpgradeCost -= 300;
	}
	if (filled == 0) {
		upgraded = false;
	}

}

void PrivateProperties::DecWifi()
{
	if (wifi - 1 >= 0 ) {
		wifi -= 1;
		ItemRent -= getPercentage(ItemRent, 10);
		displaytexts[7].setString(Convertstring(ItemRent));
		UpgradeCost -= 30;
	}
	if (filled == 0) {
		upgraded = false;
	}

}

void PrivateProperties::DecElectricity()
{
	if (electricity - 1 >= 0) {
		electricity -= 1;
		ItemRent -= getPercentage(ItemRent, 20);
		displaytexts[7].setString(Convertstring(ItemRent));
		UpgradeCost -= 50;
	}
	if (filled == 0) {
		upgraded = false;
	}

}

void PrivateProperties::DecGas()
{
	if (gas - 1 >= 0) {
		gas -= 1;
		ItemRent -= getPercentage(ItemRent, 20);
		displaytexts[7].setString(Convertstring(ItemRent));
		UpgradeCost -= 50;
	}
	if (filled == 0) {
		upgraded = false;
	}

}

int PrivateProperties::getUpgradeCost()
{
	return UpgradeCost;
}

void PrivateProperties::removeUpgrades()
{
	UpgradeCost = 0;
	houses = 0;
	hotels = 0;
	shops = 0;
	wifi = 0;
	electricity = 0;
	gas = 0;
	setCellType(0);
}

ofstream& PrivateProperties::saveGame(ofstream& fout)
{
	fout << status << endl;
	fout << Mortgage << endl;
	fout << *CellType << endl;
	if (owner != nullptr) {
		fout << owner->getplayername()<<endl;
	}
	if (owner == nullptr) {
		fout << "BANK" << endl;
	}
	fout << UpgradeCost << endl;
	fout << houses << endl;
	fout << hotels << endl;
	fout << shops << endl;
	fout << wifi << endl;
	fout << electricity << endl;
	fout << gas << endl;
	fout << upgraded << endl;
	return fout;
}

ifstream& PrivateProperties::loadgame(ifstream& fin)
{
	string str;
	char v;
	fin >> status;
	fin >> Mortgage;
	fin >> *CellType;
	fin >> str;
	if (str == "PLAYER") {
		fin >> v;
		str = str +' '+ v;
	}
	OwnerName = str;
	fin >> UpgradeCost;
	fin >> houses;
	fin >> hotels;
	fin >> shops;
	fin >> wifi;
	fin >> electricity;
	fin >> gas;
	fin >> upgraded;
	upgrades[1].setString(IntToChar(houses));
	upgrades[3].setString(IntToChar(hotels));
	upgrades[5].setString(IntToChar(shops));
	displaytexts[3].setString(OwnerName);
	return fin;
}

PrivateProperties::~PrivateProperties()
{
	delete[] upgrades;
	upgrades = nullptr;
}

UtilitiesandStations::UtilitiesandStations(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture, String name, String type, int price,int rent, Font f, int &cellType) : Deeds(texture, cood, V, C,i,windowtexture, name, type, price,rent,f,cellType) {
	Cell.setTexture(texture);
}

ofstream& UtilitiesandStations::saveGame(ofstream& fout)
{
	fout << status << endl;
	fout << Mortgage << endl;
	fout << *CellType << endl;
	if (owner != nullptr) {
		fout << owner->getplayername() << endl;
	}
	if (owner == nullptr) {
		fout << "BANK" << endl;
	}
	return fout;
}

ifstream& UtilitiesandStations::loadgame(ifstream& fin) {
	string str;
	char v;
	fin >> status;
	fin >> Mortgage;
	fin >> *CellType;
	fin >> str;
	if (str == "PLAYER") {
		fin >> v;
		str = str + ' ' + v;
	}
	OwnerName = str;
	return fin;

}
