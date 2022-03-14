#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"
#include"AssetsManager.h"
#include<iostream>
using namespace sf;
using namespace std;
class PurchaseableItems
{
protected:
	bool OwnerShipStatus;
	Player* owner;
	String OwnerName;
	String ItemName;
	String ItemType;
	int ItemPrice;
	int ItemRent;
	Text* displaytexts;
	Font font;
public:
	PurchaseableItems(String name, String type, int price,int rent,Font f);
	char* IntToChar(int a);
	void setOwner(Player* owner);
	~PurchaseableItems();
};

