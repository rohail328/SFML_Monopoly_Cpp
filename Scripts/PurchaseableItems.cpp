#include "PurchaseableItems.h"

PurchaseableItems::PurchaseableItems(String name, String type, int price, int rent, Font f) :font(f)
{
	OwnerShipStatus = false;
	owner = nullptr;
	ItemName = name;
	ItemType = type;
	ItemPrice = price;
	ItemRent = rent;
	displaytexts = new Text[8];
	for (int i = 0; i < 8; i++) {
		displaytexts[i].setFont(font);
		displaytexts[i].setOutlineThickness(2.0f);
		displaytexts[i].setOutlineColor(Color::Black);
		displaytexts[i].setCharacterSize(15);
	}
	displaytexts[0].setCharacterSize(22);
	displaytexts[1].setCharacterSize(18);

	displaytexts[0].setString(ItemName);
	displaytexts[1].setString(ItemType);
	displaytexts[2].setString("OWNER: ");
	displaytexts[3].setString("BANK");
	displaytexts[4].setString("PRICE: ");
	displaytexts[5].setString(IntToChar(price));
	displaytexts[6].setString("RENT: ");
	displaytexts[7].setString(IntToChar(rent));
	OwnerName = "BANK";
}

char* PurchaseableItems::IntToChar(int a)
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

void PurchaseableItems::setOwner(Player* owner)
{
	if (owner != nullptr) {
		this->owner = owner;
		OwnerName = owner->getplayername();
	}
	if (owner == nullptr) {
		this->owner = nullptr;
		OwnerName = "BANK";
	}
	displaytexts[3].setString(OwnerName);
}

PurchaseableItems::~PurchaseableItems()
{
	owner = nullptr;
	delete[] displaytexts;
	displaytexts = nullptr;
}

