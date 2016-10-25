//Includes
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <ctype.h>
#include <vector>

//Define namespace
using namespace std;

//Define functions
void printString(string stringInput);
void pause();
void screenResolution();
void setTextColor(int col);
void nameGreeting();
void choseFontSize();
void greeting();
void classMenu();
void inputSign();
void drawInventory();
void instantPrint(string stringInput);
void removeFromInvSortArray(int itemID);
void grantItem(int itemID, int quantity);
void shop(int shopID);
void printStringColor(int color, string stringInput, int color2, string stringInput2, int color3, string stringInput3, int color4, string stringInput4, int color5, string stringInput5, bool instant);
void asignDefaultRarityColor();
void battle(int enemyType);
void abilities(int playerClass);
void death();
void levelUpCheck();
void printTalentUI(int firstTalent, int secondTalent, string talentNames[4]);
void talents();
string genRandomString(int stringSize);
void classPundare();
void classAlkis();
void classGangster();
void skanstull();
void rinkeby();
void falafelShop();
void plattan();
void shadyGuy();
void cigoteket();
void djKhaled();
void classCheck();
void NK();
void fightPrint();
void TC();
void burgerKing();

//Global vars
//Vars used for loading
bool firstInvLoad = true;
int winHeight = 0;
int winWide = 0;

//Inventory related vars
int numberOfItems = 16;
int invSort = 1;
int equipedWeapon = 1;
int invSortPos[16];
int defaultColor = 7;

//Player related vars
string playerName = "";
int playerClass = 0;
int playerGold = 0;
int playerLevel = 1;
int playerExperience = 0;
int playerMaxHealth = 10;
int playerHealth = playerMaxHealth;
int attackPower;
int healPower;
string classOneTalents[4] = { "Goodiebag", "Kurva", "Sverige", "Satan" };
string classTwoTalents[4] = { "Dance Around", "Beer throw", "Shot", "Fall" };
string classThreeTalents[4] = { "Rob", "Hit", "Walla", "Shoot" };
int classOneTalentsDamage[4] = { 0,3,3,5 };
int classOneTalentsRedDamage[4] = { 3,0,0,-2 };
int classTwoTalentsDamage[4] = { 2,3,0,3 };
int classTwoTalentsRedDamage[4] = { 1,0,3,-3 };
int classThreeTalentsDamage[4] = { 1,1,0,2 };
int classThreeTalentsRedDamage[4] = { 0,0,4,-3 };
int talentOne = 0;
int talentTwo = 0;
string talentUsed;


//Create a structure of type array for every item
struct inventoryItems {
	string quality = "Common";
	string name;
	int quantity = 0;
	bool weapon = false;
	bool consumable = false;
	int damage = 0;
	string type = "Quest";
	int healthRegen = 0;
	string desc = "";
	bool questItem = false;
	int inventoryColor = defaultColor;
	int levelRequirement = 0;
	int buyPrice = 0;
} invItems[16];

//Create a structure of type array for every enemy
struct ememies {
	int health = 10;
	string name;
	int damage;
	int xpGain;
	int maxHealth = 10;
	bool hasDrop = false;
	int drop;
	int dropAmount;
	int potentialLoot;
} enemy[10];

//Create a structure of type array for every shopkeeper
struct shopKeepers {
	string name;
	string greeting;
	int items[5];
	vector<string> ascii;
	int numberOfAsciiLines = 0;
	int numberofCharsPerLine = 0;
} shopKeeper[10];

//Start loadin from here
void main()
{
	//Assign name and info for every item in the game
	invItems[1].name = "Stick"; invItems[1].quantity = 1; invItems[1].quality = "Common"; invItems[1].weapon = true; invItems[1].buyPrice = 1; invItems[1].type = "Weapon"; invItems[1].damage = 2; invItems[1].desc = "Just a stick";
	invItems[2].name = "Health potion"; invItems[2].quantity = 0; invItems[2].quality = "Uncommon"; invItems[2].consumable = true; invItems[2].buyPrice = 10; invItems[2].healthRegen = 5; invItems[2].desc = "Heals for 5 HP when used";
	invItems[3].name = "Rotten burger"; invItems[3].quantity = 0; invItems[3].quality = "Common"; invItems[3].consumable = true; invItems[3].levelRequirement = 2; invItems[3].buyPrice = 10; invItems[3].healthRegen = 0; invItems[3].desc = "Really shouldn't eat this";
	invItems[4].name = "Bottle"; invItems[4].quantity = 1; invItems[4].quality = "Legendary"; invItems[4].levelRequirement = 3; invItems[4].buyPrice = 13;
	invItems[5].name = "Good Good"; invItems[5].quantity = 0; invItems[5].quality = "Rare"; invItems[5].buyPrice = 50; invItems[5].consumable = true; invItems[5].healthRegen = playerMaxHealth; invItems[5].desc = "That good good";
	invItems[6].name = "Gucci belt"; invItems[6].quantity = 0; invItems[6].quality = "Rare"; invItems[6].buyPrice = 100; invItems[6].weapon = true; invItems[6].damage = 5; invItems[6].desc = "Expensive shit";
	invItems[7].name = "Strange man's knife "; invItems[7].quantity = 0; invItems[7].quality = "Uncommon"; invItems[7].buyPrice = 50; invItems[7].weapon = true; invItems[7].levelRequirement = 2; invItems[7].damage = 3; invItems[7].desc = "It is a knife";
	invItems[8].name = "The Key"; invItems[8].quantity = 0; invItems[8].quality = "Legendary"; invItems[8].inventoryColor = 16; invItems[8].levelRequirement = 2; invItems[8].questItem = true; invItems[8].desc = "I GOT THE KEYS"; 
	invItems[9].name = "Akash's location"; invItems[9].quantity = 0; invItems[9].quality = "Rare"; invItems[9].questItem = true; invItems[9].desc = "Where can he be?";
	invItems[10].name = "Dank Kush"; invItems[10].quantity = 0; invItems[10].buyPrice = 2674; invItems[10].quality = "DANK"; invItems[10].inventoryColor = 16;
	invItems[13].name = "Good"; invItems[13].quantity = 0; invItems[13].quality = "Rare"; invItems[13].buyPrice = 50; invItems[13].consumable = true; invItems[13].healthRegen = playerMaxHealth;

	//MOBS
	enemy[0].health = 10; enemy[0].name = "Subwayguard"; enemy[0].damage = 1; enemy[0].xpGain = 100, enemy[0].maxHealth = 10; enemy[0].drop = 2; enemy[0].hasDrop = true; enemy[0].dropAmount = 1; enemy[0].potentialLoot = 2;
	enemy[1].health = 11; enemy[1].name = "Ken Bone"; enemy[1].damage = 1; enemy[1].xpGain = 100, enemy[1].maxHealth = 11; enemy[1].drop = 2; enemy[1].hasDrop = true; enemy[1].dropAmount = 1; enemy[1].potentialLoot = 2;
	enemy[2].health = 10; enemy[2].name = "Bartender"; enemy[2].damage = 1; enemy[2].xpGain = 100, enemy[2].maxHealth = 10; enemy[2].drop = 2; enemy[2].hasDrop = true; enemy[2].dropAmount = 1; enemy[2].potentialLoot = 2;
	enemy[3].health = 17; enemy[3].name = "Strange man"; enemy[3].damage = 2; enemy[3].xpGain = 300, enemy[3].maxHealth = 17; enemy[3].drop = 5; enemy[3].hasDrop = true; enemy[3].dropAmount = 2; enemy[3].potentialLoot = 7;
	enemy[4].health = 40; enemy[4].name = "DAS VAPELORD"; enemy[4].damage = 3; enemy[3].xpGain = 2000, enemy[3].maxHealth = 40; enemy[4].drop = 8; enemy[3].hasDrop = true; enemy[3].dropAmount = 4; enemy[3].potentialLoot = 2;
	
	
	//ShopKeepers
	shopKeeper[0].name = "BurgerKing"; shopKeeper[0].greeting = "Hello my friend, Grabben was here earlier and ate all the food, sry."; shopKeeper[0].items[0] = 1; shopKeeper[0].items[1] = 6; shopKeeper[0].items[2] = 7;
	shopKeeper[0].ascii = { " _____                     _____ _         ", "| __  |_ _ ___ ___ ___ ___|  |  |_|___ ___ ", "| __ -| | |  _| . | -_|  _|    -| |   | . |", "|_____|___|_| |_  |___|_| |__|__|_|_|_|_  |", 	"              |___|                   |___|" }; shopKeeper[0].numberofCharsPerLine = 43; shopKeeper[0].numberOfAsciiLines = 5;
	shopKeeper[1].name = "Nordiska Kompaniet"; shopKeeper[1].greeting = "Hello, welcome to VaskButiken.exe"; shopKeeper[1].items[0] = 4; shopKeeper[1].items[1] = 6; shopKeeper[1].items[2] = 2; shopKeeper[1].ascii = { ".ssssssssssssssssssssssssssssssssssssss.",	"-m+......-ohmho+:--hd--:+shmh+-....../m-",	"-m:    :yho-`      hh      `:ods-    :m-",	"-m:  :hmm.         hh         `:hh-  :m-",	"-m:`yd:dmh`        hh           -dms`:m-", "-m+dy` dhmo        hh        .+hy:.hh/m-",	"-mmy`  ds/m:       hh     `/yh+.   `hmm-",	"-md.   ds sd.      hh   -sds-       -mm-",	"-mo    ds `hy`     hh.+hy/`          ym-",	"-m/    ds  .mo     hmhdh-            +m-",	"-m/    ds   /m:    hh  /ds.          +m-",	"-ms    ds    sd.   hh   `+do`        ym-",	"-mm.   ds    `hy   hh     `od+`     -mm-",	"-mmy`  ds     -mo  hh       .sd/   `hdm-",	"-m+hy` ds      /m: hh         -yh:.hy/m-",	"-m:`sd/ds       sd.hh           :mmo`:m-",	"-m:  :hmy`      `hyhh         `/hy-  :m-",	"-m:    :sdo:`    -mmh      `:sds-    :m-",	"-m/......-+ydhs+/:smd-:/osddy/......./m-",	".ssssssssssssssssssssssssssssssssssssss." }; shopKeeper[1].numberOfAsciiLines = 20; shopKeeper[1].numberofCharsPerLine = 40;

	asignDefaultRarityColor();

	choseFontSize();

	//Set console to be fulscreen
	system("mode 1000");

	screenResolution();

	greeting();

	//Tell the compiler what number to base rand(); of
	srand(time(NULL));

	nameGreeting();

	classMenu();
}

void nameGreeting()
{
	cout << endl;
	//Call the function to print text
	printString("Hello my friend, how are you?");

	pause();
	system("cls");

	cout << endl;
	printString("Oh, that's right. I don't care.");

	pause();
	system("cls");

	cout << endl;
	printString("What's your name?");
	inputSign();
	cin >> playerName;
	system("cls");

	cout << endl;
	printString("Was poppin', " + playerName + "?");

	pause();
}

void classMenu()
{
	int classConfirm;
failSaver:

	system("cls");

	cout << endl;
	//user picks a class
	printString("It's time to pick a class");
differentClass:
	printString("What would you like to play?");

	//Set text color to 2 and print
	printStringColor(7, "[1] ", 2, "Pundare", 7, "", 7, "", 7, "", false);

	//Set text color to 8 and print
	printStringColor(7, "[2] ", 8, "Alkis", 7, "", 7, "", 7, "", false);

	//Set text color to 9 and print
	printStringColor(7, "[3] ", 9, "Gangster", 7, "", 7, "", 7, "", false);

	//Add the sign > where the input is supposed to go
	inputSign();

	cin >> playerClass;
	cout << endl;

	switch (playerClass)
	{
			//class choice switchcase
	case 1:
		printString("The pundare will have a different fighting technique");
		printString("The pundare wil use his willpower and augumented reality to win fights");
		printString("Plus you will also be abled to be one with nature");
		printString("(or just really high)");
		playerClass = 1;
		break;
	case 2:
		//not sure vad jag har skrivit xD
		printString("If you have less than 10 braincells then this is the class for you. ");
		printString("I mean who would choose a class that just runs in to battle with their");
		printString("head first. The smartest class would be gangster, but nevermind. ");
		printString("With the alkis class you can throw your baws ass drunken fists at your enemies.");
		printString("Just look at Kenta, he is a really cool alkis.");
		playerClass = 2;
		break;
	case 3:
		printString("Oh so you're a gangster ");
		printString("This class is especially good when you want to attack at a long range with your 9mm.");
		printString("You have really powerful bullets that you can fire at your enemy. ");
		printString("If you are a real orten thug then this is the class for you. ");
		playerClass = 3;
		break;
	default:
		printString("That is not an option.");
		pause();
		system("cls");
		cout << endl;
		goto differentClass;
	}
	cout << endl;
	//confirm the users choice
	printString("Are you sure you want to play this class? ");
	printString("[1] Yes I am sure.");
	printString("[2] No I want to browse the other classes.");

	inputSign();
	cin >> classConfirm;
	switch (classConfirm)
	{
		//switchcase confirm choice
	case 1:
		printString("Then let's gooooo!");
		printString("Let's check out your inventory");
		pause();
		drawInventory();
		system("cls");
		system("cls");
		classCheck();
		break;
	case 2:
		printString("Okay then.");
		pause();
		system("cls");
		cout << endl;
		goto differentClass;
	default:
		printString("That is not an option.");
		pause();
		goto failSaver;

	}
	system("cls");
}

//Function to let the program know when the user is done selecting font size
void choseFontSize()
{
	//Until the user has pressed one print press one to proceed.
	do {
		system("cls");
		cout << "If you want to change the font size, do so now.\nPress 1 to proceed." << endl;
	} while (_getch() != '1');
}

//Function to print the greeting text
void greeting()
{
	instantPrint(" _    _      _                            _                                   ");
	instantPrint("| |  | |    | |                          | |                                  ");
	instantPrint("| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___                             ");
	instantPrint("| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\                            ");
	instantPrint("\\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |                           ");
	instantPrint(" \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/                            ");
	cout << endl << endl;
	instantPrint(" _   _                    _                   _    ___  _             _      ");
	instantPrint("| | | |                  | |                 | |  / _ \\| |           | |     ");
	instantPrint("| | | | __ _ _ __   ___  | |     ___  _ __ __| | / /_\\ \\ | ____ _ ___| |__   ");
	instantPrint("| | | |/ _` | '_ \\ / _ \\ | |    / _ \\| '__/ _` | |  _  | |/ / _` / __| '_ \\  ");
	instantPrint("\\ \\_/ / (_| | |_) |  __/ | |___| (_) | | | (_| | | | | |   < (_| \\__ \\ | | | ");
	instantPrint(" \\___/ \\__,_| .__/ \\___| \\_____/\\___/|_|  \\__,_| \\_| |_/_|\\_\\__,_|___/_| |_| ");
	instantPrint("            | |                                                              ");
	instantPrint("            |_|                                                              ");

	setTextColor(15);

	instantPrint("                _                                      ");
	instantPrint("              (`  ).                   _               ");
	instantPrint("             (     ).              .:(`  )`.           ");
	instantPrint("            _(       '`.          :(   .    )          ");
	instantPrint("        .=(`(      .   )     .--  `.  (    ) )         ");
	instantPrint("  ''--  ((    (..__.:'-'   .+(   )   ` _`  ) )         ");
	instantPrint("`(       `(       ) )       (   .  )     (   )  ._     ");
	instantPrint("((    )      ` __.:'   )     (   (   ))     `-'.-(`  ) ");
	instantPrint("`(    )  ( )       --'       `- __.'         :(      ))");
	instantPrint("` ¨'_..-'  (_.'          .')                    `(   ) ");
	instantPrint("                  (_  )                     ` __.:'    ");
	instantPrint("                                                       ");
	instantPrint("--..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._.-__--..");

	setTextColor(7);

	pause();

	system("cls");
}

//Function to asign default color values based on item quality
void asignDefaultRarityColor()
{
	// For every item in te game
	for (int i = 1; i < numberOfItems + 1; i++)
	{
		//Check if item is of rarity legendary and has not been assigned a custom value
		if (invItems[i].quality == "Legendary" && invItems[i].inventoryColor == defaultColor)
		{
			//Set color to color 14
			invItems[i].inventoryColor = 14;
		}
		//Check if item is of rarity Rare and has not been assigned a custom value
		else if (invItems[i].quality == "Rare" && invItems[i].inventoryColor == defaultColor)
		{
			//Set color to color 11
			invItems[i].inventoryColor = 11;
		}
		//Check if item is of rarity Uncommon and has not been assigned a custom value
		else if (invItems[i].quality == "Uncommon" && invItems[i].inventoryColor == defaultColor)
		{
			//Set color to color 2
			invItems[i].inventoryColor = 2;
		}
		//Check if item has not been assigned a rarity and not a custom color
		else if (invItems[i].quality == "Common" && invItems[i].inventoryColor == defaultColor)
		{
			//Set color to color 8
			invItems[i].inventoryColor = 8;
		}
	}
}

//Function to set text color the proper way
/// <summary>Used to set text color the proper way
/// <para>Usage: setTextColor(0-16);</para>
/// </summary>
void setTextColor(int col)
{
	//Set text color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (col & 0x0F));
}

//Function to print text in the center
/// <summary>Used to print text slowly
/// <para>Usage: printString("Text here");</para>
/// </summary>
void printString(string stringInput)
{
	int spacing = winWide / 2 - stringInput.length() / 2;
	cout << string(spacing, ' ');
	//For every letter in string do this
	for (int i = 0; i < stringInput.length(); i++)
	{
		//Print character and sleep for 30ms
		cout << stringInput[i];
		Sleep(30);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			for (int n = i + 1; n < stringInput.length(); n++)
			{
				cout << stringInput[n];
			}
			while (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				//Do nothing
			}
			break;
		}

	}

	cout << endl;
}

//Function to print text with color in the center
/// <summary>Used to print text slowly and with mixed color with a feature of rainbow when color 16 is specified. Default col is 7
/// <para>Usage: printStringColor(16, "", 7, "", 7, "", 7, "", false/true wether you want it to be instant or not);</para>
/// </summary>
void printStringColor(int color, string stringInput, int color2, string stringInput2, int color3, string stringInput3, int color4, string stringInput4, int color5, string stringInput5, bool instant)
{
	//Add every stirng together and caculate string length to center content
	int totalLength = stringInput.length() + stringInput2.length() + stringInput3.length() + stringInput4.length() + stringInput5.length();
	int spacing = winWide / 2 - totalLength / 2;
	int rainbowColors[6]{ 12, 14, 10, 11, 9, 13 };
	int colorLoop = 0;
	bool isRainbow = false;

	cout << string(spacing, ' ');

	//Set text color to color if int isn't 16 = rainbow
	if (color == 16)
	{
		isRainbow = true;
	}
	else
	{
		setTextColor(color);
		isRainbow = false;
	}

	for (int i = 0; i < stringInput.length(); i++)
	{
		if (isRainbow)
		{
			setTextColor(rainbowColors[colorLoop]);
			colorLoop++;
			if (colorLoop > 5)
			{
				colorLoop = 0;
			}
		}

		cout << stringInput[i];
		//Add a delay between each character if wanted
		if (instant == false)
			Sleep(30);

		//Check if shift is pressed
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			//For every character that has not been printed yet, print them
			for (int n = i + 1; n < stringInput.length(); n++)
			{
				//Check if color is rainbow and if so, change color for each char.
				if (isRainbow)
				{
					setTextColor(rainbowColors[colorLoop]);
					colorLoop++;
					if (colorLoop > 5)
					{
						colorLoop = 0;
					}
				}
				//Print the remaining chars.
				cout << stringInput[n];
			}
			//While shift is pressed pause code, so that it doesn't skip everything
			while (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				//Do nothing
			}
			break;
		}

	}

	//Set text color to color if int isn't 16 = rainbow
	if (color2 == 16)
	{
		isRainbow = true;
	}
	else
	{
		setTextColor(color2);
		isRainbow = false;
	}

	//For every letter in string do this
	for (int i = 0; i < stringInput2.length(); i++)
	{
		if (isRainbow)
		{
			setTextColor(rainbowColors[colorLoop]);
			colorLoop++;
			if (colorLoop > 5)
			{
				colorLoop = 0;
			}
		}

		cout << stringInput2[i];
		//Add a delay between each character if wanted
		if (instant == false)
			Sleep(30);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			for (int n = i + 1; n < stringInput2.length(); n++)
			{
				if (isRainbow)
				{
					setTextColor(rainbowColors[colorLoop]);
					colorLoop++;
					if (colorLoop > 5)
					{
						colorLoop = 0;
					}
				}
				cout << stringInput2[n];
			}
			while (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				//Do nothing
			}
			break;
		}

	}

	//Set text color to color if int isn't 16 = rainbow
	if (color3 == 16)
	{
		isRainbow = true;
	}
	else
	{
		setTextColor(color3);
		isRainbow = false;
	}

	//For every letter in string do this
	for (int i = 0; i < stringInput3.length(); i++)
	{
		if (isRainbow)
		{
			setTextColor(rainbowColors[colorLoop]);
			colorLoop++;
			if (colorLoop > 5)
			{
				colorLoop = 0;
			}
		}

		cout << stringInput3[i];
		//Add a delay between each character if instant is false
		if (instant == false)
			Sleep(30);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			for (int n = i + 1; n < stringInput3.length(); n++)
			{
				if (isRainbow)
				{
					setTextColor(rainbowColors[colorLoop]);
					colorLoop++;
					if (colorLoop > 5)
					{
						colorLoop = 0;
					}
				}
				cout << stringInput3[n];
			}
			while (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				//Do nothing
			}
			break;
		}

	}

	//Set text color to color if int isn't 16 = rainbow
	if (color4 == 16)
	{
		isRainbow = true;
	}
	else
	{
		setTextColor(color4);
		isRainbow = false;
	}

	//For every letter in string do this
	for (int i = 0; i < stringInput4.length(); i++)
	{
		if (isRainbow)
		{
			setTextColor(rainbowColors[colorLoop]);
			colorLoop++;
			if (colorLoop > 5)
			{
				colorLoop = 0;
			}
		}

		cout << stringInput4[i];
		//Add a delay between each character if wanted
		if (instant == false)
			Sleep(30);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			for (int n = i + 1; n < stringInput4.length(); n++)
			{
				if (isRainbow)
				{
					setTextColor(rainbowColors[colorLoop]);
					colorLoop++;
					if (colorLoop > 5)
					{
						colorLoop = 0;
					}
				}
				cout << stringInput4[n];
			}
			while (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				//Do nothing
			}
			break;
		}

	}

	//Set color to color
	if (color5 == 16)
	{
		isRainbow = true;
	}
	else
	{
		setTextColor(color5);
		isRainbow = false;
	}

	//For every letter in string do this
	for (int i = 0; i < stringInput5.length(); i++)
	{
		if (isRainbow)
		{
			setTextColor(rainbowColors[colorLoop]);
			colorLoop++;
			if (colorLoop > 5)
			{
				colorLoop = 0;
			}
		}

		cout << stringInput5[i];
		//Add a delay between each character if wanted
		if (instant == false)
			Sleep(30);

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			for (int n = i + 1; n < stringInput5.length(); n++)
			{
				if (isRainbow)
				{
					setTextColor(rainbowColors[colorLoop]);
					colorLoop++;
					if (colorLoop > 5)
					{
						colorLoop = 0;
					}
				}
				cout << stringInput5[n];
			}
			while (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				//Do nothing
			}
			break;
		}

	}

	//Set text color back to default
	setTextColor(7);

	//Add a new line
	cout << endl;
}

//Function to print text instantly in the center
/// <summary>Used to print text instantly and centered
/// <para>Usage: instantPrint("This is printed instanly");</para>
/// </summary>
void instantPrint(string stringInput)
{
	//Get center of screen depending on string length
	int spacing = winWide / 2 - stringInput.length() / 2;

	//Print the spaces
	cout << string(spacing, ' ');

	//Print the string in the center
	cout << stringInput;

	cout << endl;
}

//Function to draw the '> ' sign before the input
/// <summary>Used to draw the input sign '> '
/// <para>Usage: inputSign();</para>
/// </summary>
void inputSign()
{
	//Define variable types and calculate string length and assign position
	string pauseText = "Press any key to proceed";
	int pauseTextLength = pauseText.length();
	int pauseTextPos = winWide / 2 - pauseTextLength / 2;
	cout << string(pauseTextPos, ' ') << "> ";
}

//Function to pause the console until an input is present
/// <summary>Used to pause the console and prevent it from continuing
/// <para>Usage: pause();</para>
/// </summary>
void pause()
{
	//Define variable types and calculate string length and assign position
	string pauseText = "Press any key to proceed";
	int pauseTextLength = pauseText.length();
	int pauseTextPos = winWide / 2 - pauseTextLength / 2;

	//Print Press any key to proceed and pause
	printString(pauseText);
	inputSign();
	system("pause >nul");
}

//Function to determine console line width and number of line height
void screenResolution()
{
	//Throw an error if you can't retrieve screen res.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		//Error
		cout << "Cannot determine console size." << endl;
	}
	else
	{
		//Set global vars to window size in characters
		winHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		winWide = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
}

//Function to draw the inventory
/// <summary>Used to draw the inventory on the screen
/// <para>Usage: drawInventory();</para>
/// </summary>
void drawInventory()
{
	//Create a string with playername and 's inventory, as well as some others
	string inventoryTitle = playerName + "'s inventory", input, damageString, levelReqText;
	int additionForOddNames = 0, numDigits = 1, numDigitsXp = 1, numDigitsGold, numDigitsPlayerLevel, quantityOrDamage, secondInput, levelReqColor;

	//IF the inventory title (name) is odd compensate in positioning later on
	if (inventoryTitle.length() % 2 == 1)
	{
		additionForOddNames = 1;
	}
	else
	{
		additionForOddNames = 0;
	}

	//Check the length of playerExperience and playerGold in character amount and not value 321 = 3 chars
	if (playerExperience > 99)
		numDigitsXp = 3;
	else if (playerExperience > 9)
		numDigitsXp = 2;
	else
		numDigitsXp = 1;
	if (playerGold > 999)
		numDigitsGold = 4;
	else if (playerGold > 99)
		numDigitsGold = 3;
	else if (playerGold > 9)
		numDigitsGold = 2;
	else
		numDigitsGold = 1;
	if (playerLevel > 9)
		numDigitsPlayerLevel = 2;
	else
		numDigitsPlayerLevel = 1;

	//Defines a goto point
top:

	system("cls");

	//Add some rows
	cout << endl << endl << endl << endl;

	//Print the ui, including player name, hp etc.
	instantPrint(" ______________/_/(*)\\_\\______________ ");
	instantPrint(" \\/---------------------------------\\/ ");
	instantPrint("  |" + string(32 / 2 - inventoryTitle.length() / 2 - 1, ' ') + "[" + inventoryTitle + "]" + string(32 / 2 - inventoryTitle.length() / 2 - additionForOddNames, ' ') + "|  ");
	instantPrint("  |---------------------------------|  ");
	printStringColor(7, "  | Level: " + to_string(playerLevel) + " " + to_string(playerExperience) + "/500" + string(13 - numDigitsGold - numDigitsXp - numDigitsPlayerLevel, ' ') + "Gold: ", 6, to_string(playerGold), 7, " |  ", 7, "", 7, "", true);
	printStringColor(7, "  |  " + string(26 - playerMaxHealth, ' ') + "HP: ", 4, string(playerHealth, '#'), 8, string(playerMaxHealth - playerHealth, '#'), 7, " |  ", 7, "", true);
	instantPrint("  |---------------------------------|  ");

	//For every item in the game
	for (int i = 0; i < numberOfItems; i++)
	{
		//Check the quantity or damage of the item to compensate the gui layout
		if (invItems[i].quantity > 9 || invItems[i].damage > 9)
			numDigits = 2;
		else
			numDigits = 1;

		//If item is a weapon, instead of printing quantity, print damage and tell the user it's damage else just set the value to the quantity of the item
		if (invItems[i].weapon == true)
		{
			quantityOrDamage = invItems[i].damage;
			numDigits = numDigits + 8;
			damageString = "(damage)";
		}
		else
		{
			quantityOrDamage = invItems[i].quantity;
			damageString = "";
		}

		//If quantity is more than 0, meaning the user has the item. Do this
		if (invItems[i].quantity > 0)
		{
			//Check if this code is ran for the first time to add the item id's to the sorting array
			if (firstInvLoad)
			{
				//Tell the program which item id is in which array slot and increase the the int invsort by 1 for each item
				invSortPos[invSort] = i;
				invSort++;
			}

			if (invItems[i].levelRequirement > playerLevel)
			{
				levelReqColor = 4;
				levelReqText = "Lvl. " + to_string(invItems[i].levelRequirement);
			}
			else
			{
				levelReqColor = 8;
				levelReqText = "";
			}

			//Check if item is not weapon and if so, don't print the string damage and also keep the quantity stat on the inventory slot else do the oposite
			if (invItems[i].weapon == false)
			{
				printStringColor(7, "  | " + to_string(invItems[i].quantity) + "x ", invItems[i].inventoryColor, invItems[i].name, levelReqColor, string(29 - to_string(invItems[i].quantity).length() - invItems[i].name.length() - levelReqText.length(), ' ') + levelReqText, 7, " |  ", 7, "", true);
				printStringColor(7, "  | ", invItems[i].inventoryColor, invItems[i].quality, 7, " (" + invItems[i].type + ")" + string(28 - invItems[i].type.length() - invItems[i].quality.length(), ' '), 7, "", 7, " |  ", true);
			}
			else
			{
				printStringColor(7, "  | ", invItems[i].inventoryColor, invItems[i].name, levelReqColor, string(31 - invItems[i].name.length() - levelReqText.length(), ' ') + levelReqText, 7, " |  ", 7, "", true);
				
				//If weapon is equiped add -> next to the slot on each side <-
				if (equipedWeapon == i)
					printStringColor(7, " -> | ", invItems[i].inventoryColor, invItems[i].quality, 7, " (" + invItems[i].type + ")" + string(19 - invItems[i].type.length() - invItems[i].quality.length() - to_string(invItems[i].damage).length(), ' ') + " Damage: ", 4, to_string(invItems[i].damage), 7, " | <- ", true);
				else
					printStringColor(7, "  | ", invItems[i].inventoryColor, invItems[i].quality, 7, " (" + invItems[i].type + ")" + string(19 - invItems[i].type.length() - invItems[i].quality.length() - to_string(invItems[i].damage).length(), ' ') + " Damage: ", 4, to_string(invItems[i].damage), 7, " |  ", true);
			}

			//Print the description for every item
			instantPrint("  | " + invItems[i].desc + string(31 - invItems[i].desc.length(), ' ') + " |  ");
			instantPrint("  |---------------------------------|  ");
		}
	}
	//Set the firstInLoad to false to prevent items being added twice to array earlier in code
	firstInvLoad = false;

	//Print the rest of the UI
	instantPrint("  |                                 |  ");
	instantPrint("  |____________/_/(*)\\_\\____________|  ");
	instantPrint("  \\/-------------------------------\\/  ");

	printString("'Equip', 'Use', 'Delete',");
	printString("'Talents' or 'Back'");

	inputSign();
	cin >> input;

	//Check the user input for various spelling probabilities
	if (input == "equip" || input == "Equip" || input == "EQUIP")
	{
		//For every item
		for (int i = 1; i < numberOfItems; i++)
		{
			//If the array slot is greater than 1
			if (invSortPos[i] > 0)
				//Print the array slot nubmer and the item name
				printString("[" + to_string(i) + "] " + invItems[invSortPos[i]].name);
		}
		//Defines a goto point
		inputSign();
		cin >> secondInput;

		//Cleares the cin if input isn't numreric
		if (!cin)
		{
			cin.clear();
			string ignore;
			getline(cin, ignore);
			goto top;
		}

		//If input is between 0 and numberOfItems
		if (secondInput < numberOfItems && secondInput > 0)
		{
			//If number is less than items in sorting array and also item is a weapon since this is the equip part else throw an error to the user
			if (secondInput < invSort && invItems[invSortPos[secondInput]].weapon == true)
			{
				if (playerLevel > invItems[invSortPos[secondInput]].levelRequirement)
				{
					//Set equipedWeapon to the selected item
					equipedWeapon = invSortPos[secondInput];
					printString(invItems[invSortPos[secondInput]].name + " has been equipped!");
					pause();
					goto top;
				}
				else
				{
					//Give the user some info about required level and current etc
					printString("You need to level up a few levels before you can use this.");
					printStringColor(7, "Level requirement: ", 4, to_string(invItems[invSortPos[secondInput]].levelRequirement), 7, "", 7, "", 7, "", false);
					printString("You are level: " + to_string(playerLevel) + " with " + to_string(playerExperience) + "/500 xp");
					pause();
					goto top;
				}
			}
			else
			{
				printString("You can only equip weapons!");
				pause();
				goto top;
			}
		}

	}
	//If input is talent, go to the talents function in order to select talents
	else if (input == "talents" || input == "Talents" || input == "TALENTS")
	{
		talents();
		system("cls");
		goto top;
	}
	//Used when removing an item from the inventory
	else if (input == "delete" || input == "Delete" || input == "DELETE")
	{
		//For every item
		for (int i = 1; i < numberOfItems; i++)
		{
			//If the array slot is greater than 1
			if (invSortPos[i] > 0)
				//Print the array slot nubmer and the item name
				printString("[" + to_string(i) + "] " + invItems[invSortPos[i]].name);
		}

		inputSign();
		cin >> secondInput;

		//Cleares the cin if input isn't numreric
		if (!cin)
		{
			cin.clear();
			string ignore;
			getline(cin, ignore);
			goto top;
		}

		//If input is between 0 and numberOfItems
		if (secondInput < numberOfItems && secondInput > 0)
		{
			//Check if selection is less than inventory items and item quantity is greater than 0 and is not equiped and also not a quest item
			if (secondInput < invSort && invItems[invSortPos[secondInput]].quantity > 0 && invSortPos[secondInput] != equipedWeapon && invItems[invSortPos[secondInput]].questItem == false)
			{
				printString(invItems[invSortPos[secondInput]].name + " has been removed successfully!");

				//Set the quantity to 0
				invItems[invSortPos[secondInput]].quantity = 0;

				//Call the function to update the array
				removeFromInvSortArray(secondInput);
			}
			else
			{
				printString("You can't delete your currently equipped weapon or quest items!");
			}
		}
		pause();
		goto top;
	}

	//Used for consuming an item
	else if (input == "use" || input == "Use" || input == "USE")
	{
		//For every item
		for (int i = 1; i < numberOfItems; i++)
		{
			//If the array slot is greater than 1
			if (invSortPos[i] > 0)
				//Print the array slot nubmer and the item name
				printString("[" + to_string(i) + "] " + invItems[invSortPos[i]].name);
		}
		inputSign();
		cin >> secondInput;
		//Cleares the cin if input isn't numreric
		if (!cin)
		{
			cin.clear();
			string ignore;
			getline(cin, ignore);
			goto top;
		}

		//Check if item is a consumable and that you are bellow max health
		if (invItems[invSortPos[secondInput]].consumable == true && playerHealth < playerMaxHealth)
		{
			//Set the quantity to the quantity - 1
			invItems[invSortPos[secondInput]].quantity--;

			//Add the health to the user from the item
			playerHealth = playerHealth + invItems[invSortPos[secondInput]].healthRegen;

			//If health goes above max health, set to max health
			if (playerHealth > playerMaxHealth)
				playerHealth = playerMaxHealth;

			//Tell the user how much the user was healed for
			if (invItems[invSortPos[secondInput]].healthRegen > 0)
				printString("You have been healed for " + to_string(invItems[invSortPos[secondInput]].healthRegen) + " healthpoints!");
			else if (invItems[invSortPos[secondInput]].healthRegen < 0)
				printString("You have been damaged for " + to_string(invItems[invSortPos[secondInput]].healthRegen) + " healthpoints!");

			printString("Current HP " + to_string(playerHealth) + "/" + to_string(playerMaxHealth));
		}
		//If item is a comsumable, but user health is full. Tell the user
		else if (invItems[invSortPos[secondInput]].consumable == true && playerHealth == playerMaxHealth)
		{
			printString("Your HP is full!");
		}
		//Otherwise print error
		else
		{
			printString("Item type is not consumable!");
		}

		pause();
		goto top;
	}

	//Used for leaving the inventory and does nothing
	else if (input == "back" || input == "Back" || input == "BACK")
	{
		if (talentOne == 0 || talentTwo == 0)
		{
			printString("Please select your talents before proceeding!");
			pause();
			drawInventory();
		}
	}

	//If input matched nothing, print error and return to top
	else
	{
		printString("Wrong input!");
		pause();
		goto top;
	}
}

//Function to add items to the player's inventory
/// <summary>Used to give items to the player
/// <para>Usage: grantItem(e.g 1, 12);</para>
/// </summary>
void grantItem(int itemID, int quantity)
{
	bool update = true;

	//Set item quantity to current quantity plus 1
	invItems[itemID].quantity = invItems[itemID].quantity + quantity;

	for (int i = 0; i < numberOfItems; i++)
	{
		if (invSortPos[i] == itemID)
			update = false;
	}
	if (update)
	{
		//Update array for inventory sortation
		invSortPos[invSort] = itemID;

		//Tell the program how many sorted values there is in total
		invSort++;
	}
}

void shop(int shopId)
{
	//Define variable types
	int priceCharCount, numDigitsGold, secondInput;
	string input, temp;

	//Define goto point
top:

	system("cls");
	cout << endl;

	//For every line in ascii art vector
	for (int i = 0; i < shopKeeper[shopId].numberOfAsciiLines; i++)
	{
		//Set temp to nothing in beginning of row
		temp = "";
		//For every character in row
		for (int n = 0; n < shopKeeper[shopId].numberofCharsPerLine; n++)
		{
			//Add that character to temp
			temp += shopKeeper[shopId].ascii.at(i).at(n);
		}
		//Print temp
		instantPrint(temp);
	}

	//Print shop name and some UI
	instantPrint(shopKeeper[shopId].name);
	instantPrint("\\\\--// -- -- -- -- -- -- -- -- -- -- -- -- \\\\--//  ");
	instantPrint("     ||   Name:                Price:           ||      ");

	//For every slot of item the vendor might have
	for (int n = 0; n <= 4; n++)
	{
		//If there's an item id stored in array print it
		if (shopKeeper[shopId].items[n] > 0)
		{
			//Get buy price length
			if (invItems[shopKeeper[shopId].items[n]].buyPrice > 99)
				priceCharCount = 3;
			else if (invItems[shopKeeper[shopId].items[n]].buyPrice > 9)
				priceCharCount = 2;
			else
				priceCharCount = 1;
			//Print item that is sold with price
			printStringColor(7, "  ||   ", invItems[shopKeeper[shopId].items[n]].inventoryColor, invItems[shopKeeper[shopId].items[n]].name + string(21 - invItems[shopKeeper[shopId].items[n]].name.length(), ' '), 6, to_string(invItems[shopKeeper[shopId].items[n]].buyPrice), 7, string(15 - priceCharCount, ' ') + "  ||    ", 7, "", true);
		}
	}
	instantPrint("//--\\\\ -- -- -- -- -- -- -- -- -- -- -- -- //--\\\\  ");

	//Get number of digits from gold
	if (playerGold > 999)
		numDigitsGold = 4;
	else if (playerGold > 99)
		numDigitsGold = 3;
	else if (playerGold > 9)
		numDigitsGold = 2;
	else
		numDigitsGold = 1;

	//Print current player gold
	printStringColor(7, string(40 - numDigitsGold, ' ') + "Gold: ", 6, to_string(playerGold), 7, "", 7, "", 7, "", true);

	//Print vendor greeting under the UI
	printString(shopKeeper[shopId].greeting);

	printString("'Buy', 'Sell', or 'Back'");

	inputSign();
	cin >> input;

	//If input is buy
	if (input == "buy" || input == "Buy" || input == "BUY")
	{
		//´For every item the vendor might sell
		for (int i = 0; i < 4; i++)
		{
			//If there's sn item id stored in array slot print the current i value and the name relating to item id
			if (shopKeeper[shopId].items[i] > 0)
			{
				printString("[" + to_string(i + 1) + "] " + invItems[shopKeeper[shopId].items[i]].name);
			}
		}

		inputSign();
		cin >> secondInput;

		//Cleares the cin if input isn't numreric
		if (!cin)
		{
			cin.clear();
			string ignore;
			getline(cin, ignore);
			goto top;
		}

		//If input is between 0 and numberOfItems
		if (secondInput < numberOfItems && secondInput > 0)
		{
			secondInput--;
			//Check if selection is less than inventory items and item quantity is greater than 0 and is not equiped and also not a quest item else tell the user he can't buy the item
			if (playerGold > invItems[shopKeeper[shopId].items[secondInput]].buyPrice)
			{
				//Set playerGold to playerGold - the buy price
				playerGold -= invItems[shopKeeper[shopId].items[secondInput]].buyPrice;

				//Give the item to the player using a function to also update the arrays used
				grantItem(shopKeeper[shopId].items[secondInput], 1);

				//Tell the user what he paid and what he got
				printStringColor(7, invItems[shopKeeper[shopId].items[secondInput]].name + " has been bought successfully for ", 6, to_string(invItems[shopKeeper[shopId].items[secondInput]].buyPrice), 7, " gold!", 7, "", 7, "", false);
			}
			else
			{
				printStringColor(7, "You don't have enough gold to buy this item! Price: ", 6, to_string(invItems[shopKeeper[shopId].items[secondInput]].buyPrice), 7, " your gold: ", 6, to_string(playerGold), 7, "", false);
			}
		}

		pause();
		goto top;
	}
	//If input is sell
	else if (input == "sell" || input == "Sell" || input == "SELL")
	{
		//For every item in inventory
		for (int i = 1; i <= invSort; i++)
		{
			//If the array slot is greater than 1
			if (invSortPos[i] > 0)
				//Print the array slot nubmer and the item name
				printStringColor(7, "[" + to_string(i) + "] " + invItems[invSortPos[i]].name + " sell price: ", 6, to_string(invItems[invSortPos[i]].buyPrice / 2), 7, "", 7, "", 7, "", false);
		}
		inputSign();
		cin >> secondInput;
		//Cleares the cin if input isn't numreric
		if (!cin)
		{
			cin.clear();
			string ignore;
			getline(cin, ignore);
			goto top;
		}

		//If input is between 0 and numberOfItems
		if (secondInput < numberOfItems && secondInput > 0)
		{
			//Check if selection is less than inventory items and item quantity is greater than 0 and is not equiped and also not a quest item
			if (secondInput < invSort && invItems[invSortPos[secondInput]].quantity > 0 && invSortPos[secondInput] != equipedWeapon && invItems[invSortPos[secondInput]].questItem == false)
			{
				printStringColor(7, invItems[invSortPos[secondInput]].name + " has been sold successfully for ", 6, to_string(invItems[invSortPos[secondInput]].buyPrice / 2), 7, " gold!", 7, "", 7, "", false);

				//Reducing quantity by one
				invItems[invSortPos[secondInput]].quantity -= - 1;

				//Sets player gold to current gold + plus the price of item / 2
				playerGold += invItems[invSortPos[secondInput]].buyPrice / 2;

				//Call the function to update the array
				removeFromInvSortArray(secondInput);
			}
			else
			{
				printString("You can't sell your currently equipped weapon or quest items!");
			}
		}
		pause();
		goto top;
	}
	//If input is back, just continue until the end of the function
	else if (input == "back" || input == "Back" || input == "BACK")
	{

	}
	else
	{
		printString("That is not a valid input!");
		pause();
		system("cls");
		goto top;
	}
}

//Used when removing an inventory item
void removeFromInvSortArray(int itemID)
{
	//For every spot in array that is larger than the removed one
	for (int i = itemID; i < numberOfItems + 1; i++)
	{
		//If it isn't the last slot in array set current slot to next slot
		if (i != numberOfItems - 1)
			invSortPos[i] = invSortPos[i + 1];
		else
		{
			invSortPos[numberOfItems - 1] = -1;
		}
	}
	//Tell the program there's one less sorted value
	invSort--;
}

void battle(int enemyType)
{
	//Define variable types
	string attack;
	int enemyAttackPower;
	bool ran = false, enemyCrit = false;

	//Set enemy health to their max in case the enemy was previously battled
	enemy[enemyType].health = enemy[enemyType].maxHealth;

	//While both the player and enemy are alive
	while (enemy[enemyType].health > 0 && playerHealth > 0)
	{
		system("cls");
		cout << endl;

		//Draws the UI where health is displayed as well as names
		printStringColor(7, "#--------------------------------#", 7, string(10, ' '), 7, "#--------------------------------#", 7, "", 7, "", true);
		printStringColor(7, "# -" + playerName + "-" + string(29 - playerName.length(), ' ') + "#", 7, string(10, ' '), 7, "# -" + enemy[enemyType].name + "-" + string(29 - enemy[enemyType].name.length(), ' ') + "#", 7, "", 7, "", true);
		printStringColor(7, "# ", 4, string(playerHealth, '#'), 7, string(playerMaxHealth - playerHealth, 'O') + string(31 - playerMaxHealth, ' ') + "#" + string(10, ' ') + "# ", 4, string(enemy[enemyType].health, '#'), 7, string(enemy[enemyType].maxHealth - enemy[enemyType].health, 'O') + string(21 - enemy[enemyType].maxHealth + 10, ' ') + "#", true);
		printStringColor(7, "#--------------------------------#", 7, string(10, ' '), 7, "#--------------------------------#", 7, "", 7, "", true);

		printString("Your turn!");
		instantPrint("Use 'attack', 'run', 'abilities' to decide your next move.");
		instantPrint("Misspelling will be punished!");
		inputSign();
		cin >> attack;

		//If input is attack
		if (attack == "attack" || attack == "Attack" || attack == "ATTACK")
		{
			//Wait for 0.5 seconds
			Sleep(500);

			//Generate a crit value
			attackPower = rand() % 10 + 1;

			//If crit value is even and greater or equal to 6 then increase the damage
			if (attackPower % 2 == 0 && attackPower >= 6)
			{
				//Set attackPower to equiped weapon damage + equiped weapon damage / 2 eg. 2 + 1 = 3
				attackPower = invItems[equipedWeapon].damage + invItems[equipedWeapon].damage / 2;
				printStringColor(4, "[Critical Hit!] ", 7, "You hit " + enemy[enemyType].name + " with ", 4, to_string(attackPower), 7, " of healthpoints!", 7, "", false);
			}
			//Or otherwise just do regular damage
			else
			{
				//Set attackPower to regular weapon damage
				attackPower = invItems[equipedWeapon].damage;
				printStringColor(7, "You hit " + enemy[enemyType].name + " with ", 4, to_string(attackPower), 7, " of healthpoints!", 7, "", 7, "", false);
			}

			//Remove the damage from the enemys health pool
			enemy[enemyType].health = enemy[enemyType].health - attackPower;

			//If enemy still has healthpoints left, print it's healthpoints
			if (enemy[enemyType].health > 0)
			{
				printStringColor(7, enemy[enemyType].name + " now has ", 4, to_string(enemy[enemyType].health), 7, " healthpoints left!", 7, "", 7, "", false);
			}
		}

		//If input is abilities
		else if (attack == "abilities" || attack == "Abilities" || attack == "ABILITIES")
		{
			//Call the function to select a ability based of talents
			abilities(playerClass);

			//Generate random value and check if greater or equal to 6
			if (rand() % 10 + 1 >= 6)
			{
				//Increase damage and healthPower by itself / 2
				attackPower += attackPower / 2;
				healPower += healPower / 2;

				//If ability has attackPower prints
				if (attackPower > 0)
				{
					printStringColor(4, "[Critical Hit!] ", 7, "You hit " + enemy[enemyType].name + " with " + talentUsed + " for ", 4, to_string(attackPower), 7, " healthpoints!", 7, "", false);
				}
				//If ability has healPower print
				if (healPower > 0)
				{
					printStringColor(4, "[Critical Hit!] ", 7, "You healed yourself with " + talentUsed + " for ", 4, to_string(healPower), 7, " of healthpoints!", 7, "", false);
				}
				//If ability has a healPower that's negative print that the player was damaged
				else if (healPower < 0)
				{
					printStringColor(4, "[Critical Hit!] ", 7, "You damage yourself for " + talentUsed + " for ", 4, to_string(healPower), 7, " healthpoints!", 7, "", false);
				}
			}

			//If not a crit do this
			else
			{
				//Print if ability has attackPower
				if (attackPower > 0)
				{
					printStringColor(7, "", 7, "You hit " + enemy[enemyType].name + " with " + talentUsed + " for ", 4, to_string(attackPower), 7, " healthpoints!", 7, "", false);
				}
				//Print if ability has healPower
				if (healPower > 0)
				{
					printStringColor(7, "", 7, "You healed yourself with " + talentUsed + " for ", 4, to_string(healPower), 7, " of healthpoints!", 7, "", false);
				}
				//Print if ability has negative healPower
				else if (healPower < 0)
				{
					printStringColor(7, "", 7, "You damage yourself for " + talentUsed + " for ", 4, to_string(healPower), 7, " healthpoints!", 7, "", false);
				}
			}

			//Set enemy health to enemty health - attackPower
			enemy[enemyType].health -= attackPower;

			//Set player healthpoints to player healthpoints + healpower
			playerHealth += healPower;

			//If health went above max health, set to max health
			if (playerHealth > playerMaxHealth)
				playerHealth = playerMaxHealth;

			//Reset attackPower and healPower values to 0
			attackPower = 0;
			healPower = 0;
		}

		//If input is run
		else if (attack == "run" || attack == "Run" || attack == "RUN")
		{
			//Set variable type and value of random
			int flee = rand() % 10 + 1;

			//If random is greater or equal to 5
			if (flee >= 5)
			{
				//Set bool ran to true to prevent XP gain later
				ran = true;
				//Set enemy health to 0
				enemy[enemyType].health = 0;
				//Break the while loop
				break;
			}
			//Print that the user didn't manage to run if random is less than 5
			else
			{
				printString("You did not manage to run!");
			}
		}

		//Wait for 0.5 seconds
		Sleep(500);

		//Generate crit chance for enemy
		enemyAttackPower = rand() % 10 + 1;

		//If enemyAttackPower is even and equa<l or greater than 8
		if (enemyAttackPower % 2 == 0 && enemyAttackPower >= 8)
		{
			//Set damage to damage + damage / 2
			enemyAttackPower += enemy[enemyType].damage / 2;

			//If the user didn't manage to flee and also enemy has more than 0 health
			if (ran == false && enemy[enemyType].health > 0)
				//Set bool enemy crit to true
				enemyCrit = true;
		}
		else
		{
			//Otherwise set damage to default enemy damage
			enemyAttackPower = enemy[enemyType].damage;
			//And bool enemy crit to false
			enemyCrit = false;
		}

		//If enemy isn't dead
		if (enemy[enemyType].health > 0)
		{
			//Set player health to player health - enemy damage
			playerHealth -= enemyAttackPower;
			//If it was a crit, print it otherwise just print damage
			if (enemyCrit)
			{
				//Print damage done if playerhealth is greater than 0
				if (playerHealth > 0)
					printStringColor(4, "[Critical Hit!] ", 7, enemy[enemyType].name + " hit you with ", 4, to_string(enemyAttackPower), 7, " of healthpoints!", 7, "", false);
			}
			else
			{
				printStringColor(7, enemy[enemyType].name + " hit you with ", 4, to_string(enemyAttackPower), 7, " of healthpoints!", 7, "", 7, "", false);
			}

			//Print player health if player health is greater than 0
			if (playerHealth > 0)
				printStringColor(7, "You now have ", 4, to_string(playerHealth), 7, " healthpoints!", 7, "", 7, "", false);
		}
		else
		{
			//If player didn't manage to run and enemy is dead
			if (ran == false)
			{
				//Set player xp to player xp + enemy xp reward and tell teh user
				playerExperience += enemy[enemyType].xpGain;
				printStringColor(7, enemy[enemyType].name + " successfully ", 4, "killed", 7, "! Which has granted you " + to_string(enemy[enemyType].xpGain) + " experience points!", 7, "", 7, "", false);

				//If enemy has drop specified
				if (enemy[enemyType].hasDrop)
				{
					//Generate random drop chance
					int dropChance = rand() % 10 + 1;

					//If dropchance is greater than 6
					if (dropChance > 6)
					{
						//Reward with 1 of potential loot and tell the user it was rare
						grantItem(enemy[enemyType].potentialLoot, 1);
						printString("Rare drop! You got a " + invItems[enemy[enemyType].potentialLoot].name);
					}

					//Give player the drop of the enemy times the drop amount and tell the user
					grantItem(enemy[enemyType].drop, enemy[enemyType].dropAmount);
					printString("You have been rewarded with " + to_string(enemy[enemyType].dropAmount) + " " + invItems[enemy[enemyType].drop].name);
				}

				//levelUpCheck();
			}
			else
			{
				//If you successfully ran print this
				printString("You have successfully ran away");
				pause();
			}
		}

		//If player health is less or equal 0 goto death function.
		if (playerHealth <= 0)
			death();

		pause();
	}
}

void abilities(int playerClass)
{
	int input;

	if (playerClass == 1)
	{
		printString("[1] " + classOneTalents[talentOne - 1] + " [2] " + classOneTalents[2 + talentTwo - 1]);
	}
	else if (playerClass == 2)
	{
		printString("[1] " + classTwoTalents[talentOne - 1] + " [2] " + classTwoTalents[2 + talentTwo - 1]);
	}
	else if (playerClass == 3)
	{
		printString("[1] " + classThreeTalents[talentOne - 1] + " [2] " + classThreeTalents[2 + talentTwo - 1]);
	}
	else
	{
		cout << "error" << endl;
		pause();
	}

	inputSign();
	cin >> input;

	switch (input)
	{
	case 1:
		if (playerClass == 1)
		{
			attackPower = classOneTalentsDamage[talentOne - 1];
			healPower = classOneTalentsRedDamage[talentOne - 1];
			talentUsed = classOneTalents[talentOne - 1];
		}
		else if (playerClass == 2)
		{
			attackPower = classTwoTalentsDamage[talentOne - 1];
			healPower = classTwoTalentsRedDamage[talentOne - 1];
			talentUsed = classTwoTalents[talentOne - 1];
		}
		else if (playerClass == 3)
		{
			attackPower = classThreeTalentsDamage[talentOne - 1];
			healPower = classThreeTalentsRedDamage[talentOne - 1];
			talentUsed = classThreeTalents[talentOne - 1];
		}
		break;
	case 2:
		if (playerClass == 1)
		{
			attackPower = classOneTalentsDamage[2 + talentTwo - 1];
			healPower = classOneTalentsRedDamage[2 + talentTwo - 1];
			talentUsed = classOneTalents[2 + talentTwo - 1];
		}
		else if (playerClass == 2)
		{
			attackPower = classTwoTalentsDamage[2 + talentTwo - 1];
			healPower = classTwoTalentsRedDamage[2 + talentTwo - 1];
			talentUsed = classTwoTalents[2 + talentTwo - 1];
		}
		else if (playerClass == 3)
		{
			attackPower = classThreeTalentsDamage[2 + talentTwo - 1];
			healPower = classThreeTalentsRedDamage[2 + talentTwo - 1];
			talentUsed = classThreeTalents[2 + talentTwo - 1];
		}
	}
}


void death()
{
	playerHealth = playerMaxHealth / 2;
	system("cls");

	instantPrint("                                           .\"\"--.._            ");
	instantPrint("                                           []      `'--.._       ");
	instantPrint("                                           ||__           `'-,   ");
	instantPrint("                                         `)||_ ```'--..       \\  ");
	instantPrint("                     _                    /|//}        ``--._  | ");
	instantPrint("                  .'` `'.                /////}              `\\/ ");
	instantPrint("                 /  .\"\"\".\\              //{///                ");
	instantPrint("                /  /_  _`\\\\            // `||                    ");
	instantPrint("                | |(_)(_)||          _//   ||                    ");
	instantPrint("                | |  /\\  )|        _///\\   ||                   ");
	instantPrint("                | |L====J |       / |/ |   ||                    ");
	instantPrint("               /  /'-..-' /    .'`  \\  |   ||                    ");
	instantPrint("              /   |  :: | |_.-`      |  \\  ||                    ");
	instantPrint("             /|   `\\-::.| |          \\   | ||                    ");
	instantPrint("           /` `|   /    | |          |   / ||                    ");
	instantPrint("         |`    \\   |    / /          \\  |  ||                    ");
	instantPrint("        |       `\\_|    |/      ,.__. \\ |  ||                    ");
	instantPrint("        /                     /`    `\\ ||  ||                    ");
	instantPrint("       |           .         /        \\||  ||                    ");
	instantPrint("       |                     |         |/  ||                    ");
	instantPrint("       /         /           |         (   ||                    ");
	instantPrint("      /          .           /          )  ||                    ");
	instantPrint("     |            \\          |             ||                    ");
	instantPrint("    /             |          /             ||                    ");
	instantPrint("   |\\            /          |              ||                    ");
	instantPrint("   \\ `-._       |           /              ||                    ");
	instantPrint("    \\ ,//`\\    /`           |              ||                    ");
	instantPrint("     ///\\  \\  |             \\              ||                    ");
	instantPrint("    |||| ) |__/             |              ||                    ");
	instantPrint("    |||| `.(                |              ||                    ");
	instantPrint("    `\\\\` /`                 /              ||                    ");
	instantPrint("       /`                   /              ||                    ");
	instantPrint("      /                     |              ||                    ");
	instantPrint("     |                      \\              ||                    ");
	instantPrint("    /                        |             ||                    ");
	instantPrint("  /`                          \\            ||                    ");
	instantPrint("/`                            |            ||                    ");
	instantPrint("`-.___,-.      .-.        ___,'            ||                    ");

	printString("You have died :(");
	pause();
	skanstull();
}

void levelUpCheck()
{
	while (playerExperience >= 500)
	{
		playerExperience = playerExperience - 500;
		playerLevel++;
		printString("Congratulations, you have reached level " + to_string(playerLevel) + "!");
		printString("Maximum HP has been increased from " + to_string(playerMaxHealth));
		playerMaxHealth = playerMaxHealth + 2;
		cout << " to " << playerMaxHealth << endl;
		printString("to " + to_string(playerMaxHealth));
	}
}

void printTalentUI(int firstTalent, int secondTalent, string talentNames[4])
{
	cout << endl;
	instantPrint("-V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V-");
	instantPrint("|                 Talents                 |");
	instantPrint("|                                         |");
	instantPrint("|-----------------------------------------|");
	if (firstTalent == 1)
		instantPrint("| [X][1] " + talentNames[0] + string(12 - talentNames[0].length(), ' ') + "[ ][2] " + talentNames[1] + string(14 - talentNames[1].length(), ' ') + "|");
	else if (firstTalent == 2)
		instantPrint("| [ ][1] " + talentNames[0] + string(12 - talentNames[0].length(), ' ') + "[X][2] " + talentNames[1] + string(14 - talentNames[1].length(), ' ') + "|");
	else
		instantPrint("| [ ][1] " + talentNames[0] + string(12 - talentNames[0].length(), ' ') + "[ ][2] " + talentNames[1] + string(14 - talentNames[1].length(), ' ') + "|");

	instantPrint("|-----------------------------------------|");

	if (secondTalent == 1)
		instantPrint("| [X][3] " + talentNames[2] + string(12 - talentNames[2].length(), ' ') + "[ ][4] " + talentNames[3] + string(14 - talentNames[3].length(), ' ') + "|");
	else if (secondTalent == 2)
		instantPrint("| [ ][3] " + talentNames[2] + string(12 - talentNames[2].length(), ' ') + "[X][4] " + talentNames[3] + string(14 - talentNames[3].length(), ' ') + "|");
	else
		instantPrint("| [ ][3] " + talentNames[2] + string(12 - talentNames[2].length(), ' ') + "[ ][4] " + talentNames[3] + string(14 - talentNames[3].length(), ' ') + "|");
	instantPrint("|                                         |");
	instantPrint("-v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v-");
}

void talents()
{
	string input, talentNames[4], talentDesc[12] = { "Consume a goodiebag, healing you.", "Swear at your foes, dealing damage.", "Deal damage, for the motherland!", "Fett me damage.", "Dance around your foes.", "Exactly what the name says.", "Drink some more.", "Fall on the grund.", "Rob an old lady.", "Deals INSANE damage to enemy.", "Call your 'brothers'.", "Deals massive amount of damage." };
	int secondInput, classNum;

top:

	switch (playerClass)
	{
	case 1:
		for (int i = 0; i < 4; i++)
		{
			talentNames[i] = classOneTalents[i];
		}
		classNum = 0;
		break;
	case 2:
		for (int i = 0; i < 4; i++)
		{
			talentNames[i] = classTwoTalents[i];
		}
		classNum = 4;
		break;
	case 3:
		for (int i = 0; i < 4; i++)
		{
			talentNames[i] = classThreeTalents[i];
		}
		classNum = 8;
		break;
	default:
		classMenu();
		goto top;
	}

	system("cls");

	printTalentUI(talentOne, talentTwo, talentNames);

	printString("'Select', 'Info', 'Back'");
	inputSign();
	cin >> input;

	if (input == "select" || input == "Select" || input == "SELECT")
	{
		for (int i = 0; i < 4; i++)
		{
			instantPrint("[" + to_string(i + 1) + "] " + talentNames[i]);
		}
		instantPrint("You may only select one talent per row!");
		instantPrint("Select one of the talents above to select:");

		inputSign();
		cin >> secondInput;

		if (!cin)
		{
			cin.clear();
			string remove;
			getline(cin, remove);
			talents();
		}

		switch (secondInput)
		{
		case 1:
			talentOne = 1;
			instantPrint(talentNames[0] + " has been selected successfully!");
			pause();
			goto top;
		case 2:
			talentOne = 2;
			instantPrint(talentNames[1] + " has been selected successfully!");
			pause();
			goto top;
		case 3:
			talentTwo = 1;
			instantPrint(talentNames[2] + " has been selected successfully!");
			pause();
			goto top;
		case 4:
			talentTwo = 2;
			instantPrint(talentNames[3] + " has been selected successfully!");
			pause();
			goto top;
		default:
			printString("Invalid input!");
			pause();
			system("cls");
			goto top;
		}
	}
	else if (input == "info" || input == "Info" || input == "INFO")
	{
		for (int i = 0; i < 4; i++)
		{
			printString("[" + to_string(i + 1) + "] " + talentNames[i]);
		}
		printString("Select one of the talents above to read info about:");
		inputSign();
		cin >> secondInput;
		switch (secondInput)
		{
		case 1:
			printString(talentNames[0] + ": " + talentDesc[classNum + 0]);
			pause();
			goto top;
			break;
		case 2:
			printString(talentNames[1] + ": " + talentDesc[classNum + 1]);
			pause();
			goto top;
			break;
		case 3:
			printString(talentNames[2] + ": " + talentDesc[classNum + 2]);
			pause();
			goto top;
			break;
		case 4:
			printString(talentNames[3] + ": " + talentDesc[classNum + 3]);
			pause();
			goto top;
			break;
		default:
			printString("Invalid input!");
			pause();
			system("cls");
			goto top;
		}
	}
	else if (input == "back" || input == "Back" || input == "BACK")
	{
		system("cls");
	}
	else
	{
		printString("That is not a valid option!");
		pause();
		system("cls");
		goto top;
	}
}

string genRandomString(int stringSize)
{
	char availChars[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	int stringLength = sizeof(availChars) - 1;

	char currentChar = availChars[rand() % stringLength];

	string currentString;

	while (currentString.length() != 10)
	{
		for (int i = 0; i < 10; i++)
		{
			if (currentString[i] == currentChar)
			{
				currentChar = availChars[rand() % stringLength];
			}
			else
			{
				currentString += currentChar;
				currentChar = availChars[rand() % stringLength];
			}
		}
	}

	return currentString;
}
void classPundare()
{
	cout << endl;
	printString("You wake up in the subway and don't remember anything.");
	printString("You think to yourself 'dang dawg that vape hit was radical.");
	printString("You look up and see a subwayguard charging at you.");
	printString("He swings a baton at you and you duckish (dodge) the baton.");
	pause();
	system("cls");
	cout << endl;
	fightPrint();
	pause();
	battle(0);
	system("cls");
	cout << endl;
	printString("After the fight you decide to go to Skanstull");
	pause();
	skanstull();
}

void classAlkis()
{
	cout << endl;
	printString("You wake up at Johnny's Pizzeria");
	printString("You have an intense headache ");
	printString("You order some adult potion ");
	printString("The bartender won't give you the potion");
	pause();
	system("cls");
	cout << endl;
	fightPrint();
	pause();
	battle(2);
	system("cls");
	cout << endl;
	printString("After the fight you decide to go to Skanstull");
	pause();
	skanstull();
}

void classGangster()
{
	cout << endl;
	printString("You decide to robbish (rob) an old lady on the subway.");
	printString("WALLA!");
	printString("It's not an old lady, it's Ken Bone.");
	printString("He flirts with you.");
	pause();
	system("cls");
	cout << endl;
	fightPrint();
	pause();
	battle(1);
	system("cls");
	cout << endl;
	printString("After the fight you decide to go to Skanstull");
	pause();
	skanstull();
}

void classCheck()
{
	if (playerName == "motherLoad")
	{
		grantItem(10, 1);
	}

	switch (playerClass)
	{
	case 1:
		classPundare();
		break;

	case 2:
		classAlkis();
		break;

	case 3:
		classGangster();
		break;

	default:
		void classMenu();
		break;
	}
}
void skanstull()
{
	int choice;
top:

	system("cls");

	cout << endl;
	instantPrint("    OO O o o o...      ______________________ _________________ ");
	instantPrint("   O     ____          |                    | |               | ");
	instantPrint("  ][_n_i_| (   ooo___  |     Skanstull      | |               | ");
	instantPrint(" (__________|_[______]_|____________________|_|_______________| ");
	instantPrint("   0--0--0      0  0      0       0     0        0        0     ");
	pause();
	system("cls");
	cout << endl;
	printString("Welcome to Skanstull(Your local train station)");
beenToRinkeby:
	printString("Where would you like to go?");

	if (invItems[9].quantity > 0)
		printString("[1] Go to NK(shop) [2] Go to Rinkeby [3] Go to TC [4] Go to Cigoteket at Torsgatan 36 [9] Open Inventory");
	else
		printString("[1] Go to NK(shop) [2] Go to Rinkeby [3] Go to TC [9] Open Inventory");

	inputSign();
	cin >> choice;
	switch (choice)
	{
	case 1:
		//NK shop
		NK();
		break;
	case 2:
		//Go to Rinkeby
		if (invItems[5].quantity > 0)
		{
			printString("Why would you go back to there? Pick another place to go to.");
			goto beenToRinkeby;
		}
		else
			rinkeby();

		break;
	case 3:
		//go to TC
		TC();
		goto top;
		break;
	case 4:
		if (invItems[9].quantity > 0)
			cigoteket();
		else
		{
			printString("Wrong input!");
			pause();
			goto top;
		}
		break;
	case 9:
		drawInventory();
		goto top;
		break;
	default:
		printString("Wrong input!");
		pause();
		goto top;

	}

}
void NK()
{
	shop(1);
	system("cls");
	cout << endl;
	printString("You decide to return to Skanstull.");
	pause();
	skanstull();
}
void rinkeby()
{
	int choice;

	system("cls");
	cout << endl;
	printString("Welcome to Rinkeby!");
	printString("As you walk out of the subway a strange man starts approaching you. ");
	printString("(Strange man) Hey my dude!");
	printString("You have no idea who this man is but you play along to not appear rude.");
	printString("After a while the strange man offers you some good good (Candy)");
	printString("Do you take the good good from the strange man?");
top:
	printString("[1] Take the good good from the man.");
	printString("[2] Don't take the candy from the strange man.");
	inputSign();
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		cout << endl;
		printString("(Strange man) Hey! what are you doing! That's my good good!");
		pause();
		system("cls");
		cout << endl;
		fightPrint();
		pause();
		battle(3);
		system("cls");
		cout << endl;
		printString("After the fight you jump on the first subway back to Skanstull,");
		printString("because why would you stay in Rinkeby?");
		pause();
		skanstull();
		break;
	case 2:
		system("cls");
		cout << endl;
		printString("(Strange man) You can't refuse a gift from a kind man like me!");
		pause();
		system("cls");
		cout << endl;
		fightPrint();
		pause();
		battle(3);
		system("cls");
		cout << endl;
		printString("After the fight you jump on the first subway back to Skanstull,");
		printString("because why would you stay in Rinkeby?");
		pause();
		skanstull();
		break;
	default:
		printString("Wrong input!");
		pause();
		system("cls");
		goto top;
	}
}
void TC()
{
	int choice;
	system("cls");

	cout << endl;
	instantPrint("    OO O o o o...      ______________________ _________________ ");
	instantPrint("   O     ____          |                    | |               | ");
	instantPrint("  ][_n_i_| (   ooo___  |         TC         | |               | ");
	instantPrint(" (__________|_[______]_|____________________|_|_______________| ");
	instantPrint("   0--0--0      0  0      0       0     0        0        0     ");
	pause();
	system("cls");
	cout << endl;
	printString("Welcome to TC!");
	printString("When you get up out of the subway you see a shady guys that looks interesting,");
	printString("You also see your favourite foodplace Burger King. ");
wrongInput:
	printString("What would you like to do?");
	if (invItems[9].quantity > 0)
		printString("[1] Go back to Skanstull [2] Go get some burgers ");
	else
		printString("[1] Go back to Skanstull [2] Go get some burgers [3] Talk to the shady guy");
	inputSign();
	cin >> choice;
	switch (choice)
	{
	case 1:
		skanstull();
		break;
	case 2:
		burgerKing();
		break;
	case 3:
		if (invItems[9].quantity > 0)
		{
			printString("Invalid choice!");
			pause();
			TC();
		}
		int secondChoice;
		system("cls");
		cout << endl;
		printString("As you walk up to the shady guy he looks at you with a scary smile and asks ");
		printString("'Do you want to know where Akash the vapelord is at?'");
		printString("I have some spicy info that you might like.");
		printString("'It will only cost you 5 gold'");
		printString("Do you buy the 'Spicy info' from the shady guy? ");
		printString("[1] Yes. [2] No.");
		inputSign();
		cin >> secondChoice;
		switch (secondChoice)
		{

		case 1:
			if (playerGold >= 5)
			{
				playerGold -= 5;
				grantItem(9, 1);
				printString("Thank you my man");
			}
			else
				printString("It looks like you do not have enough gold.");
			printString("Ohh well, you can have it anyway.");
			grantItem(9, 1);
			printString("You got item " + invItems[9].name);
			pause();
			goto wrongInput;
			break;
		case 2:
			printString("'JUST TAKE THE GODDAMN INFO!'");
			grantItem(9, 1);
			printString("You got item " + invItems[9].name);
			printString("You run back to TC subway and get on the next train back to Skanstull.");
			skanstull();
			break;
		default:
			break;
		}

		break;


	default:
		printString("That is not an option!");
		goto wrongInput;
		break;
	}
}

void burgerKing()
{
	shop(0);
	system("cls");
	cout << endl;
	printString("After that amazing food you decide to go back to TC");
	TC();

}
void fightPrint()
{

	printStringColor(7, "*|", 4, "    _______       __    __ ", 7, "|*", 7, "", 7, "", true);
	printStringColor(7, "*|", 4, "   / ____(_)___ _/ /_  / /_", 7, "|*", 7, "", 7, "", true);
	printStringColor(7, "*|", 4, "  / /_  / / __ `/ __ \\/ __/", 7, "|*", 7, "", 7, "", true);
	printStringColor(7, "*|", 4, " / __/ / / /_/ / / / / /_  ", 7, "|*", 7, "", 7, "", true);
	printStringColor(7, "*|", 4, "/_/   /_/\\__, /_/ /_/\\__/  ", 7, "|*", 7, "", 7, "", true);
	printStringColor(7, "*|", 4, "        /____/             ", 7, "|*", 7, "", 7, "", true);
	instantPrint("*******************************");
}
void cigoteket()
{
	printString("When you stand outside the Cigotek you see Akash inside ripping the fattest vape.");
	printString("suddenly he notices you!");
	printString("'HEY! WHAT ARE YOU DOING HERE!'");
	printString("'You shouldn't be here, this is my secret hideout.'");
	printString("'You wont get away with this easily'");
	pause();
	fightPrint();
	battle(4);
	system("cls");
	cout << endl;
	printString("After the fight you decide to check out what the key Akash dropped leads to.");
	printString("As you touch the key you hear in a distance:");
	printString("I got the key, the keys, the keys.");
	printString("I got the key, the keys, the keys.");
	printString("Suddenly, a fat man jumps out of the bushes.");
	printString("He starts talking in a language that sounds like english but not exactly.");
	printString("As you get a closer look at the man you see that its,");
	printString("DJ KHAAALEEEED!");
	printString("Dj Khaled runs towards you and yells 'GIVE ME MY KEY!'.");
	pause();
	fightPrint();
	pause();
	battle(5);
}
