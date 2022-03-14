#include<SFML/Graphics.hpp>
#include"AssetsManager.h"
#include"GameCells.h"
#include"Button.h"
#include<iostream>
#include"Player.h"
#include"Dice.h"
#include"Animation.h"
#include<fstream>
#include<string.h>
using namespace std;
using namespace sf;

static const int VIEW_WIDTH = 1400;
static const int VIEW_HEIGHT = 1000;
Context context;
TextureManager A;
FontManager F;
RenderWindow window(VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "MONOPOLY", Style::Close | Style::Titlebar);
GameCells** cells = new GameCells * [40];
RectangleShape middleboard(Vector2f(533.0f, 533.0f));
Clock clk;
int MainMenuChoice;
int Screen = 1;
bool Loading = false;
bool Rolling = false;
bool Reached = false;
Sprite** backgrounds = new Sprite * [3];
Button** MainMenu = new Button*[3];
Button** PlayerMenu = new Button * [4];
Texture* PlayerTextures = new Texture[5];
Texture* PlayerTokenTextures = new Texture[5];
Color** playerColors = new Color * [5];
Player** Players;
OperationManager*operations;
Text winnerText;
Text winnername;
Text HomeScreen;
Button goToHomescreen(&A["home"], Vector2f(VIEW_WIDTH-40,35), Vector2f(55, 55), Color::White, Color(236, 185, 177), Color::Yellow);
int NumberofPlayers;
int Turn = -1;
int steps = 0, stepcount = 0;
int* positions;
int loopingStep = 0;
int* inJailcounts;
bool found = false;
int* TypesCount = new int[9];
bool GameOver = false;
int BankRuptCount = 0;
int winner;
bool goback = false;
CommunityChestCards** Chests = new CommunityChestCards * [15];
ChanceCards** Chances = new ChanceCards * [14];
ifstream fin;
ofstream fout;
//increments turn
int incrementTurn(int p) {
	int T = 0;
	if (p < NumberofPlayers - 1) {
		T = p + 1;
	}
	if (p == NumberofPlayers - 1) {
		T = 0;
	}
	return T;
}

//switches turns between players
int switchTurn(int previous) {
	bool f = false;
	int T = 0;
	int P = 0;
	P = previous;
	while (f==false)
	{
		P = incrementTurn(P);
		if (Players[P]->getStatus() != "BANKRUPT") {
			T = P;
			f = true;
			break;
		}
	}
	for (int i = 0; i < NumberofPlayers; i++) {
		if (i == T) {
			Players[i]->setPlayerTurn(true);
		}
		else
		{
			Players[i]->setPlayerTurn(false);
		}
	}

	return T;
}

//creates arrays of textures and colors to store all the required textures for all the players 
void LoadPlayerTextures() {
	PlayerTextures[0] = A["p1"];
	PlayerTextures[1] = A["p2"];
	PlayerTextures[2] = A["p3"];
	PlayerTextures[3] = A["p4"];
	PlayerTextures[4] = A["p5"];

	PlayerTokenTextures[0] = A["p1_token"];
	PlayerTokenTextures[1] = A["p2_token"];
	PlayerTokenTextures[2] = A["p3_token"];
	PlayerTokenTextures[3] = A["p4_token"];
	PlayerTokenTextures[4] = A["p5_token"];

	playerColors[0] = new Color(237,28,36);
	playerColors[1] = new Color(246,142,86);
	playerColors[2] = new Color(124,197,118);
	playerColors[3] = new Color(0,174,239);
	playerColors[4] = new Color(168,100,168);
}

void setCards() {
	//CommunityChest cards
	Chests[0] = new ChestCard1(&A["chest1"]);
	Chests[1] = new ChestCard2(&A["chest2"]);
	Chests[2] = new ChestCard3(&A["chest3"]);
	Chests[3] = new ChestCard4(&A["chest4"]);
	Chests[4] = new ChestCard5(&A["chest5"],F["BoldItalic"]);
	Chests[5] = new ChestCard6(&A["chest6"]);
	Chests[6] = new ChestCard7(&A["chest7"]);
	Chests[7] = new ChestCard8(&A["chest8"]);
	Chests[8] = new ChestCard9(&A["chest9"]);
	Chests[9] = new ChestCard10(&A["chest10"]);
	Chests[10] = new ChestCard11(&A["chest11"]);
	Chests[11] = new ChestCard12(&A["chest12"]);
	Chests[12] = new ChestCard13(&A["chest13"]);
	Chests[13] = new ChestCard14(&A["chest14"]);
	Chests[14] = new ChestCard15(&A["chest15"]);

	//ChanceCards
	 Chances[0] = new ChanceCard1(&A["chance1"]);
	Chances[1] = new ChanceCard2(&A["chance2"]);
	Chances[2] = new ChanceCard3(&A["chance3"]);
	Chances[3] = new ChanceCard4(&A["chance4"]);
	Chances[4] = new ChanceCard5(&A["chance5"]);
	Chances[5] = new ChanceCard6(&A["chance6"]);
	Chances[6] = new ChanceCard7(&A["chance7"], F["BoldItalic"]);
	Chances[7] = new ChanceCard8(&A["chance8"]);
	Chances[8] = new ChanceCard9(&A["chance9"]);
	Chances[9] = new ChanceCard10(&A["chance10"]);
	Chances[10] = new ChanceCard11(&A["chance11"]);
	Chances[11] = new ChanceCard12(&A["chance12"]);
	Chances[12] = new ChanceCard13(&A["chance13"]);
	Chances[13] = new ChanceCard14(&A["chance14"]);

}

//creates an array of sprites to load all the backgrounds of the game window
void setBackgrounds() {
	backgrounds[0] = new Sprite(A["mainmenu"]);
	backgrounds[1] = new Sprite(A["playernumber"]);
	backgrounds[2] = new Sprite(A["wallpaper"]);
}

//creates 2 arrays of buttons for the main and player menu screens
void setMenu() {
	MainMenu[0] = new Button(&(A["start"]), Vector2f(175.5f, 226.0f), Vector2f(233.0f, 66.0f), Color::White, Color(236, 185, 177), Color::Yellow);
	MainMenu[1] = new Button(&(A["load"]), Vector2f(175.5f, 308.0f), Vector2f(233.0f, 66.0f), Color::White, Color(236, 185, 177), Color::Yellow);
	MainMenu[2] = new Button(&(A["exit"]), Vector2f(175.5f, 388.0f), Vector2f(233.0f, 66.0f), Color::White, Color(236, 185, 177), Color::Yellow);
	PlayerMenu[0]= new Button(&A["2"], Vector2f(113.0f, 340.0f), Vector2f(100.0f, 100.0f), Color::White, Color(236, 185, 177), Color::Yellow);
	PlayerMenu[1]= new Button(&A["3"], Vector2f(113.0f, 460.0f), Vector2f(100.0f, 100.0f), Color::White, Color(236, 185, 177), Color::Yellow);
	PlayerMenu[2]= new Button(&A["4"], Vector2f(113.0f, 580.0f), Vector2f(100.0f, 100.0f), Color::White, Color(236, 185, 177), Color::Yellow);
	PlayerMenu[3]= new Button(&A["5"], Vector2f(113.0f, 700.0f), Vector2f(100.0f, 100.0f), Color::White, Color(236, 185, 177), Color::Yellow);

}

//updates the status of the buttons and returns what button is pressed
int MainMenuUdate(Vector2f mousePos) {
	for (int i = 0; i < 3; i++) {
		MainMenu[i]->StatusUpdate(mousePos);
	}
	for (int i = 0; i < 3; i++) {
		if (MainMenu[i]->ButtonClicked() == true) {
			return i + 1;
		}
	}
	return 0;
}

void GameOverScreen(int I) {
	HomeScreen.setFont(F["BoldItalic"]);
	HomeScreen.setCharacterSize(40);
	HomeScreen.setPosition(250, 350);
	HomeScreen.setString("CLICK ANYWHERE TO GO BACK TO HOME SCREEN");
	HomeScreen.setOutlineColor(Color::Black);
	HomeScreen.setOutlineThickness(3);

	winnerText.setFont(F["BoldItalic"]);
	winnerText.setCharacterSize(30);
	winnerText.setPosition(580, 420);
	winnerText.setString("HAS WON THE GAME!!");
	winnerText.setOutlineColor(Color::Black);
	winnerText.setOutlineThickness(3);

	winnername.setFont(F["BoldItalic"]);
	winnername.setCharacterSize(30);
	winnername.setPosition(440, 420);
	winnername.setString("PLAYER 1");
	winnername.setOutlineColor(Color::Black);
	winnername.setOutlineThickness(3);


}

//updates the status of the buttons and returns what button is pressed
int PlayerMenuUpdate(Vector2f mousePos) {
	for (int i = 0; i < 4; i++) {
		PlayerMenu[i]->StatusUpdate(mousePos);
	}
	for (int i = 0; i < 4; i++) {
		if (PlayerMenu[i]->ButtonClicked() == true) {
			return i + 1;
		}
	}
	return 0;
}

//creates a 2d array of CElls and using pollymorphism creates a board including all types of cells
void setboard() {
	for (int i = 0; i < 9; i++) {
		TypesCount[i] = 0;
	}
	middleboard.setTexture(&(A["middle"]));
	middleboard.setOrigin(middleboard.getSize() / 2.0f);
	middleboard.setPosition(446.0f + 25.0f, 446.0f + 25.0f);
	middleboard.setOutlineThickness(3.0f);
	middleboard.setOutlineColor(Color::Black);
	Vector2f coordinates(118.0f, 118.0f);
	cells[0] = new Go(&(A["go"]), coordinates, false, true,1,nullptr);
	coordinates.x += 93.0f;
	cells[1] = new CommunityChest(&(A["chest"]), coordinates, false, false, 0,nullptr);
	coordinates.x += 65.0f;
	cells[2] = new PrivateProperties(&(A["johar_a"]), coordinates, false, false,0,&(A["deed"]),"Johar Town A","JOHAR",200,80, F["BoldItalic"],TypesCount[1]);
	coordinates.x += 65.0f;
	cells[3] = new PrivateProperties(&(A["johar_b"]), coordinates, false, false,0, &(A["deed"]),"Johar Town B","JOHAR",250,90, F["BoldItalic"], TypesCount[1]);
	coordinates.x += 65.0f;
	cells[4] = new PropertyTax(&(A["propertytax"]), coordinates, false, false,0,nullptr);
	coordinates.x += 65.0f;
	cells[5] = new UtilitiesandStations(&(A["railway"]), coordinates, false, false,0, &(A["deed"]),"Railway","STATION",2500,350, F["BoldItalic"], TypesCount[7]);
	coordinates.x += 65.0f;
	cells[6] = new PrivateProperties(&(A["faisal_a"]), coordinates, false, false,0, &(A["deed"]),"Faisal Town A","FAISAL",300,100, F["BoldItalic"], TypesCount[2]);
	coordinates.x += 65.0f;
	cells[7] = new PrivateProperties(&(A["faisal_b"]), coordinates, false, false,0, &(A["deed"]),"Faisal Town B","FAISAL",400,130, F["BoldItalic"], TypesCount[2]);
	coordinates.x += 65.0f;
	cells[8] = new PrivateProperties(&(A["iqbal_a"]), coordinates, false, false, 0, &(A["deed"]),"Iqbal Town A","IQBAL",250,60, F["BoldItalic"], TypesCount[0]);
	coordinates.x += 65.0f;
	cells[9] = new PrivateProperties(&(A["faisal_c"]), coordinates, false, false,0, &(A["deed"]),"Faisal Town C","FAISAL",400,130, F["BoldItalic"], TypesCount[2]);
	coordinates.x += 93.0f;
	cells[10] = new Jail(&(A["jail"]), coordinates, false, true,0,nullptr);
	coordinates.y += 93.0f;
	cells[11] = new Chance(&(A["chance"]), coordinates, true, false,0,nullptr);
	coordinates.y += 65.0f;
	cells[12] = new UtilitiesandStations(&(A["lesco"]), coordinates, true, false,0, &(A["deed"]),"L.E.S.C.O.","UTILITY",5000,450, F["BoldItalic"], TypesCount[8]);
	coordinates.y += 65.0f;
	cells[13] = new PrivateProperties(&(A["iqbal_b"]), coordinates, true, false,0, &(A["deed"]),"Iqbal Town B","IQBAL",300,70, F["BoldItalic"], TypesCount[0]);
	coordinates.y += 65.0f;
	cells[14] = new PrivateProperties(&(A["iqbal_c"]), coordinates, true, false,0, &(A["deed"]), "Iqbal Town C", "IQBAL", 400, 100, F["BoldItalic"], TypesCount[0]);
	coordinates.y += 65.0f;
	cells[15] = new UtilitiesandStations(&(A["metro"]), coordinates, true, false,0, &(A["deed"]), "Metro", "STATION", 2000, 200, F["BoldItalic"], TypesCount[7]);
	coordinates.y += 65.0f;
	cells[16] = new PrivateProperties(&(A["model_a"]), coordinates, true, false,0, &(A["deed"]),"Model Town A","MODEL",800,200, F["BoldItalic"], TypesCount[3]);
	coordinates.y += 65.0f;
	cells[17] = new PrivateProperties(&(A["model_b"]), coordinates, true, false, 0, &(A["deed"]), "Model Town B", "MODEL", 850, 250, F["BoldItalic"], TypesCount[3]);
	coordinates.y += 65.0f;
	cells[18] = new PrivateProperties(&(A["model_c"]), coordinates, true, false, 0, &(A["deed"]), "Model Town C", "MODEL", 2000, 500, F["BoldItalic"], TypesCount[3]);
	coordinates.y += 65.0f;
	cells[19] = new CommunityChest(&(A["chest"]), coordinates, true, false, 0, nullptr);
	coordinates.y += 93.0f;
	cells[20] = new Parking(&(A["parking"]), coordinates, false, true, 0,nullptr);
	coordinates.x -= 93.0f;
	cells[21] = new Chance(&(A["chance"]), coordinates, false, false, 0,nullptr);
	coordinates.x -= 65.0f;
	cells[22] = new PrivateProperties(&(A["bahria_a"]), coordinates, false, false, 0, &(A["deed"]),"Bahria Town A","BAHRIA",2500,800, F["BoldItalic"], TypesCount[6]);
	coordinates.x -= 65.0f;
	cells[23] = new PrivateProperties(&(A["bahria_b"]), coordinates, false, false, 0, &(A["deed"]), "Bahria Town B", "BAHRIA", 3000, 900, F["BoldItalic"], TypesCount[6]);
	coordinates.x -= 65.0f;
	cells[24] = new UtilitiesandStations(&(A["bus"]), coordinates, false, false, 0, &(A["deed"]), "Bus", "STATION", 2000, 200, F["BoldItalic"], TypesCount[7]);
	coordinates.x -= 65.0f;
	cells[25] = new UtilitiesandStations(&(A["sui"]), coordinates, false, false, 0, &(A["deed"]),"Sui","UTILITY",2500,350, F["BoldItalic"], TypesCount[8]);
	coordinates.x -= 65.0f;
	cells[26] = new PrivateProperties(&(A["dha_a"]), coordinates, false, false, 0, &(A["deed"]),"D.H.A A","DHA",2000,500, F["BoldItalic"], TypesCount[5]);
	coordinates.x -= 65.0f;
	cells[27] = new PrivateProperties(&(A["dha_b"]), coordinates, false, false, 0, &(A["deed"]), "D.H.A B", "DHA", 2000, 500, F["BoldItalic"], TypesCount[5]);
	coordinates.x -= 65.0f;
	cells[28] = new CommunityChest(&(A["chest"]), coordinates, false, false, 0,nullptr);
	coordinates.x -= 65.0f;
	cells[29] = new PrivateProperties(&(A["bahria_c"]), coordinates, false, false, 0, &(A["deed"]), "Bahria Town C", "BAHRIA", 3000, 1000, F["BoldItalic"], TypesCount[6]);
	coordinates.x -= 93.0f;
	cells[30] = new GoToJail(&(A["gotojail"]), coordinates, false, true, 1,nullptr);
	coordinates.y -= 93.0f;
	cells[31] = new LandTax(&(A["landtax"]), coordinates, true, false, 1,nullptr);
	coordinates.y -= 65.0f;
	cells[32] = new PrivateProperties(&(A["dha_y"]), coordinates, true, false, 1, &(A["deed"]), "D.H.A Y", "DHA", 2500, 1000, F["BoldItalic"], TypesCount[5]);
	coordinates.y -= 65.0f;
	cells[33] = new UtilitiesandStations(&(A["orange"]), coordinates, true, false, 1, &(A["deed"]),"Orange","STATION",2500,350, F["BoldItalic"], TypesCount[7]);
	coordinates.y -= 65.0f;
	cells[34] = new Chance(&(A["chance"]), coordinates, true, false, 1,nullptr);
	coordinates.y -= 65.0f;
	cells[35] = new PrivateProperties(&(A["gulberg_a"]), coordinates, true, false, 1, &(A["deed"]),"Gulberg II A","GULBERG",1000,300, F["BoldItalic"], TypesCount[4]);
	coordinates.y -= 65.0f;
	cells[36] = new UtilitiesandStations(&(A["wasa"]), coordinates, true, false, 1, &(A["deed"]),"W.A.S.A","UTILITY",4000,400, F["BoldItalic"], TypesCount[8]);
	coordinates.y -= 65.0f;
	cells[37] = new PrivateProperties(&(A["gulberg_b"]), coordinates, true, false, 1, &(A["deed"]), "Gulberg II B", "GULBERG", 1200, 350, F["BoldItalic"], TypesCount[4]);
	coordinates.y -= 65.0f;
	cells[38] = new PrivateProperties(&(A["gulberg_c"]), coordinates, true, false, 1, &(A["deed"]), "Gulberg II C", "GULBERG", 2500, 600, F["BoldItalic"], TypesCount[4]);
	coordinates.y -= 65.0f;
	cells[39] = new UtilitiesandStations(&(A["ptcl"]), coordinates, true, false, 1, &(A["deed"]), "P.T.C.L", "UTILITY", 8000, 500, F["BoldItalic"], TypesCount[8]);


}

//after number of players are selected, this functions allocates the memory to the players5
void setPlayers(int player) {
	LoadPlayerTextures();
	NumberofPlayers = player;
	positions = new int[NumberofPlayers];
	inJailcounts = new int[NumberofPlayers];
	Players = new Player * [NumberofPlayers];
	float K = 130.0f;
	char arr[] = { "PLAYER 1" };
	for (int i = 0; i < NumberofPlayers; i++) {
		arr[7] = i + 49;
		Players[i] = new Player(F["BoldItalic"], *playerColors[i], &(PlayerTextures[i]), Vector2f(1150.0f, K), arr, &(PlayerTokenTextures[i]), cells[0]->getPos());
		K += 180.0f;
		positions[i] = 0;
		inJailcounts[i] = 0;
	}
	Players[0]->setPlayerTurn(true);
	operations = new OperationManager(&clk,cells, Players, NumberofPlayers,&A["operation"],&A["Low"], &A["buy"], &A["auction"], &A["sell"], &A["upgrade"], &A["mortgage"], &A["add"], &A["sub"], &A["bid"], &A["fold"],&A["unmort"],&A["upgradewin"],&A["fine"],&A["card"],&A["skip"]);
	int i = 0;
	for (i = 0; i < 14; i++) {
		Chances[i]->setOperator(operations);
		Chests[i]->setOperator(operations);
	}
	Chests[i]->setOperator(operations);
	for (int i = 0; i < 40; i++) {
		cells[i]->setOperationManager(operations);
		cells[i]->setCommunityChestCards(Chests);
		cells[i]->setChanceCards(Chances);
	}
	operations->SetCards(Chests[4], Chances[6]);
}

bool CheckGameOver() {
	if (BankRuptCount == NumberofPlayers-1) {
		for (int i = 0; i < NumberofPlayers; i++) {
			if (Players[i]->getStatus() != "BANKRUPT") {
				winner = i;
				break;
			}
		}
		return true;
	}
	return false;
}

void RemoveBankruptPlayer() {
	BankRuptCount = 0;
	for (int i = 0; i < NumberofPlayers; i++) {
		if (Players[i]->getStatus() == "BANKRUPT") {
			BankRuptCount++;
		}
	}
}

void clearGame() {
	for (int i = 0; i < 40; i++) {
		delete cells[i];
	}
	delete[]cells;
	cells = nullptr;
	for (int i = 0; i < NumberofPlayers; i++) {
		delete Players[i];
	}
	delete[]Players;
	Players = nullptr;
	for (int i = 0; i < 3; i++) {
		delete backgrounds[i];
		delete MainMenu[i];
	}
	delete[]backgrounds;
	delete[]MainMenu;
	backgrounds = nullptr;
	MainMenu = nullptr;
	for (int i = 0; i < 4; i++) {
		delete PlayerMenu[i];
	}
	delete[]PlayerMenu;
	PlayerMenu = nullptr;
	delete operations;
	operations = nullptr;
	for (int i = 0; i < 5; i++) {
		delete playerColors[i];
	}
	delete[]playerColors;
	playerColors = nullptr;
	delete[] PlayerTextures;
	PlayerTextures = nullptr;
	delete[] PlayerTokenTextures;
	delete[] positions;
	positions = nullptr;
	delete[] inJailcounts;
	inJailcounts = nullptr;
	delete[] TypesCount;
	TypesCount = nullptr;
	for (int i = 0; i < 15; i++) {
		delete[]Chests[i];
	}
	delete[]Chests;
	Chests = nullptr;
	for (int i = 0; i < 14; i++) {
		delete[]Chances[i];
	}
	delete[]Chances;
	Chances = nullptr;
}

void saveGame() {
	fout.open("Scripts/PlayerData.txt");
	fout << NumberofPlayers << endl;
	for (int i = 0; i < NumberofPlayers; i++) {
		Players[i]->savegame(fout);
	}
	fout.close();
	fout.open("Scripts/CellsData.txt");
	for (int i = 0; i < 40; i++) {
		cells[i]->saveGame(fout);
	}
	fout.close();
}

void loadGame() {
	fin.open("Scripts/PlayerData.txt");
	fin >> NumberofPlayers;
	setPlayers(NumberofPlayers);
	for (int i = 0; i<NumberofPlayers; i++) {
		Players[i]->loadgame(fin);
	}
	fin.close();
	fin.open("Scripts/CellsData.txt");
	for (int i = 0; i < 40; i++) {
		cells[i]->loadgame(fin);
	}
	fin.close();
	for (int i = 0; i < 40; i++) {
		if (cells[i]->getOwner() != "BANK") {
			for (int j = 0; j < NumberofPlayers; j++) {
				if (cells[i]->getOwner() == Players[j]->getplayername()) {
					cells[i]->setowner(*Players[j]);
					break;
				}
			}
		}
	}
}

int main() {
	setCards();
	setMenu();
	setBackgrounds();
	setboard();
	Dice dice(Vector2f(118, 940.0f));
	Color a(186, 181, 181,100);
	Animation LoadingAnimation(Vector2f(VIEW_WIDTH/2.0f, VIEW_HEIGHT/2.0f),&(A["Loading"]), Vector2u(6, 3), 0.02f,Color::Black);
	Animation RollingAnimation(Vector2f(middleboard.getPosition()),&(A["DiceRoll"]), Vector2u(4, 4), 0.02f,Color::White);
	Vector2f mousePos;
	int choice=0;
	float delta = 0.0f;
	float animTime = 0.0f;
	while (window.isOpen()) {
		delta = clk.restart().asSeconds();
		Event events;
		while (window.pollEvent(events)) {
			switch (events.type)
			{//closes the window if close window button is pressed
			case Event::Closed:
				window.close();
				break;
			}
		}
		//stores the position of the mouse relative to the window
		GameOver = CheckGameOver();
		GameOverScreen(winner);
		mousePos.x = (float)Mouse::getPosition(window).x;
		mousePos.y = (float)Mouse::getPosition(window).y;
		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			system("cls");
			for (int z = 0; z < 40; z++) {
				cout << cells[z]->getItemType() << " : " << cells[z]->getOwner() << " : " << cells[z]->getCellType()<<endl<<endl;
			}
			cout << endl << endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
			system("cls");
			for (int h = 0; h < NumberofPlayers; h++) {
				cout << Players[h]->getplayername() << " : " << Players[h]->getBalance() << " : " << Players[h]->getProperties() << " : " << Players[h]->getNetWorth() << endl << endl;
			}
		}
		//if (Mouse::isButtonPressed(Mouse::Left)) {
		//	cout << mousePos.x << " , " << mousePos.y << endl;
		//}
		//the main menu screen
		if (Screen == 1) {
			if (choice == 0) {
				choice = MainMenuUdate(mousePos);
			}
			if (choice > 0) {
				backgrounds[0]->setColor(a);
				Loading = true;
			}
		}
		//player menu screen
		if (Screen == 2) {
			if (choice == 0) {
				choice = PlayerMenuUpdate(mousePos);
			}
			if (choice > 0) {
				backgrounds[1]->setColor(a);
				Loading = true;
			}
		}
		//game board screen
		if (Screen == 3) {
			goToHomescreen.StatusUpdate(mousePos);
			for (int i = 0; i < 40; i++) {
				cells[i]->updateCell(mousePos);
			}
			operations->UpdateManager(mousePos);
			operations->setActivePlayer(*Players[switchTurn(Turn)]);
			//operations->setActivePlayer(*Players[Turn]);
			dice.DiceUpdate(mousePos);//updates the status of "roll the dice" button
			bool p = false;
			if (Rolling == false) {
				p = dice.getDiceStatus();
			}
			if (p == true) {
				Rolling = true;
				p = false;
			}
		}

		if (GameOver == true) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				GameOver = false;
				backgrounds[Screen - 1]->setColor(Color::White);
				window.close();
			}
		}
		window.clear(Color::White);//clearing the screen
		if (Screen == 1) {//drawing main menu screen
			window.draw(*backgrounds[0]);
			for (int i = 0; i < 3; i++) {
				MainMenu[i]->DrawButton(window);
			}
		}
		if (Screen == 2) {//drawing player menu screen
			window.draw(*backgrounds[1]);
			for (int i = 0; i < 4; i++) {
				PlayerMenu[i]->DrawButton(window);
			}
		}
		if (Screen == 3) {//drawing the gameboard screen
				if (Turn >= 0) {//movving the players after they have rolled the dice
					if (Players[Turn]->getStatus() != "IN JAIL") {
						if (Players[Turn]->MoveToken(1, 1, cells[positions[Turn]]->getPos()) == false) {
							Players[Turn]->MoveToken(1, 1, cells[positions[Turn]]->getPos());
						}
						if (positions[Turn] == 39 && loopingStep > 0) {//resets the position to "Go" cell after one rotation and then moves the steps
							Players[Turn]->resetloop(cells[0]->getPos());//accordin to the dices
							if (loopingStep > 0) {
								positions[Turn] = loopingStep - 1;
								if (positions[Turn] > 0) {
									Players[Turn]->incrementBalance(500);
								}
							}
						}
						if (cells[positions[Turn]]->reachedCell(Players[Turn]->getPos())) {
							if (Reached == true) {
								Reached = cells[positions[Turn]]->Method(*Players[Turn]);
								if (positions[Turn] == 30 && (Players[Turn]->getStatus() == "IN JAIL")) {
									positions[Turn] = 10;
								}
								Reached = false;
							}
							RemoveBankruptPlayer();
							GameOver = CheckGameOver();
							operations->setPlayers(Players, NumberofPlayers);
						}
					}
					if (Players[Turn]->getStatus() == "IN JAIL") {
						if (Reached == true) {
							Reached = operations->getJailStatus(inJailcounts[Turn]);
						}
					}

				}
			window.draw(*backgrounds[2]);
			window.draw(middleboard);
			for (int i = 0; i < 40; i++) {
				cells[i]->DrawCell(window);
			}
			for (int i = 0; i < NumberofPlayers; i++) {
				Players[i]->PlayerDraw(window);
				Players[i]->TokenDraw(window);
			}
			for (int i = 0; i < 40; i++) {
				cells[i]->drawWindow(window, cells[i]->ButtonStatus());
			}
			operations->DrawManager(window);
			goToHomescreen.DrawButton(window);
			if (goToHomescreen.ButtonClicked()) {
				Loading = true;
				goback = true;
				backgrounds[Screen - 1]->setColor(a);
			}
		}
		if (Loading == true) {//draws the loading animation on to the screen and switches between screen
			window.draw(*backgrounds[Screen-1]);
			LoadingAnimation.Update(delta);//switching between frames
			animTime+=clk.getElapsedTime().asSeconds();//increments the time for which the loding animation is active
			if (animTime <= 1.0f) {
				LoadingAnimation.DrawAnimation(window);
			}
			else
			{
				Loading = false;
				if (Screen == 1&&choice>0) {
					if (choice == 1) {
						Screen = 2;
					}
					if (choice == 2) {
						loadGame();
						Screen = 3;
					}
					if (choice == 3) {
						window.close();
					}
					choice = 0;
					animTime = 0;
					backgrounds[0]->setColor(Color::White);
				}
				if (Screen == 2&&choice>0) {//loading second screen
					NumberofPlayers = choice + 1;
					setPlayers(NumberofPlayers);
					Screen = 3;
					choice = 0;
					animTime = 0;
					backgrounds[1]->setColor(Color::White);
				}
				if (Screen == 3&&goback==true) {
					saveGame();
					goback = false;
					window.close();
				}
			}
		}
		if (Rolling == true) {//draws the dice rolling animation to the screen
			loopingStep = 0;
			RollingAnimation.Update(delta);//switches between frames
			animTime += clk.getElapsedTime().asSeconds();
			if (animTime <= 0.5f) {
				RollingAnimation.DrawAnimation(window);
			}
			else
			{
				Rolling = false;
				found = false;
				Turn = switchTurn(Turn);
				if (Players[Turn]->getStatus() != "IN JAIL") {
					steps = dice.RollDice(*Players[switchTurn(Turn)]);//geting the random result after the dice is rolled
					for (int i = 0; i < 40; i++) {
						if (cells[i]->reachedCell(Players[Turn]->getPos())) {
							positions[Turn] = i;
							break;
						}
					}
					positions[Turn] += steps;
					if (positions[Turn] > 39) {//checks if the loop is completed
						loopingStep = positions[Turn] - 39;
						positions[Turn] = 39;
					}
					else {
						loopingStep = 0;
					}
					for (int i = 0; i < 14; i++) {
						Chances[i]->amountonDice(steps);
					}
					animTime = 0;
					Reached = true;
				}
				if (Players[Turn]->getStatus() == "IN JAIL") {
					operations->setjailWindow(*Players[Turn], inJailcounts[Turn], true);
					animTime = 0;
					Reached = true;
				}
			}
		}
		if (Screen == 3) {//draws the dice roll button and the dices onto the screen
			dice.Draw(window);
		}
		if (GameOver == true) {
			backgrounds[2]->setColor(Color::Blue);
			window.draw(*backgrounds[2]);
			window.draw(HomeScreen);
			window.draw(winnername);
			window.draw(winnerText);
		}


		window.display();

	}
	clearGame();
}


