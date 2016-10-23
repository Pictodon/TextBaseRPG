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

//Global vars
//Vars used for loading
bool firstInvLoad = true;
int winHeight = 0;
int winWide = 0;
//Inventory related vars
int numberOfItems = 11;
int invSort = 1;
int equipedWeapon = 1;
int invSortPos[11];
int defaultColor = 7;
//Player related vars
string playerName = "";
int playerClass = 0;
int playerGold = 0;
int playerLevel = 1;
int playerExperience = 0;
int playerMaxHealth = 10;
int playerHealth = playerMaxHealth;

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
} invItems[11];

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

struct shopKeepers {
	string name;
	string greeting;
	int items[5];
	vector<string> ascii;
	int numberOfAsciiLines = 0;
	int numberofCharsPerLine = 0;
} shopKeeper[10];

//Main
void main()
{
	//Assign name and info for every item in the game
	invItems[4].name = "Bottle"; invItems[4].quantity = 1; invItems[4].quality = "Legendary"; invItems[4].levelRequirement = 3; invItems[4].buyPrice = 13;
	invItems[6].name = "Gucci belt"; invItems[6].quantity = 0; invItems[6].quality = "Rare"; invItems[6].buyPrice = 100; invItems[6].weapon = true; invItems[6].damage = 5; invItems[6].desc = "Expensive shit";
	invItems[5].name = "asdsdadsad"; invItems[5].quantity = 1; invItems[5].quality = "Common"; invItems[5].buyPrice = 20;
	invItems[7].name = "Strange man's knife "; invItems[7].quantity = 0; invItems[7].quality = "Rare"; invItems[7].buyPrice = 50; invItems[7].weapon = true; invItems[7].levelRequirement = 2; invItems[7].damage = 3;
	invItems[3].name = "Katana"; invItems[3].quantity = 1; invItems[3].quality = "Rare"; invItems[3].weapon = true; invItems[3].inventoryColor = 16; invItems[3].levelRequirement = 2; invItems[3].buyPrice = 20;
	invItems[1].name = "Stick"; invItems[1].quantity = 1; invItems[1].quality = "Common"; invItems[1].weapon = true; invItems[1].buyPrice = 1; invItems[1].type = "Weapon"; invItems[1].damage = 2; invItems[1].desc = "Just a stick";
	invItems[2].name = "Health potion"; invItems[2].quantity = 0; invItems[2].quality = "Uncommon"; invItems[2].consumable = true; invItems[2].buyPrice = 10; invItems[2].healthRegen = 5; invItems[2].desc = "Heals for 5 HP when used";
	invItems[8].name = "The Key"; invItems[8].quantity = 0; invItems[8].quality = "Legendary"; invItems[8].inventoryColor = 16; invItems[8].levelRequirement = 2; invItems[8].questItem = true;
	invItems[9].name = "Akash's location"; invItems[9].quantity = 0; invItems[9].quality = "Rare"; invItems[9].questItem = true;
	invItems[10].name = "Dank Kush"; invItems[10].quantity = 0; invItems[10].buyPrice = 2674; invItems[10].quality = "DANK"; invItems[10].inventoryColor = 16;
	invItems[5].name = "Good Good"; invItems[5].quantity = 0; invItems[5].quality = "Rare"; invItems[5].buyPrice = 50; invItems[5].consumable = true; invItems[5].healthRegen = playerMaxHealth; 
	//MOBS
	enemy[0].health = 10; enemy[0].name = "Subwayguard"; enemy[0].damage = 1; enemy[0].xpGain = 100, enemy[0].maxHealth = 10; enemy[0].drop = 2; enemy[0].hasDrop = true; enemy[0].dropAmount = 1; enemy[0].potentialLoot = 2;
	enemy[1].health = 11; enemy[1].name = "Ken Bone"; enemy[1].damage = 1; enemy[1].xpGain = 100, enemy[1].maxHealth = 11; enemy[1].drop = 2; enemy[1].hasDrop = true; enemy[1].dropAmount = 1; enemy[1].potentialLoot = 2;
	enemy[2].health = 10; enemy[2].name = "Bartender"; enemy[2].damage = 1; enemy[2].xpGain = 100, enemy[2].maxHealth = 10; enemy[2].drop = 2; enemy[2].hasDrop = true; enemy[2].dropAmount = 1; enemy[2].potentialLoot = 2;
	enemy[3].health = 17; enemy[3].name = "Strange man"; enemy[3].damage = 2; enemy[3].xpGain = 300, enemy[3].maxHealth = 17; enemy[3].drop = 5; enemy[3].hasDrop = true; enemy[3].dropAmount = 2; enemy[3].potentialLoot = 7;
	//ShopKeepers
	shopKeeper[0].name = "Oskar"; shopKeeper[0].greeting = "Hello, newfag"; shopKeeper[0].items[0] = 4; shopKeeper[0].items[1] = 6; shopKeeper[0].items[2] = 7;
	shopKeeper[1].name = "NK"; shopKeeper[1].greeting = "Hello, welcome to expensiveShop.exe"; shopKeeper[1].items[0] = 4; shopKeeper[1].items[1] = 6; shopKeeper[1].items[2] = 2; shopKeeper[1].ascii = { ".ssssssssssssssssssssssssssssssssssssss.",	"-m+......-ohmho+:--hd--:+shmh+-....../m-",	"-m:    :yho-`      hh      `:ods-    :m-",	"-m:  :hmm.         hh         `:hh-  :m-",	"-m:`yd:dmh`        hh           -dms`:m-", "-m+dy` dhmo        hh        .+hy:.hh/m-",	"-mmy`  ds/m:       hh     `/yh+.   `hmm-",	"-md.   ds sd.      hh   -sds-       -mm-",	"-mo    ds `hy`     hh.+hy/`          ym-",	"-m/    ds  .mo     hmhdh-            +m-",	"-m/    ds   /m:    hh  /ds.          +m-",	"-ms    ds    sd.   hh   `+do`        ym-",	"-mm.   ds    `hy   hh     `od+`     -mm-",	"-mmy`  ds     -mo  hh       .sd/   `hdm-",	"-m+hy` ds      /m: hh         -yh:.hy/m-",	"-m:`sd/ds       sd.hh           :mmo`:m-",	"-m:  :hmy`      `hyhh         `/hy-  :m-",	"-m:    :sdo:`    -mmh      `:sds-    :m-",	"-m/......-+ydhs+/:smd-:/osddy/......./m-",	".ssssssssssssssssssssssssssssssssssssss." }; shopKeeper[1].numberOfAsciiLines = 20; shopKeeper[1].numberofCharsPerLine = 40;

	asignDefaultRarityColor();

	choseFontSize();

	//Set console to be fulscreen
	system("mode 1000");

	screenResolution();

	//Tell the compiler what number to base rand(); of
	srand(time(NULL));

	drawInventory();

	nameGreeting();

	classMenu();

	//Random shiz
	drawInventory();

	shop(0);

	drawInventory();
}

void nameGreeting()
{
	//Call the function to print text
	cout << endl;
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
		printString("Oh so you're a hunter type. ");
		printString("This class is especially good when you want to attack at a long range.");
		printString("You have a really powerful arrow that you can fire at your enemy. ");
		printString("If you are easily scared by monsters then this is the class for you. ");

		break;
	case 2:
		//not sure vad jag har skrivit xD
		printString("If you have less than 10 braincells then this is the class for you. ");
		printString("I mean who would choose a class that just runs in to battle with their");
		printString("head first. The smartest class would be hunter, but nevermind. ");
		printString("With the warrior class you can slash your baws ass sword at your enemies.");
		printString("Just look at He-Man, he's the boss.");
		break;
	case 3:
		printString("VIKTOR SKRIVER");
		printString("VIKTOR SKRIVER");
		printString("VIKTOR SKRIVER");
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
		pause();
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

void choseFontSize()
{
	do {
		system("cls");
		cout << "If you want to change the font size, do so now.\nPress 1 to proceed." << endl;
	} while (_getch() != '1');
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

	//Set color to color if int isn't 16 = rainbow
	if (color == 16)
	{
		isRainbow = true;
	}
	else
	{
		setTextColor(color);
		isRainbow = false;
	}

	//For every letter in string do this
	for (int i = 0; i < stringInput.length(); i++)
	{
		//If isRainbow is true change color for each character
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
	}

	//Set color to color if int isn't 16 = rainbow
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
		//If isRainbow is true change color for each character
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
	}

	//Set color to color if int isn't 16 = rainbow
	if (color3 == 16)
	{
		isRainbow = true;
	}
	else
	{
		setTextColor(color3);
		isRainbow = false;
	}

	//Set color to color if int isn't 16 = rainbow
	for (int i = 0; i < stringInput3.length(); i++)
	{
		//If isRainbow is true change color for each character
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
		//Add a delay between each character if wanted
		if (instant == false)
			Sleep(30);
	}

	//Set color to color
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
		//If isRainbow is true change color for each character
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
		//If isRainbow is true change color for each character
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
	}

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
	int spacing = winWide / 2 - stringInput.length() / 2;
	cout << string(spacing, ' ');

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

	//Add some spaces
	cout << endl << endl << endl << endl;
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

			//Check item quality and set color to the right quality color with the printStringColor(7, "", 7, "", 7, "", 7, "", false); function
			//If no quality matched, make default color
			if (invItems[i].weapon == false)
				printStringColor(7, "  | " + to_string(invItems[i].quantity) + "x ", invItems[i].inventoryColor, invItems[i].name, levelReqColor, string(29 - to_string(invItems[i].quantity).length() - invItems[i].name.length() - levelReqText.length(), ' ') + levelReqText, 7, " |  ", 7, "", true);
			else
				printStringColor(7, "  | ", invItems[i].inventoryColor, invItems[i].name, levelReqColor, string(31 - invItems[i].name.length() - levelReqText.length(), ' ') + levelReqText, 7, " |  ", 7, "", true);

			printStringColor(7, "  | ", invItems[i].inventoryColor, invItems[i].quality, 7, " (" + invItems[i].type + ")" + string(19 - invItems[i].type.length() - invItems[i].quality.length() - to_string(invItems[i].damage).length(), ' ') + " Damage: ", 4, to_string(invItems[i].damage), 7, " |  ", true);
			instantPrint("  | " + invItems[i].desc + string(31 - invItems[i].desc.length(), ' ') + " |  ");
			instantPrint("  |---------------------------------|  ");
		}
	}
	//Set the firstInLoad to false to prevent items being added twice to array earlier in code
	firstInvLoad = false;

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
			if (secondInput < invSort && invItems[invSortPos[secondInput]].quantity > 0 && secondInput != equipedWeapon && invItems[invSortPos[secondInput]].questItem == false)
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
			printString("You have been healed for " + to_string(invItems[invSortPos[secondInput]].healthRegen) + " health points!");

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
	int priceCharCount, numDigitsGold, secondInput;

	string input, temp;

top:

	system("cls");
	cout << endl;

	for (int i = 0; i < shopKeeper[shopId].numberOfAsciiLines; i++)
	{
		temp = "";
		for (int n = 0; n < shopKeeper[shopId].numberofCharsPerLine; n++)
		{
			temp += shopKeeper[shopId].ascii.at(i).at(n);
		}
		instantPrint(temp);
	}

	instantPrint(shopKeeper[shopId].name);
	instantPrint("\\\\--// -- -- -- -- -- -- -- -- -- -- -- -- \\\\--//  ");
	instantPrint("     ||  Name:                Price:            ||      ");

	for (int n = 0; n <= 4; n++)
	{
		if (shopKeeper[shopId].items[n] > 0)
		{
			if (invItems[shopKeeper[shopId].items[n]].buyPrice > 99)
				priceCharCount = 3;
			else if (invItems[shopKeeper[shopId].items[n]].buyPrice > 9)
				priceCharCount = 2;
			else
				priceCharCount = 1;
			printStringColor(7, "  ||   ", invItems[shopKeeper[shopId].items[n]].inventoryColor, invItems[shopKeeper[shopId].items[n]].name + string(21 - invItems[shopKeeper[shopId].items[n]].name.length(), ' '), 6, to_string(invItems[shopKeeper[shopId].items[n]].buyPrice), 7, string(15 - priceCharCount, ' ') + "  ||    ", 7, "", true);
		}
	}
	instantPrint("//--\\\\ -- -- -- -- -- -- -- -- -- -- -- -- //--\\\\  ");

	if (playerGold > 999)
		numDigitsGold = 4;
	else if (playerGold > 99)
		numDigitsGold = 3;
	else if (playerGold > 9)
		numDigitsGold = 2;
	else
		numDigitsGold = 1;

	printStringColor(7, string(40 - numDigitsGold, ' ') + "Gold: ", 6, to_string(playerGold), 7, "", 7, "", 7, "", true);
	printString(shopKeeper[shopId].greeting);

	printString("'Buy', 'Sell', or 'Back'");

	inputSign();
	cin >> input;

	if (input == "buy" || input == "Buy" || input == "BUY")
	{
		for (int i = 0; i < 5; i++)
		{
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
			//Check if selection is less than inventory items and item quantity is greater than 0 and is not equiped and also not a quest item
			if (playerGold > invItems[shopKeeper[shopId].items[secondInput]].buyPrice)
			{
				playerGold = playerGold - invItems[shopKeeper[shopId].items[secondInput]].buyPrice;

				grantItem(shopKeeper[shopId].items[secondInput], 1);

				printString(invItems[shopKeeper[shopId].items[secondInput]].name + " has been bought successfully!");
			}
			else
			{
				printStringColor(7, "You don't have enough gold to buy this item! Price: ", 6, to_string(invItems[shopKeeper[shopId].items[secondInput]].buyPrice), 7, " your gold: ", 6, to_string(playerGold), 7, "", false);
			}
		}

		pause();
		goto top;
	}
	else if (input == "sell" || input == "Sell" || input == "SELL")
	{
		//For every item
		for (int i = 1; i <= invSort; i++)
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
			if (secondInput < invSort && invItems[invSortPos[secondInput]].quantity > 0 && secondInput != equipedWeapon && invItems[invSortPos[secondInput]].questItem == false)
			{
				printString(invItems[invSortPos[secondInput]].name + " has been sold successfully!");

				//Reducing quantity by one
				invItems[invSortPos[secondInput]].quantity = invItems[invSortPos[secondInput]].quantity - 1;

				//Sets player gold to current gold + plus the price of item / 2
				playerGold = playerGold + invItems[invSortPos[secondInput]].buyPrice / 2;

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
			invSortPos[numberOfItems - 1] = - 1;
		}
	}
	//Tell the program there's one less sorted value
	invSort--;
}

void battle(int enemyType)
{
	string attack;
	int attackPower, enemyAttackPower;
	bool ran = false, enemyCrit = false;
	enemy[enemyType].health = enemy[enemyType].maxHealth;
	while (enemy[enemyType].health > 0 && playerHealth > 0)
	{
		system("cls");
		cout << endl;

		printStringColor(7, "#--------------------------------#", 7, string(10, ' '), 7, "#--------------------------------#", 7, "", 7, "", true);
		printStringColor(7, "# -" + playerName + "-" + string(29 - playerName.length(), ' ') + "#", 7, string(10, ' '), 7, "# -" + enemy[enemyType].name + "-" + string(29 - enemy[enemyType].name.length(), ' ') + "#", 7, "", 7, "", true);
		printStringColor(7, "# ", 4, string(playerHealth, '#'), 7, string(playerMaxHealth - playerHealth, 'O') + string(31 - playerMaxHealth, ' ') + "#" + string(10, ' ') + "# ", 4, string(enemy[enemyType].health, '#'), 7, string(enemy[enemyType].maxHealth - enemy[enemyType].health, 'O') + string(21 - enemy[enemyType].maxHealth + 10, ' ') + "#", true);
		printStringColor(7, "#--------------------------------#", 7, string(10, ' '), 7, "#--------------------------------#", 7, "", 7, "", true);
		//"# -" << playerName << "-" << string(29 - playerName.length(), ' ') << "#"

		printString("Your turn!"); 
		instantPrint("Use 'attack', 'run', 'block' to decide your next move.");
		inputSign();
		cin >> attack;

		if (attack == "attack" || attack == "Attack" || attack == "ATTACK")
		{
			Sleep(500);
			attackPower = rand() % 10 + 1;
			if (attackPower % 2 == 0 && attackPower >= 6)
			{
				attackPower = invItems[equipedWeapon].damage + invItems[equipedWeapon].damage / 2;
				printStringColor(4, "[Critical Hit!] ", 7, "You hit " + enemy[enemyType].name + " with ", 4, to_string(attackPower), 7, " of healthpoints!", 7, "", false);
			}
			else
			{
				attackPower = invItems[equipedWeapon].damage;
				printStringColor(7, "You hit " + enemy[enemyType].name + " with ", 4, to_string(attackPower), 7, " of healthpoints!", 7, "", 7, "", false);
			}
			enemy[enemyType].health = enemy[enemyType].health - attackPower;
			if (enemy[enemyType].health > 0)
			{
				printStringColor(7, enemy[enemyType].name + " now has ", 4, to_string(enemy[enemyType].health), 7, " healthpoints left!", 7, "", 7, "", false);
			}
		}
		else if (attack == "run" || attack == "Run" || attack == "RUN")
		{
			int flee = rand() % 10 + 1;
			if (flee > 5)
			{
				ran = true;
				enemy[enemyType].health = 0;
				break;
			}
			else
			{
				printString("You did not manage to run!");
			}
		}

		Sleep(500);

		enemyAttackPower = rand() % 10 + 1;

		if (enemyAttackPower % 2 == 0 && enemyAttackPower >= 8)
		{
			enemyAttackPower = enemy[enemyType].damage + enemy[enemyType].damage / 2;
			if (ran == false && enemy[enemyType].health > 0)
			enemyCrit = true;
		}
		else
		{
			enemyAttackPower = enemy[enemyType].damage;
			enemyCrit = false;
		}

		if (enemy[enemyType].health > 0)
		{
			playerHealth = playerHealth - enemyAttackPower;
			if (enemyCrit)
			{
				printStringColor(4, "[Critical Hit!] ", 7, enemy[enemyType].name + " hit you with ", 4, to_string(enemyAttackPower), 7, " of healthpoints!", 7, "", false);
			}
			else
			{
				printStringColor(7, enemy[enemyType].name + " hit you with ", 4, to_string(enemyAttackPower), 7, " of healthpoints!", 7, "", 7, "", false);
			}

			printStringColor(7, "You now have ", 4, to_string(playerHealth), 7, " healthpoints!", 7, "", 7, "", false);
		}
		else
		{
			if (ran == false)
			{
				playerExperience = playerExperience + enemy[enemyType].xpGain;
				printStringColor(7, enemy[enemyType].name + " successfully ", 4, "killed", 7, "! Which has granted you " + to_string(enemy[enemyType].xpGain) + " experience points!", 7, "", 7, "", false);

				if (enemy[enemyType].hasDrop)
				{
					int dropChance = rand() % 10 + 1;
					if (dropChance > 6)
					{
						invItems[enemy[enemyType].potentialLoot].quantity++;
						printString("Rare drop! You got a " + invItems[enemy[enemyType].potentialLoot].name);
					}
					invItems[enemy[enemyType].drop].quantity = invItems[enemy[enemyType].drop].quantity + enemy[enemyType].dropAmount;
					printString("You have been rewarded with " + to_string(enemy[enemyType].dropAmount) + " " + invItems[enemy[enemyType].drop].name);
				}

				//levelUpCheck();
			}
			else
			{
				printString("You have successfully ran away");
				pause();
			}
		}

		if (playerHealth <= 0)
			death();

		pause();
	}
}

void death()
{
	playerHealth = playerMaxHealth / 2;
	system("cls");
	printString("You have died :(");
	printString("Press any key to respawn.");
	pause();
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
		printString(" to " + to_string(playerMaxHealth));
	}
}

void printTalentUI(int firstTalent, int secondTalent, string talentNames[4])
{
	instantPrint("-V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V^V-");
	instantPrint("|                 Talents                 |");
	instantPrint("|                                         |");
	instantPrint("|    [1] " + talentNames[0] + string(12 - talentNames[0].length(), ' ') + "[2] " + talentNames[1] + string(17 - talentNames[1].length(), ' ') + "|");
	instantPrint("|    [3] " + talentNames[2] + string(12 - talentNames[2].length(), ' ') + "[4] " + talentNames[3] + string(17 - talentNames[3].length(), ' ') + "|");
	instantPrint("|                                         |");
	instantPrint("-v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v-");
}

void talents()
{

	int talentOne = 0, talentTwo = 0, secondInput;

	string input, talentNames[4], classOneTalents[4] = { "Vit", "makt", ",", "negerslakt" }, classTwoTalents[4] = { "dsada", "das", "dasdsa", "asd" }, classThreeTalents[4] = { "23d", "23d", "32d", "32d" };

top:

	switch (playerClass)
	{
	case 1:
		for (int i = 0; i < 4; i++)
		{
			talentNames[i] = classOneTalents[i];
		}
		break;
	case 2:
		for (int i = 0; i < 4; i++)
		{
			talentNames[i] = classTwoTalents[i];
		}
		break;
	case 3:
		for (int i = 0; i < 4; i++)
		{
			talentNames[i] = classThreeTalents[i];
		}
		break;
	default:
		classMenu();
		goto top;
	}

	system("cls");

	printTalentUI(talentOne, talentTwo, talentNames);

	printString("'select', 'info', 'back'");
	inputSign();
	cin >> input;

	if (input == "select" || input == "Select" || input == "SELECT")
	{
		for (int i = 0; i < 4; i++)
		{
			printString("[" + to_string(i + 1) + "] " + talentNames[i]);
		}
		printString("Select one of the talents above to select:");

		inputSign();
		cin >> secondInput;
		switch (secondInput)
		{
		case 1:
			talentOne = 1;
			printString(talentNames[0] + " has been selected successfully!");
			pause();
			goto top;
		case 2:
			talentTwo = 2;
			printString(talentNames[1] + " has been selected successfully!");
			pause();
			goto top;
		case 3:
			talentTwo = 3;
			printString(talentNames[2] + " has been selected successfully!");
			pause();
			goto top;
		case 4:
			talentTwo = 1;
			printString(talentNames[3] + " has been selected successfully!");
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
		printString("Select one of the talents above to select:");

		switch (secondInput)
		{
		case 1:
			printString(talentNames[0] + " has been selected successfully!");
			pause();
			goto top;
			break;
		case 2:
			printString(talentNames[1] + " has been selected successfully!");
			pause();
			goto top;
			break;
		case 3:
			printString(talentNames[2] + " has been selected successfully!");
			pause();
			goto top;
			break;
		case 4:
			printString(talentNames[4] + " has been selected successfully!");
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
	printString("FIGHT!");
	pause();
	battle(0);
	system("cls");
	cout << endl;
	printString("Let's check out your inventory");
	pause();
	drawInventory();
	system("cls");
	cout << endl;
	printString("After the fight you decide to go to skanstull");
	pause();
	skanstull();
}

void classAlkis()
{
	cout << endl;
	printString("You wake up at Johnny's Pizzeria");
	printString("You have a intense headache ");
	printString("You order some adult potion ");
	printString("The bartender won't give you the potion");
	pause();
	system("cls");
	cout << endl;
	printString("FIGHT!");
	pause();
	battle(2);
	system("cls");
	cout << endl;
	printString("Let's check out your inventory");
	pause();
	drawInventory();
	system("cls");
	cout << endl;
	printString("After the fight you decide to go to skanstull");
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
	printString("FIGHT");
	pause();
	//battle(1);
	system("cls");
	cout << endl;
	printString("Let's check out your inventory");
	pause();
	drawInventory();
	system("cls");
	cout << endl;
	printString("After the fight you decide to go to skanstull");
	pause();
	skanstull();
}

void classCheck()
{
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
	grantItem(10, 1);
	system("cls");
	cout << endl;
	printString("Welcome to Skanstull(Your local train station)");
	printString("Where would you like to go?");
	printString("[1] Go to NK(shop) [2] Go to Rinkeby [3] Go to TC");
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
		drawInventory();
		break;
	case 3:
		//go to TC
		break;
	case 4:
		if (invItems[2].quantity > 0)
			cout << endl;
			printString("Travel to Cigoteket at Torsgatan 36?");
		printString("Yes");
		printString("No");
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
	printString("Welcome to Rinkeby");
	printString("As you walk out of the subway a strange man starts aproacing you. ");
	printString("Hey my dude! (Strange man)");
	printString("You have no idea who this man is but you play along just to not seem rude.");
	printString("After a while the strange man offers you some good good (Candy)");
	printString("Do you take the good good from the strange man?");
	pause();
top:
	printString("[1] Take the good good from the man.");
	printString("[2] Don't take the candy from the strange man.");
	inputSign();
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		printString("Hey! what are you doing! That's my good good! (Strange man)");
		pause();
		system("cls");
		printString("FIGHT!");
		pause();
		battle(7);
		system("cls");
		printString("After the fight you jump on the first subway back to Skanstull, because why would you stay in Rinkeby?");
		pause();
		skanstull();
		break;
	case 2:
		system("cls");
		printString("You can't refuse a gift from a kind man like me! (Strange man)");
		pause();
		printString("FIGHT!");
		pause();
		battle(7);
		system("cls");
		printString("After the fight you jump on the first subway back to Skanstull, because why would you stay in Rinkeby?");
		pause();
		skanstull();
		break;
	default: 
		system("cls");
		printString("Wrong input!");
		goto top;
	}
}
