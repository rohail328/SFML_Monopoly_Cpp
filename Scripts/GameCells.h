#pragma once
#include"SFML/Graphics.hpp"
#include"Button.h"
#include"Player.h"
#include"PurchaseableItems.h"
#include <stdlib.h>
#include <time.h>
#include<fstream>
#include<iostream>
using namespace sf;
class OperationManager;
class CommunityChestCards;
class ChanceCards;
class GameCells
{
protected:
	Vector2f coordinates;
	bool status;
	RectangleShape Cell;
	bool cornenercell;
	bool vertical;
	int left;
	int right;
public:
	GameCells(Vector2f cood,bool V,bool C, int i);
	virtual void DrawCell(RenderWindow& window);
	virtual void setActive(Color color) {};
	virtual void updateCell(Vector2f mousePos) {};
	virtual void drawWindow(RenderWindow& window,bool hovered) {};
	virtual bool ButtonStatus() { return false; };
	virtual bool Method(Player& obj) {return false; };
	virtual void setOperationManager(OperationManager*o) {};
	bool reachedCell(Vector2f pos);
	Vector2f getPos() {
		Vector2f cod(coordinates.x, coordinates.y);
		return cod ;
	}
	virtual Vector2f getWindowPos() { return Vector2f(0, 0); };
	virtual Text getPrice() { return Text(); };
	virtual Text getPriceText() { return Text(); };
	virtual int getItemPrice() { return 0; };
	virtual void setowner(Player& obj) {};
	virtual void sellToBank() {};
	bool getStatus() {
		return status;
	};
	virtual string getItemType() { return "-"; };
	virtual bool getMortgageStatus() { return false; };
	virtual void setMortgageStatus(bool m) {};
	virtual string getOwner() { return "-"; };
	char* Convertstring(int a);
	int getPercentage(int A, int b);
	void setStatus(bool st) { status = st; };
	virtual int getCellType() { return 0; };
	virtual int getFilledSlots() { return 0; };
	virtual int getHouses() { return 0; };
	virtual int getHotels() { return 0; };
	virtual int getShops() { return 0; };
	virtual int getWifi() { return 0; };
	virtual int getElectricity() { return 0; };
	virtual int getGas() { return 0; };

	virtual void IncCellType(int a) {  };
	virtual void IncFilledSlots() {  };
	virtual void IncHouses() {  };
	virtual void IncHotels() {  };
	virtual void IncShops() {  };
	virtual void IncWifi() {  };
	virtual void IncElectricity() {  };
	virtual void IncGas() {  };

	virtual void DecCellType(int a) {  };
	virtual void DecFilledSlots() {  };
	virtual void DecHouses() {  };
	virtual void DecHotels() {  };
	virtual void DecShops() {  };
	virtual void DecWifi() {  };
	virtual void DecElectricity() {  };
	virtual void DecGas() {  };
	virtual bool getUpgradeStatus() { return false; };
	virtual int getUpgradeCost() { return 0; };
	virtual void setCellType(int a) {};
	virtual void removeUpgrades() {};
	virtual void setCommunityChestCards(CommunityChestCards**cards) {};
	virtual Player* getItemOwner() { return nullptr; };
	virtual int getItemrent() { return 0; };
	virtual void setChanceCards(ChanceCards**cards) {};
	virtual ofstream& saveGame(ofstream& fout) { return fout; };
	virtual ifstream& loadgame(ifstream& fin) { return fin; };
	virtual ~GameCells() {};
};

class Go :public GameCells {
public:
	Go(Texture* texture, Vector2f cood, bool V, bool C, int i,Texture* windowtexture);
	bool Method(Player& obj);
};

class GoToJail :public GameCells {
public:
	GoToJail(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture);
	bool Method(Player& obj);
};

class Jail :public GameCells {
public:
	Jail(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture);
};

class CommunityChest :public GameCells {
	CommunityChestCards** cards;
	int cardNumber;
public:
	CommunityChest(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture);
	void setCommunityChestCards(CommunityChestCards** cards);
	void DrawCell(RenderWindow& window);
	bool Method(Player& obj);
	~CommunityChest();
};

class Chance :public GameCells {
	ChanceCards** cards;
	int cardNumber;
public:
	Chance(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture);
	void setChanceCards(ChanceCards** cards);
	void DrawCell(RenderWindow& window);
	bool Method(Player& obj);
	~Chance();
};

class Parking :public GameCells {
	OperationManager* Operator;
public:
	Parking(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture);
	bool Method(Player& obj);
	void setOperationManager(OperationManager* o);
	~Parking();
};

class LandTax :public GameCells {
	OperationManager* Operator;
public:
	LandTax(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture);
	bool Method(Player& obj);
	void setOperationManager(OperationManager* o);
	~LandTax();
};

class PropertyTax :public GameCells {
	OperationManager* Operator;
public:
	PropertyTax(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture);
	bool Method(Player& obj);
	void setOperationManager(OperationManager* o);
	~PropertyTax();
};

class Deeds :public GameCells,public PurchaseableItems {
	RectangleShape ownership;
	Button* details;
protected:
	OperationManager* Operator;
	RectangleShape detailWindow;
	bool ManagerOn;
	int* CellType;
	bool Mortgage;
public:
	Deeds(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture, String name, String type, int price,int rent,Font f, int &cellType);
	void DrawCell(RenderWindow& window);
	void setActive(Color color);
	void updateCell(Vector2f mousePos);
	void drawWindow(RenderWindow& window,bool hovered);
	bool ButtonStatus();
	bool Method(Player& obj);
	void setOperationManager(OperationManager*o);
	Vector2f getWindowPos();
	Text getPrice();
	Text getPriceText();
	int getItemPrice();
	void setowner(Player& obj);
	string getItemType();
	bool getMortgageStatus();
	void setMortgageStatus(bool m);
	string getOwner();
	int getCellType();
	void IncCellType(int a);
	void DecCellType(int a);
	void sellToBank();
	void setCellType(int a);
	Player* getItemOwner();
	int getItemrent();
	 ~Deeds();
};
 
class PrivateProperties :public Deeds {
	Text* upgrades;
	int MAX;
	int filled;
	int houses;
	int hotels;
	int shops;
	int wifi;
	int electricity;
	int gas;
	bool upgraded;
	int UpgradeCost;
public:
	PrivateProperties(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture, String name, String type, int price,int rent, Font f, int&cellType);
	void drawWindow(RenderWindow& window, bool hovered);
	int getFilledSlots();
	int getHouses();
	int getHotels();
	int getShops();
	int getWifi();
	int getElectricity();
	int getGas();
	bool getUpgradeStatus();
	//void IncFilledSlots(int a);
	void IncHouses();
	void IncHotels();
	void IncShops();
	void IncWifi();
	void IncElectricity();
	void IncGas();

	//void DecFilledSlots(int a);
	void DecHouses();
	void DecHotels();
	void DecShops();
	void DecWifi();
	void DecElectricity();
	void DecGas();
	int getUpgradeCost();
	void removeUpgrades();
	ofstream& saveGame(ofstream& fout);
	ifstream& loadgame(ifstream& fin);
	~PrivateProperties();
};

class UtilitiesandStations :public Deeds {
public:
	UtilitiesandStations(Texture* texture, Vector2f cood, bool V, bool C, int i, Texture* windowtexture, String name, String type, int price,int rent, Font f, int&cellType);
	ofstream& saveGame(ofstream& fout);
	ifstream& loadgame(ifstream& fin);
};

class OperationManager
{
	GameCells** cells;
	Player** players;
	int nop;
	bool WinOne;
	bool AuctionWin;
	bool ManagerWin;
	bool RentWin;
	bool UpgradeWin;
	bool SellWin;
	bool getOutofJailWin;
	RectangleShape MainWindow;
	RectangleShape AuctionWindow;
	RectangleShape ManagerWindow;
	RectangleShape RentWindow;
	RectangleShape UpgradeWindow;
	RectangleShape Sellwindow;
	RectangleShape getOutOfJailWindow;
	Button* buy;
	Button* auction;
	Button* sell;
	Button* mortgage;
	Button* un_mortgage;
	Button* upgrade;
	Text *PriceText;
	Text *Price;
	Player* ActivePlayer;
	Text* PlayerNameText;
	GameCells* ActiveCell;
	int BidTurn;
	int leftcount;
	int* ActiveAuction;
	int* BidAmounts;
	Text* BidValue;
	Text* BidValueText;
	Text* message;
	Button* add;
	Button* sub;
	Button* bid;
	Button* fold;
	Clock* clk;
	int time;
	bool printMessage;
	bool managerPressed;
	Button** Increment;
	Button** Decrement;
	Text* Values;
	bool upgradeAble;
	int upgradeType;
	int SellingPrice;
	float minimumAuctionPrice;
	Button* purchase;
	Button* skip;
	Button* payFine;
	Button* useJailCard;
	Button* skipTurn;
	int jailCount;
	CommunityChestCards* CMgetoutofJail;
	ChanceCards* CHgetoutofJail;
public:
	OperationManager(Clock*c,GameCells** C, Player** p, int n, Texture* wintex,Texture*lowBalance, Texture* t1, Texture* t2, Texture* t3, Texture* t4, Texture* t5, Texture* t6, Texture* t7, Texture* t8, Texture* t9,Texture*t10,Texture*upgradewin,Texture*t11, Texture* t12, Texture* t13);
	void SetManagerWindow(GameCells&obj);
	bool getManagerstatus();
	void UpdateManager(Vector2f mousePos);
	void DrawManager(RenderWindow& window);
	void setActivePlayer(Player&obj);
	Vector2f getPos();
	void SetWindowone(Player& p, GameCells& cell);
	int IncrementTurn(int previous);
	int SwitchAuctionTurn(int previous);
	void AuctionManager();
	int increment(int a);
	int decrement(int b);
	void setAuctionWindow(GameCells& cell);
	void setRentWindow(GameCells& cell);
	void setUpgradeWindow();
	void UpgradeManger();
	void checkUpgradeAble();
	int UpgradeCase();
	bool checkDoubleRent(GameCells&obj);
	GameCells**&GetCells();
	Player**&GetPlayers();
	int getnop();
	void setSellWindow();
	void SaleManager();
	void Bankrupcy(Player* owner, Player* debted);
	void setPlayers(Player** p, int n);
	void getOutofJailManager();
	void setjailWindow(Player& obj, int& count,bool v);
	bool getJailStatus(int &jailcount);
	void SetCards(CommunityChestCards* CM, ChanceCards* CH);
	~OperationManager();
};


class ChanceCards
{
protected:
	RectangleShape CardBody;
	OperationManager* Operator;
	int amountOnDice;
public:
	ChanceCards() {
		CardBody.setSize(Vector2f(150, 100));
		CardBody.setOrigin(150 / 2, 100 / 2);
		CardBody.setPosition(591, 613);
		Operator = nullptr;
		amountOnDice = 0;
	}
	virtual bool method(Player& obj) { return false; };
	void DrawCard(RenderWindow& window) {
		window.draw(CardBody);
	}
	virtual void setOperator(OperationManager* obj) {
		Operator = obj;
	};
	void amountonDice(int a) {
		amountOnDice = a;
	}
	virtual void setOwner(Player* obj) {};

	virtual ~ChanceCards() {
		Operator = nullptr;
	}
};

class ChanceCard1 :public ChanceCards {
public:
	ChanceCard1(Texture*a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard2 :public ChanceCards {
public:
	ChanceCard2(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard3 :public ChanceCards {
public:
	ChanceCard3(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard4 :public ChanceCards {
public:
	ChanceCard4(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard5 :public ChanceCards {
public:
	ChanceCard5(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard6 :public ChanceCards {
public:
	ChanceCard6(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard7 :public ChanceCards, public PurchaseableItems {
public:
	ChanceCard7(Texture* a,Font f) :ChanceCards(),PurchaseableItems("GET OUT OF JAIL", "COMMUNITY CHEST", 500, NULL, f) {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
	void setOwner(Player* obj);
	~ChanceCard7() {
		ChanceCards::~ChanceCards();
	}
};
//getoutofjailcard

class ChanceCard8 :public ChanceCards {
public:
	ChanceCard8(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard9 :public ChanceCards {
public:
	ChanceCard9(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard10 :public ChanceCards {
public:
	ChanceCard10(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard11 :public ChanceCards {
public:
	ChanceCard11(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard12 :public ChanceCards {
public:
	ChanceCard12(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard13 :public ChanceCards {
public:
	ChanceCard13(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};

class ChanceCard14 :public ChanceCards {
public:
	ChanceCard14(Texture* a) :ChanceCards() {
		CardBody.setTexture(a);
	}
	bool method(Player& obj);
};





class CommunityChestCards {
protected:
	RectangleShape CardBody;
	OperationManager* Operator;
public:
	CommunityChestCards() {
		CardBody.setSize(Vector2f(150, 100));
		CardBody.setOrigin(150 / 2, 100 / 2);
		CardBody.setPosition(350, 327);
		Operator = nullptr;
	}
	virtual void setOperator(OperationManager* obj) {
		Operator = obj;
	};
	virtual bool method(Player& obj) { return false; };
	void DrawCard(RenderWindow& window) {
		window.draw(CardBody);
	}
	virtual void setOwner(Player* obj) {};
	virtual ~CommunityChestCards() {
		Operator = nullptr;
	}
};

class ChestCard1 :public CommunityChestCards {
public:
	ChestCard1(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard2 :public CommunityChestCards {
public:
	ChestCard2(Texture*a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard3 :public CommunityChestCards {
public:
	ChestCard3(Texture*a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard4 :public CommunityChestCards {
public:
	ChestCard4(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard5 :public CommunityChestCards, public PurchaseableItems {
public:
	ChestCard5(Texture* a,Font f) :CommunityChestCards(), PurchaseableItems("GET OUT OF JAIL", "COMMUNITY CHEST", 500, NULL, f) {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
	void setOwner(Player* obj);
	~ChestCard5() {
		CommunityChestCards::~CommunityChestCards();
	}
};
//getoutofjail

class ChestCard6 :public CommunityChestCards {
public:
	ChestCard6(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard7 :public CommunityChestCards {
public:
	ChestCard7(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard8 :public CommunityChestCards {
public:
	ChestCard8(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard9 :public CommunityChestCards {
public:
	ChestCard9(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard10 :public CommunityChestCards {
public:
	ChestCard10(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard11 :public CommunityChestCards {
public:
	ChestCard11(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard12 :public CommunityChestCards {
public:
	ChestCard12(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard13 :public CommunityChestCards {
public:
	ChestCard13(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard14 :public CommunityChestCards {
public:
	ChestCard14(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};

class ChestCard15 :public CommunityChestCards {
public:
	ChestCard15(Texture* a) :CommunityChestCards() {
		CardBody.setTexture(a);
	};
	bool method(Player& obj);
};


