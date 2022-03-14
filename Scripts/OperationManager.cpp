#include"GameCells.h"

OperationManager::OperationManager(Clock* c,GameCells** C, Player** p, int n, Texture* wintex, Texture* lowBalance, Texture* t1, Texture* t2, Texture* t3, Texture* t4, Texture* t5, Texture* t6, Texture* t7, Texture* t8, Texture* t9, Texture* t10, Texture* upgradewin, Texture* t11, Texture* t12, Texture* t13)
{
	clk = c;
	time = 0;
	cells = C;
	for (int i = 0; i < 40; i++) {
		cells[i] = C[i];
	}
	nop = n;
	players = p;
	for (int i = 0; i < nop; i++) {
		players[i] = p[i];
	}
	WinOne = false;
	AuctionWin = false;
	ManagerWin = false;
	RentWin = false;
	UpgradeWin = false;
	getOutofJailWin = false;
	MainWindow.setSize(Vector2f(170.0f, 210.0f));
	MainWindow.setTexture(wintex);
	AuctionWindow.setSize(Vector2f(170.0f, 210.0f));
	AuctionWindow.setTexture(wintex);
	ManagerWindow.setSize(Vector2f(170.0f, 210.0f));
	ManagerWindow.setTexture(wintex);
	RentWindow.setSize(Vector2f(170.0f, 100.0f));
	RentWindow.setTexture(lowBalance);
	UpgradeWindow.setSize(Vector2f(200.0f, 300.0f));
	UpgradeWindow.setTexture(upgradewin);
	Sellwindow.setSize(Vector2f(170.0f, 210.0f));
	Sellwindow.setTexture(wintex);
	getOutOfJailWindow.setSize(Vector2f(170.0f, 210.0f));
	getOutOfJailWindow.setTexture(wintex);
	Vector2f a(118, 118), b(95, 44);
	buy = new Button(t1, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	auction = new Button(t2, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	sell = new Button(t3, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	upgrade = new Button(t4, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	mortgage = new Button(t5, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	un_mortgage = new Button(t10, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	Price = nullptr;
	PriceText = nullptr;
	ActiveCell = nullptr;
	ActivePlayer = nullptr;
	BidTurn = -1;
	leftcount = 0;
	ActiveAuction = new int[nop];
	BidAmounts = new int[nop];
	for (int i = 0; i < nop; i++) {
		ActiveAuction[i] = 0;
		BidAmounts[i] = 10;
	}
	BidValue = nullptr;
	BidValueText = nullptr;
	PlayerNameText = nullptr;
	add = new Button(t6, a, Vector2f(30, 30), Color::White, Color(236, 185, 177), Color::Yellow);
	sub = new Button(t7, a, Vector2f(30, 30), Color::White, Color(236, 185, 177), Color::Yellow);
	bid = new Button(t8, a, Vector2f(50, 50), Color::White, Color(236, 185, 177), Color::Yellow);
	fold = new Button(t9, a, Vector2f(50, 50), Color::White, Color(236, 185, 177), Color::Yellow);
	Increment = new Button * [6];
	Decrement = new Button * [6];
	Values = new Text[6];
	for (int i = 0; i < 6; i++) {
		Increment[i] = new Button(t6, a, Vector2f(30, 30), Color::White, Color(186, 181, 181, 100), Color::Yellow);
		Decrement[i] = new Button(t7, a, Vector2f(30, 30), Color::White, Color(186, 181, 181, 100), Color::Yellow);
	}
	printMessage = false;
	message = nullptr;
	managerPressed = false;
	upgradeAble = false;
	SellWin = false;
	upgradeType = 0;
	SellingPrice = 0;
	minimumAuctionPrice = 0;
	purchase = new Button(t1, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	skip = new Button(t9, a, Vector2f(50, 50), Color::White, Color(236, 185, 177), Color::Yellow);
	getOutofJailWin = false;
	payFine = new Button(t11, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	useJailCard = new Button(t12, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	skipTurn = new Button(t13, a, b, Color::White, Color(120, 200, 235), Color::Cyan);
	jailCount = 0;
	CMgetoutofJail = nullptr;
	CHgetoutofJail = nullptr;
}

void OperationManager::SetManagerWindow(GameCells& obj)
{
	managerPressed = true;
	ActiveCell = &obj;
	checkUpgradeAble();
	upgradeType = UpgradeCase();
	ManagerWindow.setPosition(obj.getWindowPos());
	Vector2f v(ManagerWindow.getPosition().x + 170 / 2.0f, ManagerWindow.getPosition().y + 30);
	v.y += 20;
	sell->setPosition(v);
	v.y += 50;
	if (ActiveCell->getItemType() != "STATION" && ActiveCell->getItemType() != "UTILITY" && upgradeAble == true && upgradeType > 0) {
		upgrade->setPosition(v);
		v.y += 50;
		mortgage->setPosition(v);
		un_mortgage->setPosition(v);
		setUpgradeWindow();
	}
	if (ActiveCell->getItemType() == "STATION" || ActiveCell->getItemType() == "UTILITY" || upgradeAble == false) {
		mortgage->setPosition(v);
		un_mortgage->setPosition(v);
	}
	minimumAuctionPrice = ActiveCell->getItemPrice() / 2 + ActiveCell->getUpgradeCost();
	minimumAuctionPrice += ActiveCell->getPercentage(minimumAuctionPrice, 20);
	setSellWindow();
}

bool OperationManager::getManagerstatus()
{
	if (WinOne == true || AuctionWin == true || ManagerWin == true) {
		return true;
	}
	return false;
}

void OperationManager::UpdateManager(Vector2f mousePos)
{
	if (UpgradeWin == true || ManagerWin == true || SellWin == true) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (!(ManagerWindow.getGlobalBounds().contains(mousePos))) {
				if (UpgradeWin == false && SellWin == false) {
					ManagerWin = false;
				}
			}
			if (!(UpgradeWindow.getGlobalBounds().contains(mousePos))) {
				UpgradeWin = false;
				SellWin = false;
				ManagerWin = false;
			}
		}
	}
	if (ManagerWin == true) {
		if (UpgradeWin == false && SellWin == false) {
			sell->StatusUpdate(mousePos);
			if (ActiveCell->getItemType() != "STATION" && ActiveCell->getItemType() != "UTILITY") {
				upgrade->StatusUpdate(mousePos);
			}
			if (ActiveCell->getMortgageStatus() == false) {
				mortgage->StatusUpdate(mousePos);
			}
			if (ActiveCell->getMortgageStatus() == true) {
				un_mortgage->StatusUpdate(mousePos);
			}
			if (upgrade->ButtonClicked()) {
				time = 0;
				while (time < 0.01f) {
					time += clk->getElapsedTime().asSeconds();
				}
				UpgradeWin = true;
			}
			if (sell->ButtonClicked()) {
				time = 0;
				while (time < 0.01f) {
					time += clk->getElapsedTime().asSeconds();
				}
				SellWin = true;
			}
			if (mortgage->ButtonClicked() && ActiveCell->getMortgageStatus() == false) {
				ActiveCell->setMortgageStatus(true);
				ActivePlayer->incrementBalance(ActiveCell->getItemPrice() / 2 + ActiveCell->getUpgradeCost());
				ActivePlayer->removeproperty(ActiveCell->getItemPrice());
			}
			if (un_mortgage->ButtonClicked() && ActiveCell->getMortgageStatus() == true) {
				if (ActivePlayer->getBalance() >= minimumAuctionPrice ){
					ActiveCell->setMortgageStatus(false);
					ActivePlayer->decrementBalance(minimumAuctionPrice);
					ActivePlayer->addproperty(ActiveCell->getItemPrice());
				}
			}

		}
		if (UpgradeWin == true) {
			Increment[0]->StatusUpdate(mousePos);
			Decrement[0]->StatusUpdate(mousePos);
			Increment[1]->StatusUpdate(mousePos);
			Decrement[1]->StatusUpdate(mousePos);
			Increment[2]->StatusUpdate(mousePos);
			Decrement[2]->StatusUpdate(mousePos);
			Increment[3]->StatusUpdate(mousePos);
			Decrement[3]->StatusUpdate(mousePos);
			Increment[4]->StatusUpdate(mousePos);
			Decrement[4]->StatusUpdate(mousePos);
			Increment[5]->StatusUpdate(mousePos);
			Decrement[5]->StatusUpdate(mousePos);
			UpgradeManger();
		}
		if (SellWin == true) {
			purchase->StatusUpdate(mousePos);
			skip->StatusUpdate(mousePos);
			SaleManager();
		}
		if (AuctionWin == true) {
			add->StatusUpdate(mousePos);
			sub->StatusUpdate(mousePos);
			bid->StatusUpdate(mousePos);
			fold->StatusUpdate(mousePos);
			AuctionManager();
		}

	}
	if (WinOne == true) {
		if (AuctionWin == false) {
			buy->StatusUpdate(mousePos);
			auction->StatusUpdate(mousePos);
			if (buy->ButtonClicked()) {
				if (ActivePlayer->getBalance() >= ActiveCell->getItemPrice()) {
					ActiveCell->setowner(*ActivePlayer);
					ActivePlayer->addproperty(ActiveCell->getItemPrice());
					ActivePlayer->decrementBalance(ActiveCell->getItemPrice());
					ActiveCell->setActive(ActivePlayer->getColor());
					WinOne = false;
				}
				if (ActivePlayer->getBalance() < ActiveCell->getItemPrice()&&WinOne==true) {
					printMessage = true;
					time = 0;
				}
			}
			if (auction->ButtonClicked()) {
				time = 0;
				while (time < 0.01f) {
					time += clk->getElapsedTime().asSeconds();
				}
				AuctionWin = true;
			}
			if (printMessage == true) {
				if(time < 500) {
					time += 1;
				}
				else
				{
					printMessage = false;
					AuctionWin = true;
					message = 0;
				}
			}
		}
		if (AuctionWin == true) {
			add->StatusUpdate(mousePos);
			sub->StatusUpdate(mousePos);
			bid->StatusUpdate(mousePos);
			fold->StatusUpdate(mousePos);
			AuctionManager();
		}
	}
	if (RentWin == true) {
		if (time < 1500) {
			time += 1;
		}
		else
		{
			RentWin = false;
		}

	}
	if (getOutofJailWin == true) {
		skipTurn->StatusUpdate(mousePos);
		useJailCard->StatusUpdate(mousePos);
		payFine->StatusUpdate(mousePos);
		getOutofJailManager();
	}
}

void OperationManager::DrawManager(RenderWindow& Window)
{
	if (ManagerWin == true) {
		if (UpgradeWin == false&&SellWin==false) {
			Window.draw(ManagerWindow);
			sell->DrawButton(Window);
			if (ActiveCell->getItemType() != "STATION" && ActiveCell->getItemType() != "UTILITY"&&upgradeAble==true) {
				upgrade->DrawButton(Window);
			}
			if (ActiveCell->getMortgageStatus() == false) {
				mortgage->DrawButton(Window);
			}
			if (ActiveCell->getMortgageStatus() == true) {
				un_mortgage->DrawButton(Window);
			}
		}
		if (UpgradeWin == true) {
			Window.draw(UpgradeWindow);
			Increment[0]->DrawButton(Window);
			Window.draw(Values[0]);
			Decrement[0]->DrawButton(Window);

			Increment[1]->DrawButton(Window);
			Window.draw(Values[1]);
			Decrement[1]->DrawButton(Window);

			Increment[2]->DrawButton(Window);
			Window.draw(Values[2]);
			Decrement[2]->DrawButton(Window);

			Increment[3]->DrawButton(Window);
			Window.draw(Values[3]);
			Decrement[3]->DrawButton(Window);

			Increment[4]->DrawButton(Window);
			Window.draw(Values[4]);
			Decrement[4]->DrawButton(Window);

			Increment[5]->DrawButton(Window);
			Window.draw(Values[5]);
			Decrement[5]->DrawButton(Window);
		}

		if (SellWin == true) {
			Window.draw(Sellwindow);
			Window.draw(*PlayerNameText);
			Window.draw(*Price);
			Window.draw(*PriceText);
			purchase->DrawButton(Window);
			skip->DrawButton(Window);
		}
	}
	if (WinOne == true) {
		if (AuctionWin == false) {
			Window.draw(MainWindow);
			Window.draw(*Price);
			Window.draw(*PriceText);
			buy->DrawButton(Window);
			auction->DrawButton(Window);
			if (printMessage == true) {
				Window.draw(*message);
			}
		}
		if (AuctionWin == true) {
			Window.draw(AuctionWindow);
			Window.draw(*BidValueText);
			Window.draw(*BidValue);
			Window.draw(*PlayerNameText);
			add->DrawButton(Window);
			sub->DrawButton(Window);
			bid->DrawButton(Window);
			fold->DrawButton(Window);
		}
	}
	if (RentWin == true) {
		Window.draw(RentWindow);
	}
	if (getOutofJailWin == true) {
		Window.draw(getOutOfJailWindow);
		skipTurn->DrawButton(Window);
		useJailCard->DrawButton(Window);
		payFine->DrawButton(Window);
	}
}

void OperationManager::setActivePlayer(Player& obj)
{
	if (managerPressed == true) {
		if (obj.getplayername() == ActiveCell->getOwner()) {
			ActivePlayer = &obj;
			ManagerWindow.setFillColor(ActivePlayer->getColor());
			ManagerWin = true;
			managerPressed = false;
		}
		else
		{
			ManagerWin = false;
			managerPressed = false;
		}
	}
}

Vector2f OperationManager::getPos()
{
	return MainWindow.getPosition();
}

void OperationManager::SetWindowone(Player& p, GameCells& cell)
{
	ActivePlayer = &p;
	ActiveCell = &cell;
	WinOne = false;
	WinOne = true;
	MainWindow.setPosition(cell.getWindowPos());
	MainWindow.setFillColor(Color(203,213,93));
	Vector2f v(MainWindow.getPosition().x + 170 / 2.0f, MainWindow.getPosition().y + 80);
	buy->setPosition(v);
	v.y += 50;
	auction->setPosition(v);
	v.y += 45;
	message = new Text(cell.getPriceText());
	message->setString("LOW BALANCE");
	message->setPosition(MainWindow.getPosition().x + 30.0f, v.y);
	Price = new Text(cell.getPrice());
	PriceText = new Text(cell.getPriceText());
	PriceText->setPosition(MainWindow.getPosition().x + 40, MainWindow.getPosition().y + 25);
	Price->setPosition(MainWindow.getPosition().x + 100, MainWindow.getPosition().y + 25);
	setAuctionWindow(cell);
}

int OperationManager::IncrementTurn(int previous)
{
	int T = 0;
	if (previous < nop - 1) {
		T = previous + 1;
	}
	if (previous == nop - 1) {
		T = 0;
	}
	return T;

}

int OperationManager::SwitchAuctionTurn(int previous)
{
	int Turn = previous;
	bool found = false;
	int count = 0;
	while ((found == false)&&(count<=nop)) {
		Turn = IncrementTurn(Turn);
		if (ActiveAuction[Turn] == 0) {
			found = true;
			return Turn;
		}
		if (ActiveAuction[Turn] == 1) {
			found = false;
		}
		count++;
		if (count == 5) {
			break;
		}
	}
	if (found == false) {
		return -1;
	}
}

void OperationManager::AuctionManager()
{
	if (ActiveCell->getStatus() == false&&leftcount!=nop&&BidTurn>=0) {
		if (players[BidTurn]->getBalance() >= minimumAuctionPrice ) {//
			if (add->ButtonClicked()) {
				if (increment(BidAmounts[BidTurn]) <= players[BidTurn]->getBalance()) {
					BidAmounts[BidTurn] = increment(BidAmounts[BidTurn]);
				}
			}
			if (sub->ButtonClicked()) {
				BidAmounts[BidTurn] = decrement(BidAmounts[BidTurn]);

			}
			if (bid->ButtonClicked()) {
				time = 0;
				while (time <= 0.1f) {
					time += clk->getElapsedTime().asSeconds();
				}
				if (leftcount < nop - 1) {
					BidTurn = SwitchAuctionTurn(BidTurn);
				}
				if (leftcount == nop - 1) {
					ActiveCell->setowner(*players[BidTurn]);
					players[BidTurn]->addproperty(ActiveCell->getItemPrice());
					players[BidTurn]->decrementBalance(BidAmounts[BidTurn]);
					ActiveCell->setActive(players[BidTurn]->getColor());
				}
			}
			if (fold->ButtonClicked()) {
				time = 0;
				while (time <= 0.1f) {
					time += clk->getElapsedTime().asSeconds();
				}
				leftcount++;
				ActiveAuction[BidTurn] = 1;
				if (leftcount <= nop - 1) {
					BidTurn = SwitchAuctionTurn(BidTurn);
				}
			}
			BidValue->setString(players[BidTurn]->IntToChar(BidAmounts[BidTurn]));
			PlayerNameText->setString(players[BidTurn]->getplayername());
		}//
		else//
		{
			time = 0;
			while (time <= 0.1f) {
				time += clk->getElapsedTime().asSeconds();
			}
			leftcount++;
			ActiveAuction[BidTurn] = 1;
			if (leftcount <= nop - 1) {
				BidTurn = SwitchAuctionTurn(BidTurn);
			}
		}

	}
	else
	{
		AuctionWin = false;
		WinOne = false;
		ManagerWin = false;
		for (int i = 0; i < nop; i++) {
			ActiveAuction[i] = 0;
			BidAmounts[i] = 0;
		}
		leftcount = 0;
		BidTurn = -1;
	}
}

int OperationManager::increment(int a)
{
	return a+1;
}

int OperationManager::decrement(int b)
{
	if (b>ActiveCell->getPercentage(ActiveCell->getItemPrice(),5)) {
		return b - 1;
	}
	else
	{
		return b;
	}
}

void OperationManager::setAuctionWindow(GameCells& cell)
{
	AuctionWindow.setPosition(cell.getWindowPos());
	AuctionWindow.setFillColor(Color(203, 213, 93));
	BidTurn = IncrementTurn(BidTurn);
	BidValue = new Text(cell.getPriceText());
	BidValueText = new Text(cell.getPriceText());
	PlayerNameText = new Text(cell.getPriceText());
	BidValueText->setString("BID AMOUNT:");
	BidValue->setString("0");
	PlayerNameText->setString(players[BidTurn]->getplayername());
	PlayerNameText->setPosition(AuctionWindow.getPosition().x + 50, AuctionWindow.getPosition().y + 25);
	BidValueText->setPosition(AuctionWindow.getPosition().x + 15, AuctionWindow.getPosition().y + 45);
	BidValue->setPosition(AuctionWindow.getPosition().x + 130, AuctionWindow.getPosition().y + 45);
	add->setPosition(Vector2f(AuctionWindow.getPosition().x + 52.5, AuctionWindow.getPosition().y + 90));
	sub->setPosition(Vector2f(AuctionWindow.getPosition().x + 120.5, AuctionWindow.getPosition().y + 90));
	bid->setPosition(Vector2f(AuctionWindow.getPosition().x + 52.5, AuctionWindow.getPosition().y + 140));
	fold->setPosition(Vector2f(AuctionWindow.getPosition().x +120.5, AuctionWindow.getPosition().y + 140));
	minimumAuctionPrice = ActiveCell->getPercentage(ActiveCell->getItemPrice(), 5);
	for (int i = 0; i < nop; i++) {
		BidAmounts[i] = minimumAuctionPrice;
	}
}

void OperationManager::setRentWindow(GameCells& cell)
{
	RentWin = true;
	ActiveCell=&cell;
	time = 0;
	RentWindow.setPosition(cell.getWindowPos());

}

void OperationManager::setUpgradeWindow()
{
	UpgradeWindow.setPosition(ActiveCell->getWindowPos());
	UpgradeWindow.setFillColor(ActivePlayer->getColor());
	Vector2f a(UpgradeWindow.getPosition().x + 88.0f, UpgradeWindow.getPosition().y + 31.5f);
	Vector2f b(UpgradeWindow.getPosition().x + 162.0f, UpgradeWindow.getPosition().y + 31.5f);
	Vector2f c(UpgradeWindow.getPosition().x + 120.0f, UpgradeWindow.getPosition().y + 22.0f);

	float X = 162;
	float x = 125;
	for (int i = 0; i < 6; i++) {
		Values[i] = ActiveCell->getPriceText();
		Values[i].setString("0");
		Increment[i]->setPosition(a);
		Decrement[i]->setPosition(b);
		Values[i].setPosition(c);
		a.y += 48.0f;
		b.y += 48.0f;
		c.y += 48.0f;
	}

}

void OperationManager::UpgradeManger()
{
	upgradeType = UpgradeCase();
	if (upgradeType == 1) {
		//houses
		if (Increment[0]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 100) {
				ActiveCell->IncCellType(1);
				if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
					ActiveCell->IncHouses();
					ActivePlayer->decrementBalance(100);
					ActivePlayer->addHouse(100);
				}
			}
		}
		if (Decrement[0]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getHouses() > 0) {
				ActiveCell->DecCellType(1);
				if (ActiveCell->getFilledSlots() > ActiveCell->getCellType()) {
					ActiveCell->DecHouses();
					ActivePlayer->incrementBalance(50);
					ActivePlayer->subHouse(100);
				}
			}
		}
		//shops
		if (Increment[1]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getHouses() < 3) {
				if (ActivePlayer->getBalance() >= 300) {
					ActiveCell->IncCellType(3);
					if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
						ActiveCell->IncShops();
						ActivePlayer->decrementBalance(300);
						ActivePlayer->addShop(300);
					}
				}
			}
			if (ActiveCell->getHouses() >= 3) {
				for (int i = 0; i < 3; i++) {
					ActiveCell->DecHouses();
					ActivePlayer->subHouse(100);
				}
				ActiveCell->IncShops();
				ActivePlayer->addShop(300);
			}
		}
		if (Decrement[1]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getShops() > 0) {
				ActiveCell->DecCellType(3);
				if (ActiveCell->getFilledSlots() > ActiveCell->getCellType()) {
					ActiveCell->DecShops();
					ActivePlayer->incrementBalance(150);
					ActivePlayer->subShop(300);
				}
			}
		}
		//hotels
		if (Increment[2]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getHouses() >= 4 && ActiveCell->getShops() >= 2) {
				for (int i = 0; i < 4; i++) {
					ActiveCell->DecHouses();
					ActivePlayer->subHouse(100);
					if (i < 2) {
						ActiveCell->DecShops();
						ActivePlayer->subShop(300);
					}
				}
				ActiveCell->IncHotels();
				ActivePlayer->addHotel(1000);
			}

		}
		if (Decrement[2]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getHotels() > 0) {
				ActiveCell->DecCellType(10);
				if (ActiveCell->getFilledSlots() > ActiveCell->getCellType()) {
					ActiveCell->DecHotels();
					ActivePlayer->subHotel(1000);
					ActivePlayer->incrementBalance(500);
				}
			}
		}
		//wifi
		if (Increment[3]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 30) {
				if (ActiveCell->getWifi() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncWifi();
					ActivePlayer->decrementBalance(30);
				}
			}

		}
		if (Decrement[3]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getWifi() > 0) {
				ActiveCell->DecWifi();
				ActivePlayer->incrementBalance(15);
			}
		}
		//gas
		if (Increment[4]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 50) {
				if (ActiveCell->getGas() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncGas();
					ActivePlayer->decrementBalance(50);
				}
			}
		}
		if (Decrement[4]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getGas() > 0) {
				ActiveCell->DecGas();
				ActivePlayer->incrementBalance(25);
			}
		}
		//electricity
		if (Increment[5]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 50) {
				if (ActiveCell->getElectricity() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncElectricity();
					ActivePlayer->decrementBalance(50);
				}
			}
		}
		if (Decrement[5]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getElectricity() > 0) {
				ActiveCell->DecElectricity();
				ActivePlayer->incrementBalance(25);
			}
		}

	}

	if (upgradeType == 2) {
		//houses
		if (Increment[0]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 100) {
				if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
					ActiveCell->IncHouses();
					ActivePlayer->decrementBalance(100);
					ActivePlayer->addHouse(100);
				}
			}
		}
		if (Decrement[0]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getHouses() > 0) {
				if (ActiveCell->getFilledSlots() > ActiveCell->getCellType()) {
					ActiveCell->DecHouses();
					ActivePlayer->incrementBalance(50);
					ActivePlayer->subHouse(100);
				}
			}
		}
		//shops
		if (Increment[1]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getHouses() < 3) {
				if (ActivePlayer->getBalance() >= 300) {
					if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
						ActiveCell->IncShops();
						ActivePlayer->decrementBalance(300);
						ActivePlayer->addShop(300);
					}
				}
			}
			if (ActiveCell->getHouses() >= 3) {
				for (int i = 0; i < 3; i++) {
					ActiveCell->DecHouses();
					ActivePlayer->subHouse(100);
				}
				ActiveCell->IncShops();
			}

		}
		if (Decrement[1]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getShops() > 0) {
				if (ActiveCell->getFilledSlots() > ActiveCell->getCellType()) {
					ActiveCell->DecShops();
					ActivePlayer->incrementBalance(150);
					ActivePlayer->subShop(300);
				}
			}
		}
		//hotels
		if (Increment[2]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getHouses() >= 4 && ActiveCell->getShops() >= 2) {
				for (int i = 0; i < 4; i++) {
					ActiveCell->DecHouses();
					ActivePlayer->subHouse(100);
					if (i < 2) {
						ActiveCell->DecShops();
						ActivePlayer->subShop(300);
					}
				}
				ActiveCell->IncHotels();
				ActivePlayer->addHotel(1000);
			}

		}
		if (Decrement[2]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getHotels() > 0) {
				if (ActiveCell->getFilledSlots() > ActiveCell->getCellType()) {
					ActiveCell->DecHotels();
					ActivePlayer->incrementBalance(500);
					ActivePlayer->addHotel(1000);
				}
			}
		}
		//wifi
		if (Increment[3]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 30) {
				if (ActiveCell->getWifi() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncWifi();
					ActivePlayer->decrementBalance(30);
				}
			}

		}
		if (Decrement[3]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getWifi() > 0) {
				ActiveCell->DecWifi();
				ActivePlayer->incrementBalance(15);
			}
		}
		//gas
		if (Increment[4]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 50) {
				if (ActiveCell->getGas() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncGas();
					ActivePlayer->decrementBalance(50);
				}
			}
		}
		if (Decrement[4]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getGas() > 0) {
				ActiveCell->DecGas();
				ActivePlayer->incrementBalance(25);
			}
		}
		//electricity
		if (Increment[5]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 50) {
				if (ActiveCell->getElectricity() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncElectricity();
					ActivePlayer->decrementBalance(50);
				}
			}
		}
		if (Decrement[5]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getElectricity() > 0) {
				ActiveCell->DecElectricity();
				ActivePlayer->incrementBalance(25);
			}
		}

	}

	if (upgradeType == 3) {
		//wifi
		if (Increment[3]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 30) {
				if (ActiveCell->getWifi() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncWifi();
					ActivePlayer->decrementBalance(30);
				}
			}

		}
		if (Decrement[3]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getWifi() > 0) {
				ActiveCell->DecWifi();
				ActivePlayer->incrementBalance(15);
			}
		}
		//gas
		if (Increment[4]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 50) {
				if (ActiveCell->getGas() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncGas();
					ActivePlayer->decrementBalance(50);
				}
			}
		}
		if (Decrement[4]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getGas() > 0) {
				ActiveCell->DecGas();
				ActivePlayer->incrementBalance(25);
			}
		}
		//electricity
		if (Increment[5]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 50) {
				if (ActiveCell->getElectricity() < ActiveCell->getFilledSlots()) {
					ActiveCell->IncElectricity();
					ActivePlayer->decrementBalance(50);
				}
			}
		}
		if (Decrement[5]->ButtonClicked()) {
			time = 0;
			while (time < 0.001) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActiveCell->getElectricity() > 0) {
				ActiveCell->DecElectricity();
				ActivePlayer->incrementBalance(25);
			}
		}
	}

	if (upgradeType == -1) {
		time = 0;
		while (time < 0.001) {
			time += clk->getElapsedTime().asSeconds();
		}
		UpgradeWin = false;
		ManagerWin = false;
	}

	Values[0].setString(ActivePlayer->IntToChar(ActiveCell->getHouses()));
	Values[1].setString(ActivePlayer->IntToChar(ActiveCell->getShops()));
	Values[2].setString(ActivePlayer->IntToChar(ActiveCell->getHotels()));
	Values[3].setString(ActivePlayer->IntToChar(ActiveCell->getWifi()));
	Values[4].setString(ActivePlayer->IntToChar(ActiveCell->getGas()));
	Values[5].setString(ActivePlayer->IntToChar(ActiveCell->getElectricity()));
}

void OperationManager::checkUpgradeAble()
{
	if (ActiveCell->getItemType() == "JOHAR") {
		if (ActiveCell->getOwner() == cells[2]->getOwner() && ActiveCell->getOwner() == cells[3]->getOwner()) {
			if (ActiveCell->getFilledSlots() == cells[2]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[3]->getFilledSlots()) {
				upgradeAble = true;
			}
			if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
				upgradeAble = true;
			}
		}
		else
		{
			upgradeAble = false;
		}
	}
	if (ActiveCell->getItemType() == "FAISAL") {
		if (ActiveCell->getOwner() == cells[6]->getOwner() && ActiveCell->getOwner() == cells[7]->getOwner() && ActiveCell->getOwner() == cells[9]->getOwner()) {
			if (ActiveCell->getFilledSlots() == cells[6]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[7]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[9]->getFilledSlots()) {
				upgradeAble = true;
			}
			if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
				upgradeAble = true;
			}
		}
		else
		{
			upgradeAble = false;
		}
	}
	if (ActiveCell->getItemType() == "IQBAL") {
		if (ActiveCell->getOwner() == cells[8]->getOwner() && ActiveCell->getOwner() == cells[13]->getOwner() && ActiveCell->getOwner() == cells[14]->getOwner()) {
			if (ActiveCell->getFilledSlots() == cells[8]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[13]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[14]->getFilledSlots()) {
				upgradeAble = true;
			}
			if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
				upgradeAble = true;
			}
		}
		else
		{
			upgradeAble = false;
		}
	}
	if (ActiveCell->getItemType() == "MODEL") {
		if (ActiveCell->getOwner() == cells[16]->getOwner() && ActiveCell->getOwner() == cells[17]->getOwner() && ActiveCell->getOwner() == cells[18]->getOwner()) {
			if (ActiveCell->getFilledSlots() == cells[16]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[17]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[18]->getFilledSlots()) {
				upgradeAble = true;
			}
			if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
				upgradeAble = true;
			}
		}
		else
		{
			upgradeAble = false;
		}
	}
	if (ActiveCell->getItemType() == "BAHRIA") {
		if (ActiveCell->getOwner() == cells[22]->getOwner() && ActiveCell->getOwner() == cells[23]->getOwner() && ActiveCell->getOwner() == cells[29]->getOwner()) {
			if (ActiveCell->getFilledSlots() == cells[22]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[23]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[29]->getFilledSlots()) {
				upgradeAble = true;
			}
			if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
				upgradeAble = true;
			}
		}
		else
		{
			upgradeAble = true;
		}
	}
	if (ActiveCell->getItemType() == "DHA") {
		if (ActiveCell->getOwner() == cells[26]->getOwner() && ActiveCell->getOwner() == cells[27]->getOwner() && ActiveCell->getOwner() == cells[32]->getOwner()) {
			if (ActiveCell->getFilledSlots() == cells[26]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[27]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[32]->getFilledSlots()) {
				upgradeAble = true;
			}
			if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
				upgradeAble = true;
			}
		}
		else
		{
			upgradeAble = false;
		}
	}
	if (ActiveCell->getItemType() == "GULBERG") {
		if (ActiveCell->getOwner() == cells[35]->getOwner() && ActiveCell->getOwner() == cells[37]->getOwner() && ActiveCell->getOwner() == cells[38]->getOwner()) {
			if (ActiveCell->getFilledSlots() == cells[35]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[37]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[38]->getFilledSlots()) {
				upgradeAble = true;
			}
			if (ActiveCell->getFilledSlots() < ActiveCell->getCellType()) {
				upgradeAble = true;
			}
		}
		else
		{
			upgradeAble = false;
		}
	}

}

int OperationManager::UpgradeCase()
{
	if (ActiveCell->getItemType() == "JOHAR") {
		if (ActiveCell->getFilledSlots() == ActiveCell->getCellType()) {
			if (ActiveCell->getFilledSlots() == cells[2]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[3]->getFilledSlots()) {
				return 1;//upgrade and increase
			}
			if (ActiveCell->getFilledSlots() != cells[2]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[3]->getFilledSlots()) {
				if (ActiveCell->getElectricity() != ActiveCell->getFilledSlots() || ActiveCell->getWifi() != ActiveCell->getFilledSlots() || ActiveCell->getGas() != ActiveCell->getFilledSlots()) {
					return 3;
				}
				else {
					return -1;//don't upgrade
				}
			}
		}
		if (ActiveCell->getFilledSlots() != ActiveCell->getCellType()) {
			if (cells[2]->getFilledSlots() == cells[2]->getCellType() && cells[3]->getFilledSlots() == cells[3]->getCellType()) {
				return 1;//upgrade and increase
			}
			if (cells[2]->getFilledSlots() != cells[2]->getCellType() || cells[3]->getFilledSlots() != cells[3]->getCellType()) {
				return 2;//upgrade 
			}
		}
	}
	if (ActiveCell->getItemType() == "FAISAL") {
		if (ActiveCell->getFilledSlots() == ActiveCell->getCellType()) {
			if (ActiveCell->getFilledSlots() == cells[6]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[7]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[9]->getFilledSlots()) {
				return 1;
			}
			if (ActiveCell->getFilledSlots() != cells[6]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[7]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[9]->getFilledSlots()) {
				if (ActiveCell->getElectricity() != ActiveCell->getFilledSlots() || ActiveCell->getWifi() != ActiveCell->getFilledSlots() || ActiveCell->getGas() != ActiveCell->getFilledSlots()) {
					return 3;
				}
				else {
					return -1;//don't upgrade
				}
			}
		}
		if (ActiveCell->getFilledSlots() != ActiveCell->getCellType()) {
			if (cells[6]->getFilledSlots() == cells[6]->getCellType() && cells[7]->getFilledSlots() == cells[7]->getCellType() && cells[9]->getFilledSlots() == cells[9]->getCellType()) {
				return 1;
			}
			if (cells[6]->getFilledSlots() != cells[6]->getCellType() || cells[7]->getFilledSlots() != cells[7]->getCellType() || cells[9]->getFilledSlots() == cells[9]->getCellType()) {
				return 2;
			}
		}
	}
	if (ActiveCell->getItemType() == "IQBAL") {//8 13 14
		if (ActiveCell->getFilledSlots() == ActiveCell->getCellType()) {
			if (ActiveCell->getFilledSlots() == cells[8]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[13]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[14]->getFilledSlots()) {
				return 1;
			}
			if (ActiveCell->getFilledSlots() != cells[8]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[13]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[14]->getFilledSlots()) {
				if (ActiveCell->getElectricity() != ActiveCell->getFilledSlots() || ActiveCell->getWifi() != ActiveCell->getFilledSlots() || ActiveCell->getGas() != ActiveCell->getFilledSlots()) {
					return 3;
				}
				else {
					return -1;//don't upgrade
				}
			}
		}
		if (ActiveCell->getFilledSlots() != ActiveCell->getCellType()) {
			if (cells[8]->getFilledSlots() == cells[8]->getCellType() && cells[13]->getFilledSlots() == cells[13]->getCellType() && cells[14]->getFilledSlots() == cells[14]->getCellType()) {
				return 1;
			}
			if (cells[8]->getFilledSlots() != cells[8]->getCellType() || cells[13]->getFilledSlots() != cells[13]->getCellType() || cells[14]->getFilledSlots() == cells[14]->getCellType()) {
				return 2;
			}
		}
	}
	if (ActiveCell->getItemType() == "MODEL") {//16 17 18
		if (ActiveCell->getFilledSlots() == ActiveCell->getCellType()) {
			if (ActiveCell->getFilledSlots() == cells[16]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[17]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[9]->getFilledSlots()) {
				return 1;
			}
			if (ActiveCell->getFilledSlots() != cells[16]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[17]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[9]->getFilledSlots()) {
				if (ActiveCell->getElectricity() != ActiveCell->getFilledSlots() || ActiveCell->getWifi() != ActiveCell->getFilledSlots() || ActiveCell->getGas() != ActiveCell->getFilledSlots()) {
					return 3;
				}
				else {
					return -1;//don't upgrade
				}
			}
		}
		if (ActiveCell->getFilledSlots() != ActiveCell->getCellType()) {
			if (cells[16]->getFilledSlots() == cells[16]->getCellType() && cells[17]->getFilledSlots() == cells[17]->getCellType() && cells[18]->getFilledSlots() == cells[18]->getCellType()) {
				return 1;
			}
			if (cells[16]->getFilledSlots() != cells[16]->getCellType() || cells[17]->getFilledSlots() != cells[17]->getCellType() || cells[18]->getFilledSlots() == cells[18]->getCellType()) {
				return 2;
			}
		}
	}
	if (ActiveCell->getItemType() == "BAHRIA") {//22 23 29
		if (ActiveCell->getFilledSlots() == ActiveCell->getCellType()) {
			if (ActiveCell->getFilledSlots() == cells[22]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[23]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[29]->getFilledSlots()) {
				return 1;
			}
			if (ActiveCell->getFilledSlots() != cells[22]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[23]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[29]->getFilledSlots()) {
				if (ActiveCell->getElectricity() != ActiveCell->getFilledSlots() || ActiveCell->getWifi() != ActiveCell->getFilledSlots() || ActiveCell->getGas() != ActiveCell->getFilledSlots()) {
					return 3;
				}
				else {
					return -1;//don't upgrade
				}
			}
		}
		if (ActiveCell->getFilledSlots() != ActiveCell->getCellType()) {
			if (cells[22]->getFilledSlots() == cells[22]->getCellType() && cells[23]->getFilledSlots() == cells[23]->getCellType() && cells[29]->getFilledSlots() == cells[29]->getCellType()) {
				return 1;
			}
			if (cells[22]->getFilledSlots() != cells[22]->getCellType() || cells[23]->getFilledSlots() != cells[23]->getCellType() || cells[29]->getFilledSlots() == cells[29]->getCellType()) {
				return 2;
			}
		}
	}
	if (ActiveCell->getItemType() == "DHA") {//26 27 32
		if (ActiveCell->getFilledSlots() == ActiveCell->getCellType()) {
			if (ActiveCell->getFilledSlots() == cells[26]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[27]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[32]->getFilledSlots()) {
				return 1;
			}
			if (ActiveCell->getFilledSlots() != cells[26]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[27]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[32]->getFilledSlots()) {
				if (ActiveCell->getElectricity() != ActiveCell->getFilledSlots() || ActiveCell->getWifi() != ActiveCell->getFilledSlots() || ActiveCell->getGas() != ActiveCell->getFilledSlots()) {
					return 3;
				}
				else {
					return -1;//don't upgrade
				}
			}
		}
		if (ActiveCell->getFilledSlots() != ActiveCell->getCellType()) {
			if (cells[26]->getFilledSlots() == cells[26]->getCellType() && cells[27]->getFilledSlots() == cells[27]->getCellType() && cells[32]->getFilledSlots() == cells[32]->getCellType()) {
				return 1;
			}
			if (cells[26]->getFilledSlots() != cells[26]->getCellType() || cells[27]->getFilledSlots() != cells[27]->getCellType() || cells[32]->getFilledSlots() == cells[32]->getCellType()) {
				return 2;
			}
		}
	}
	if (ActiveCell->getItemType() == "GULBERG") {//35 37 38
		if (ActiveCell->getFilledSlots() == ActiveCell->getCellType()) {
			if (ActiveCell->getFilledSlots() == cells[35]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[37]->getFilledSlots() && ActiveCell->getFilledSlots() == cells[38]->getFilledSlots()) {
				return 1;
			}
			if (ActiveCell->getFilledSlots() != cells[35]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[37]->getFilledSlots() || ActiveCell->getFilledSlots() != cells[38]->getFilledSlots()) {
				if (ActiveCell->getElectricity() != ActiveCell->getFilledSlots() || ActiveCell->getWifi() != ActiveCell->getFilledSlots() || ActiveCell->getGas() != ActiveCell->getFilledSlots()) {
					return 3;
				}
				else {
					return -1;//don't upgrade
				}
			}
		}
		if (ActiveCell->getFilledSlots() != ActiveCell->getCellType()) {
			if (cells[35]->getFilledSlots() == cells[35]->getCellType() && cells[37]->getFilledSlots() == cells[37]->getCellType() && cells[38]->getFilledSlots() == cells[38]->getCellType()) {
				return 1;
			}
			if (cells[35]->getFilledSlots() != cells[35]->getCellType() || cells[37]->getFilledSlots() != cells[37]->getCellType() || cells[38]->getFilledSlots() == cells[38]->getCellType()) {
				return 2;
			}
		}
	}
	return 0;
}

bool OperationManager::checkDoubleRent(GameCells& obj)
{
	ActiveCell = &obj;
	if (ActiveCell->getItemType() == "JOHAR") {
		if (ActiveCell->getOwner() == cells[2]->getOwner() && ActiveCell->getOwner() == cells[3]->getOwner()) {
			if (cells[2]->getMortgageStatus()==false&&cells[3]->getMortgageStatus()==false) {
				return true;
			}
			return false;
		}
		return false;
	}
	if (ActiveCell->getItemType() == "FAISAL") {
		if (ActiveCell->getOwner() == cells[6]->getOwner() && ActiveCell->getOwner() == cells[7]->getOwner() && ActiveCell->getOwner() == cells[9]->getOwner()) {
			if (cells[6]->getMortgageStatus() == false && cells[7]->getMortgageStatus()==false && cells[9]->getMortgageStatus()==false) {
				return true;
			}
			return false;
		}
		return false;
	}
	if (ActiveCell->getItemType() == "IQBAL") {
		if (ActiveCell->getOwner() == cells[8]->getOwner() && ActiveCell->getOwner() == cells[13]->getOwner() && ActiveCell->getOwner() == cells[14]->getOwner()) {
			if (cells[8]->getMortgageStatus() == false && cells[13]->getMortgageStatus() == false && cells[14]->getMortgageStatus() == false) {
				return true;
			}
			return false;
		}
		return false;
	}
	if (ActiveCell->getItemType() == "MODEL") {
		if (ActiveCell->getOwner() == cells[16]->getOwner() && ActiveCell->getOwner() == cells[17]->getOwner() && ActiveCell->getOwner() == cells[18]->getOwner()) {
			if (cells[16]->getMortgageStatus() == false && cells[17]->getMortgageStatus() == false && cells[18]->getMortgageStatus() == false) {
				return true;
			}
			return false;
		}
		return false;
	}
	if (ActiveCell->getItemType() == "BAHRIA") {
		if (ActiveCell->getOwner() == cells[22]->getOwner() && ActiveCell->getOwner() == cells[23]->getOwner() && ActiveCell->getOwner() == cells[29]->getOwner()) {
			if (cells[22]->getMortgageStatus() == false && cells[23]->getMortgageStatus() == false && cells[29]->getMortgageStatus() == false) {
				return true;
			}
			return false;
		}
		return false;
	}
	if (ActiveCell->getItemType() == "DHA") {
		if (ActiveCell->getOwner() == cells[26]->getOwner() && ActiveCell->getOwner() == cells[27]->getOwner() && ActiveCell->getOwner() == cells[32]->getOwner()) {
			if (cells[26]->getMortgageStatus() == false && cells[27]->getMortgageStatus() == false && cells[32]->getMortgageStatus() == false) {
				return true;
			}
			return false;
		}
		return false;
	}
	if (ActiveCell->getItemType() == "GULBERG") {
		if (ActiveCell->getOwner() == cells[35]->getOwner() && ActiveCell->getOwner() == cells[37]->getOwner() && ActiveCell->getOwner() == cells[38]->getOwner()) {
			if (cells[35]->getMortgageStatus() == false && cells[37]->getMortgageStatus() == false && cells[38]->getMortgageStatus() == false) {
				return true;
			}
			return false;
		}
		return false;
	}
	if (ActiveCell->getItemType() == "UTILITY") {
		if (ActiveCell->getOwner() == cells[12]->getOwner() && ActiveCell->getOwner() == cells[25]->getOwner() && ActiveCell->getOwner() == cells[36]->getOwner() && ActiveCell->getOwner() == cells[39]->getOwner()) {
			if (cells[12]->getMortgageStatus() == false && cells[25]->getMortgageStatus() == false && cells[36]->getMortgageStatus() == false && cells[39]->getMortgageStatus()==false) {
				return true;
			}
			return false;
		}
		return false;
	}
	if (ActiveCell->getItemType() == "STATION") {
		if (ActiveCell->getOwner() == cells[5]->getOwner() && ActiveCell->getOwner() == cells[15]->getOwner() && ActiveCell->getOwner() == cells[24]->getOwner() && ActiveCell->getOwner() == cells[33]->getOwner()) {
			if (cells[5]->getMortgageStatus() == false && cells[15]->getMortgageStatus() == false && cells[24]->getMortgageStatus() == false && cells[33]->getMortgageStatus() == false) {
				return true;
			}
			return false;
		}
		return false;
	}

	return false;
}

GameCells**& OperationManager::GetCells()
{
	return cells;
}

Player**& OperationManager::GetPlayers()
{
	return players;
}

int OperationManager::getnop()
{
	return nop;
}

void OperationManager::setSellWindow()
{
	Sellwindow.setPosition(ActiveCell->getWindowPos());
	Sellwindow.setFillColor(Color(203, 213, 93));
	purchase->setPosition(Vector2f(Sellwindow.getPosition().x + 60, Sellwindow.getPosition().y + 150));
	skip->setPosition(Vector2f(Sellwindow.getPosition().x + 135, Sellwindow.getPosition().y + 150));
	PlayerNameText = new Text(ActiveCell->getPrice());
	PlayerNameText->setPosition(Vector2f(Sellwindow.getPosition().x + 50, Sellwindow.getPosition().y + 30));
	Price = new Text(ActiveCell->getPrice());
	if (ActiveCell->getMortgageStatus() == true) {
		Price->setString(ActiveCell->Convertstring(minimumAuctionPrice));
		SellingPrice = minimumAuctionPrice;
	}
	else {
		Price->setString(ActiveCell->Convertstring(ActiveCell->getItemPrice()));
		SellingPrice = ActiveCell->getItemPrice();
	}
	PriceText = new Text(ActiveCell->getPriceText());
	PriceText->setPosition(Sellwindow.getPosition().x + 40, Sellwindow.getPosition().y + 50);
	Price->setPosition(Sellwindow.getPosition().x + 100, Sellwindow.getPosition().y + 50);
	//for (int i = 0; i < nop; i++) {
	//	if (ActiveCell->getOwner() == players[i]->getplayername()) {
	//		ActiveAuction[i] = 1;
	//		leftcount++;
	//		break;
	//	}
	//}
	BidTurn = SwitchAuctionTurn(BidTurn);
	ActiveCell->setStatus(false);
	PlayerNameText->setString(players[BidTurn]->getplayername());
}

void OperationManager::SaleManager()
{
	int c = 0;
	if (leftcount != nop && ActiveCell->getStatus() == false && BidTurn>=0) {
		if (players[BidTurn]->getBalance() >= SellingPrice && players[BidTurn]->getplayername()!=ActiveCell->getOwner()) {
			if (purchase->ButtonClicked()) {
				time = 0;
				while (time <= 0.1f) {
					time += clk->getElapsedTime().asSeconds();
				}
				ActivePlayer->incrementBalance(SellingPrice);
				ActivePlayer->removeproperty(ActiveCell->getItemPrice());
				ActiveCell->setowner(*players[BidTurn]);
				players[BidTurn]->addproperty(ActiveCell->getItemPrice());
				players[BidTurn]->decrementBalance(SellingPrice);
				ActiveCell->setActive(players[BidTurn]->getColor());
			
			}
			if (skip->ButtonClicked()) {
				time = 0;
				while (time <= 0.1f) {
					time += clk->getElapsedTime().asSeconds();
				}
				leftcount++;
				ActiveAuction[BidTurn] = 1;
				if (leftcount <= nop - 1) {
					BidTurn = SwitchAuctionTurn(BidTurn);
				}

			}
			PlayerNameText->setString(players[BidTurn]->getplayername());
		}
		else {
			time = 0;
			while (time <= 0.1f) {
				time += clk->getElapsedTime().asSeconds();
			}
			leftcount++;
			ActiveAuction[BidTurn] = 1;
			if (leftcount <= nop - 1) {
				BidTurn = SwitchAuctionTurn(BidTurn);
			}

		}
		cout << leftcount << endl;

	}
	else
	{
		if (ActiveCell->getStatus() == false) {
			ActiveCell->sellToBank();
			ActivePlayer->removeproperty(ActiveCell->getItemPrice());
			ActivePlayer->incrementBalance(SellingPrice);
			ActiveCell->setMortgageStatus(false);
		}
		ManagerWin = false;
		SellWin = false;
		leftcount = 0;
		BidTurn = -1;
		for (int i = 0; i < nop; i++) {
			ActiveAuction[i] = 0;
		}

	}
}

void OperationManager::Bankrupcy(Player* owner, Player* debted)
{
	minimumAuctionPrice = ActiveCell->getItemPrice() / 2 + ActiveCell->getUpgradeCost();
	minimumAuctionPrice += ActiveCell->getPercentage(minimumAuctionPrice, 20);
	if (owner != nullptr) {
		owner->setBalance(0);
		for (int i = 0; i < 40; i++) {
			if (cells[i]->getOwner() == debted->getplayername()) {
				debted->removeproperty(cells[i]->getItemPrice());
				owner->addproperty(cells[i]->getItemPrice());
				cells[i]->setowner(*owner);
				cells[i]->setActive(owner->getColor());
				cells[i]->setCellType(0);
				if (cells[i]->getMortgageStatus()) {
					if (owner->getBalance() >= cells[i]->getPercentage(cells[i]->getItemPrice() / 2 + cells[i]->getUpgradeCost(), 20)) {
						owner->decrementBalance(cells[i]->getPercentage(cells[i]->getItemPrice() / 2 + cells[i]->getUpgradeCost(), 20));
					}
					else {
						owner->setdebt(cells[i]->getPercentage(cells[i]->getItemPrice() / 2 + cells[i]->getUpgradeCost(), 20));
					}
				}
				cells[i]->removeUpgrades();
			}
		}
	}
	if (owner == nullptr) {
		for (int i = 0; i < 40; i++) {
			if (cells[i]->getOwner() == debted->getplayername()) {
				debted->removeproperty(cells[i]->getItemPrice());
				cells[i]->sellToBank();
				cells[i]->setCellType(0);
				cells[i]->setMortgageStatus(false);
				cells[i]->removeUpgrades();
			}
		}
	}
}

void OperationManager::setPlayers(Player** p, int n)
{
	nop = n;
	players = p;
	for (int i = 0; i < nop; i++) {
		if (p[i]->getStatus() != "BANKRUPT") {
			players[i] = p[i];
		}
	}


}

void OperationManager::getOutofJailManager()
{
	if (getOutofJailWin == true) {
		if (skipTurn->ButtonClicked()) {
			time = 0;
			while (time <= 0.1f) {
				time += clk->getElapsedTime().asSeconds();
			}
			jailCount++;
			if (jailCount == 2) {
				ActivePlayer->setStatus(0);
				jailCount = 0;
			}
			getOutofJailWin = false;
		}
		if (payFine->ButtonClicked()) {
			time = 0;
			while (time <= 0.1f) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getBalance() >= 400) {
				ActivePlayer->decrementBalance(400);
				ActivePlayer->setStatus(0);
				jailCount = 0;
			}
			else
			{
				jailCount++;
				if (jailCount == 2) {
					ActivePlayer->setStatus(0);
					jailCount = 0;
				}
			}
			getOutofJailWin = false;
		}
		if (useJailCard->ButtonClicked()) {
			time = 0;
			while (time <= 0.1f) {
				time += clk->getElapsedTime().asSeconds();
			}
			if (ActivePlayer->getchJailCard()) {
				ActivePlayer->setStatus(0);
				jailCount = 0;
				ActivePlayer->setchJailCard(false);
				CHgetoutofJail->setOwner(nullptr);
			}
			if (ActivePlayer->getcmJailCard()) {
				ActivePlayer->setStatus(0);
				jailCount = 0;
				ActivePlayer->setcmJailCard(false);
				CMgetoutofJail->setOwner(nullptr);
			}
			if (ActivePlayer->getchJailCard() && ActivePlayer->getcmJailCard()) {
				ActivePlayer->setStatus(0);
				jailCount = 0;
				ActivePlayer->setchJailCard(false);
				CHgetoutofJail->setOwner(nullptr);
			}
			if (ActivePlayer->getchJailCard() == false && ActivePlayer->getcmJailCard() == false) {
				jailCount++;
				if (jailCount == 2) {
					ActivePlayer->setStatus(0);
					jailCount = 0;
				}
			}
			getOutofJailWin = false;
		}
	}
}

void OperationManager::setjailWindow(Player& obj, int& count,bool Y)
{
	getOutofJailWin = true;
	if (Y == true) {
		ActivePlayer = &obj;
		getOutOfJailWindow.setPosition(cells[10]->getPos());
		getOutOfJailWindow.setFillColor(Color(203, 213, 93));
		Vector2f v(getOutOfJailWindow.getPosition().x + 170 / 2.0f, getOutOfJailWindow.getPosition().y + 30);
		v.y += 20;
		skipTurn->setPosition(v);
		v.y += 50;
		payFine->setPosition(v);
		v.y += 50;
		useJailCard->setPosition(v);
		jailCount = count;
	}
}

bool OperationManager::getJailStatus(int& jailcount)
{
	jailcount = jailCount;
	return getOutofJailWin;
}

void OperationManager::SetCards(CommunityChestCards* CM, ChanceCards* CH)
{
	CHgetoutofJail = CH;
	CMgetoutofJail = CM;
}

OperationManager::~OperationManager()
{
	cells = nullptr;
	players = nullptr;
	delete buy;
	buy = nullptr;
	delete auction;
	auction = nullptr;
	delete sell;
	sell = nullptr;
    delete mortgage;
	mortgage = nullptr;
	delete un_mortgage;
	mortgage = nullptr;
	delete upgrade;
	upgrade = nullptr;
	delete PriceText;
	PriceText = nullptr;
	delete Price;
	Price = nullptr;
	ActivePlayer = nullptr;
	delete PlayerNameText;
	PlayerNameText = nullptr;
	ActiveCell = nullptr;
	delete[] ActiveAuction;
	ActiveAuction = nullptr;
	delete[] BidAmounts;
	BidAmounts = nullptr;
	delete BidValue;
	BidValue = nullptr;
	delete BidValueText;
	BidValueText = nullptr;
	delete message;
	message = nullptr;
	delete add;
	add = nullptr;
	delete sub;
	sub = nullptr;
	delete bid;
	bid = nullptr;
	delete fold;
	fold = nullptr;
	clk = nullptr;
	for (int i = 0; i < 6; i++) {
		delete Increment[i];
		delete Decrement[i];
	}
	delete[] Increment;
	delete[] Decrement;
	Increment = nullptr;
	Decrement = nullptr;
	delete[] Values;
	Values = nullptr;
	delete purchase;
	purchase = nullptr;
	delete skip;
	skip = nullptr;
	delete payFine;
	payFine = nullptr;
	delete useJailCard;
	useJailCard = nullptr;
	delete skipTurn;
	skipTurn = nullptr;
	CMgetoutofJail = nullptr;
	CHgetoutofJail = nullptr;
}



