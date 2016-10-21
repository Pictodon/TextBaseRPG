//Includes
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <ctype.h>

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
void printStringColor(int color, string stringInput, int color2, string stringInput2, int color3, string stringInput3, int color4, string stringInput4, bool instant);
void asignDefaultRarityColor();
void battle(int enemyType);
void death();
void levelUpCheck();
void talents();

//Global vars
//Vars used for loading
bool firstInvLoad = true;
int winHeight = 0;
int winWide = 0;
//Inventory related vars
int numberOfItems = 10;
int invSort = 1;
int equipedWeapon;
int invSortPos[11];
int defaultColor = 7;
//Player related vars
string playerName = "";
int playerClass;
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
} shopKeeper[10];

//Main
void main()
{
	//Assign name and info for every item in the game
	invItems[4].name = "Bottle"; invItems[4].quantity = 1; invItems[4].quality = "Legendary"; invItems[4].levelRequirement = 3; invItems[4].buyPrice = 13;
	invItems[6].name = "dada"; invItems[6].quantity = 1; invItems[6].quality = "Rare"; invItems[6].buyPrice = 100;
	invItems[5].name = "asdsdadsad"; invItems[5].quantity = 1; invItems[5].quality = "Common"; invItems[5].buyPrice = 20;
	invItems[7].name = "as31221dsdadsad"; invItems[7].quantity = 0; invItems[7].quality = "Legendary"; invItems[7].buyPrice = 10;
	invItems[3].name = "Katana"; invItems[3].quantity = 1; invItems[3].quality = "Rare"; invItems[3].weapon = true; invItems[3].inventoryColor = 16; invItems[3].levelRequirement = 2; invItems[3].buyPrice = 20;

	enemy[0].health = 10; enemy[0].name = "Skeletal"; enemy[0].damage = 1; enemy[0].xpGain = 100, enemy[0].maxHealth = 10; enemy[0].drop = 10; enemy[0].hasDrop = true; enemy[0].dropAmount = 2; enemy[0].potentialLoot = 2;
	enemy[1].health = 16; enemy[1].name = "Skeletal King"; enemy[1].damage = 2; enemy[1].xpGain = 100, enemy[1].maxHealth = 16; enemy[1].drop = 9; enemy[1].hasDrop = true; enemy[1].dropAmount = 1; enemy[1].potentialLoot = 4;

	shopKeeper[0].name = "Oskar"; shopKeeper[0].greeting = "Hello, newfag"; shopKeeper[0].items[0] = 4; shopKeeper[0].items[1] = 6; shopKeeper[0].items[2] = 7;

	asignDefaultRarityColor();

	choseFontSize();

	//Set console to be fulscreen
	system("mode 1000");

	screenResolution();

	//Tell the compiler what number to base rand(); of
	srand(time(NULL));

	talents();

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
	printStringColor(7, "[1] ", 2, "Hunter", 7, "", 7, "", false);

	//Set text color to 8 and print
	printStringColor(7, "[2] ", 8, "Warrior", 7, "", 7, "", false);

	//Set text color to 9 and print
	printStringColor(7, "[3] ", 9, "Shaman", 7, "", 7, "", false);

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
void printStringColor(int color, string stringInput, int color2, string stringInput2, int color3, string stringInput3, int color4, string stringInput4, bool instant)
{
	//Add every stirng together and caculate string length to center content
	int totalLength = stringInput.length() + stringInput2.length() + stringInput3.length() + stringInput4.length();
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
	string inventoryTitle = playerName + "'s inventory", input, damageString;
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
	printStringColor(7, "  | Level: " + to_string(playerLevel) + " " + to_string(playerExperience) + "/500" + string(13 - numDigitsGold - numDigitsXp - numDigitsPlayerLevel, ' ') + "Gold: ", 6, to_string(playerGold), 7, " |  ", 7, "", true);
	printStringColor(7, "  |  " + string(26 - playerMaxHealth, ' ') + "HP: ", 4, string(playerHealth, '#'), 8, string(playerMaxHealth - playerHealth, '#'), 7, " |  ", true);
	//printStringColor(7, "  |  " + string(26 - playerMaxHealth, ' ') + "HP: ", 8, string(playerMaxHealth - playerHealth, '#'), 4, string(playerHealth, '#'), 7, " |  ", true);
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
			}
			else
			{
				levelReqColor = 8;
			}

			//Check item quality and set color to the right quality color with the printStringColor(7, "", 7, "", 7, "", 7, "", false); function
			//If no quality matched, make default color
			if (invItems[i].weapon == false)
				printStringColor(7, "  | " + to_string(invItems[i].quantity) + "x ", invItems[i].inventoryColor, invItems[i].name, levelReqColor, string(24 - to_string(invItems[i].quantity).length() - invItems[i].name.length() - to_string(invItems[i].levelRequirement).length(), ' ') + "Lvl. " + to_string(invItems[i].levelRequirement), 7, " |  ", true);
			else
				printStringColor(7, "  | ", invItems[i].inventoryColor, invItems[i].name, levelReqColor, string(26 - invItems[i].name.length() - to_string(invItems[i].levelRequirement).length(), ' ') + "Lvl. " + to_string(invItems[i].levelRequirement), 7, " |  ", true);

			printStringColor(7, "  | ", invItems[i].inventoryColor, invItems[i].quality, 7, " (" + invItems[i].type + ")" + string(28 - invItems[i].type.length() - invItems[i].quality.length(), ' ') + " |  ", 7, "", true);
			instantPrint("  |---------------------------------|  ");
		}
	}
	//Set the firstInLoad to false to prevent items being added twice to array earlier in code
	firstInvLoad = false;

	instantPrint("  |                                 |  ");
	instantPrint("  |____________/_/(*)\\_\\____________|  ");
	instantPrint("  \\/-------------------------------\\/  ");

	printString("'Equip', 'Use', 'Delete' or 'Back'");

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
					printString("Level requirement: " + to_string(invItems[invSortPos[secondInput]].levelRequirement));
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
	bool update = false;

	//Set item quantity to current quantity plus 1
	invItems[itemID].quantity = invItems[itemID].quantity + quantity;

	for (int i = 0; i < numberOfItems; i++)
	{
		if (invSortPos[i] == itemID)
			update = true;
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
	int priceCharCount, numDigitsGold, secondInput, numberBuy = 1;

	string input;

top:

	system("cls");
	cout << endl;

	instantPrint(shopKeeper[shopId].name + "'s shop");
	instantPrint("\\\\--// -- -- -- -- -- -- -- -- -- -- -- -- \\\\--//  ");
	instantPrint("     ||  Name:                Price:            ||      ");

	for (int n = 0; n <= 4; n++)
	{
		if (shopKeeper[shopId].items[n] > 0)
		{
			if (invItems[shopKeeper[shopId].items[n]].buyPrice > 99)
				priceCharCount = 3;
			if (invItems[shopKeeper[shopId].items[n]].buyPrice > 9)
				priceCharCount = 2;
			else
				priceCharCount = 1;
			printStringColor(7, "  ||  ", invItems[shopKeeper[shopId].items[n]].inventoryColor, invItems[shopKeeper[shopId].items[n]].name + string(21 - invItems[shopKeeper[shopId].items[n]].name.length(), ' '), 6, to_string(invItems[shopKeeper[shopId].items[n]].buyPrice), 7, string(16 - priceCharCount, ' ') + "  ||    ", true);
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

	printStringColor(7, string(40 - numDigitsGold, ' ') + "Gold: ", 6, to_string(playerGold), 7, "", 7, "", true);
	printString("'Buy', 'Sell', or 'Back'");

	inputSign();
	cin >> input;

	if (input == "buy" || input == "Buy" || input == "BUY")
	{
		for (int i = 0; i < 5; i++)
		{
			if (shopKeeper[shopId].items[i] > 0)
			{
				printString("[" + to_string(numberBuy) + "]" + invItems[shopKeeper[shopId].items[i]].name);
				numberBuy++;
			}

		}
		pause();
		goto top;
	}
	else if (input == "sell" || input == "Sell" || input == "SELL")
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
}

//Used when removing an inventory item
void removeFromInvSortArray(int itemID)
{
	//For every spot in array that is larger than the removed one
	for (int i = itemID; i < numberOfItems + 1; i++)
	{
		//If it isn't the last slot in array set current slot to next slot
		if (i != numberOfItems)
			invSortPos[i] = invSortPos[i + 1];
		else
		{

		}
	}
	//Tell the program there's one less sorted value
	invSort--;
}

void battle(int enemyType)
{
	string attack;
	int attackPower, enemyAttackPower;
	bool ran = false;
	enemy[enemyType].health = enemy[enemyType].maxHealth;
	while (enemy[enemyType].health > 0 && playerHealth > 0)
	{
		system("cls");

		printStringColor(7, "#--------------------------------#", 7, string(10, ' '), 7, "#--------------------------------#", 7, "", true);
		printStringColor(7, "# -" + playerName + "-" + string(29 - playerName.length(), ' ') + "#", 7, string(10, ' '), 7, "# -" + enemy[enemyType].name + "-" + string(29 - enemy[enemyType].name.length(), ' ') + "#", 7, "", true);
		printStringColor(7, "# " + string(playerHealth, '#') + string(playerMaxHealth - playerHealth, 'O') + string(31 - playerMaxHealth, ' ') + "#", 7, string(10, ' '), 7, "# " + string(enemy[enemyType].health, '#') + string(enemy[enemyType].maxHealth - enemy[enemyType].health, 'O') + string(21 - enemy[enemyType].maxHealth + 10, ' ') + "#", 7, "", true);
		printStringColor(7, "#--------------------------------#", 7, string(10, ' '), 7, "#--------------------------------#", 7, "", true);
		//"# -" << playerName << "-" << string(29 - playerName.length(), ' ') << "#"

		cout << "Your turn!" << endl << "Use 'attack', 'run', 'block' to decide your next move." << endl;
		cin >> attack;

		if (attack == "attack" || attack == "Attack" || attack == "ATTACK")
		{
			Sleep(500);
			attackPower = rand() % 10 + 1;
			if (attackPower % 2 == 0 && attackPower >= 6)
			{
				attackPower = invItems[equipedWeapon].damage + invItems[equipedWeapon].damage / 2;
				cout << "[Critical Hit!] ";
			}
			else
			{
				attackPower = invItems[equipedWeapon].damage;
			}
			enemy[enemyType].health = enemy[enemyType].health - attackPower;
			cout << "You hit " << enemy[enemyType].name << " with " << attackPower << " of healthpoints!" << endl;


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
				cout << "You did not manage to run!" << endl;
			}
		}
		Sleep(500);

		enemyAttackPower = rand() % 10 + 1;

		if (enemyAttackPower % 2 == 0 && enemyAttackPower >= 8)
		{
			enemyAttackPower = enemy[enemyType].damage + enemy[enemyType].damage / 2;
			if (ran == false && enemy[enemyType].health > 0)
				cout << "[Critical Hit!] ";
		}
		else
		{
			enemyAttackPower = enemy[enemyType].damage;
		}

		if (enemy[enemyType].health > 0)
		{
			playerHealth = playerHealth - enemyAttackPower;

			cout << enemy[enemyType].name << " hit you with " << enemyAttackPower << " of healthpoints!" << endl;
		}
		else
		{
			if (ran == false)
			{
				playerExperience = playerExperience + enemy[enemyType].xpGain;
				cout << enemy[enemyType].name << " successfully killed! Which has granted you " << enemy[enemyType].xpGain << " experience points!" << endl;

				if (enemy[enemyType].hasDrop)
				{
					int dropChance = rand() % 10 + 1;
					if (dropChance > 6)
					{
						invItems[enemy[enemyType].potentialLoot].quantity++;
						cout << "Rare drop! You got a " << invItems[enemy[enemyType].potentialLoot].name << endl;
					}
					invItems[enemy[enemyType].drop].quantity = invItems[enemy[enemyType].drop].quantity + enemy[enemyType].dropAmount;
					cout << "You have been rewarded with " << enemy[enemyType].dropAmount << " " << invItems[enemy[enemyType].drop].name << endl;
				}

				//levelUpCheck();
			}
			else
			{
				cout << "You have successfully ran away" << endl;
				system("pause");
			}
		}

		if (playerHealth <= 0)
			death();

		system("pause");
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

void talents()
{

	int talentOne;
	int talentTwo;
	int talentThree;

talentTop1:
	system("cls");

	instantPrint("_______________________________________________");
	instantPrint("[---------------------------------------------]");
	instantPrint("|       TalentOne1 - TalentOne2 - TalentOne3  |");
	instantPrint("|                                             |");
	instantPrint("|           []           []           []      |");
	instantPrint("|                                             |");
	instantPrint("[---------------------------------------------]");
	printString("[1] Pick TalentOne1 [2] Pick TalentOne2 [3] Pick TalentOne3");
	inputSign();
	cin >> talentOne;

	switch (talentOne) {
	case 1:
		talentOne = 1;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("|       TalentOne1 - TalentOne2 - TalentOne3  |");
		instantPrint("|                                             |");
		instantPrint("|           [x]          []           []      |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	case 2:
		talentOne = 2;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("|       TalentOne1 - TalentOne2 - TalentOne3  |");
		instantPrint("|                                             |");
		instantPrint("|           []           [x]          []      |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	case 3:
		talentOne = 3;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("|       TalentOne1 - TalentOne2 - TalentOne3  |");
		instantPrint("|                                             |");
		instantPrint("|           []           []           [x]     |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	default:
		printString("That's not an option");
		pause();
		goto talentTop1;
		break;
	}

talentTop2:
	system("cls");

	instantPrint("_______________________________________________");
	instantPrint("[---------------------------------------------]");
	instantPrint("|       TalentTwo1 - TalentTwo2 - TalentTwo3  |");
	instantPrint("|                                             |");
	instantPrint("|           []           []            []     |");
	instantPrint("|                                             |");
	instantPrint("|---------------------------------------------]");
	printString("[1] Pick TalentTwo1 [2] Pick TalentTwo2 [3] Pick TalentTwo3");
	inputSign();
	cin >> talentTwo;

	switch (talentTwo) {
	case 1:
		talentTwo = 1;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("|     TalentTwo1 - TalentTwo2 - TalentTwo3    |");
		instantPrint("|                                             |");
		instantPrint("|           [x]          []            []     |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	case 2:
		talentTwo = 2;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("|     TalentTwo1 - TalentTwo2 - TalentTwo3    |");
		instantPrint("|                                             |");
		instantPrint("|           []           [x]           []     |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	case 3:
		talentTwo = 3;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("|     TalentTwo1 - TalentTwo2 - TalentTwo3    |");
		instantPrint("|                                             |");
		instantPrint("|         []           []            [x]      |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	default:
		printString("That's not an option");
		break;
		goto talentTop2;
	}

talentTop3:
	system("cls");

	instantPrint("_______________________________________________");
	instantPrint("[---------------------------------------------]");
	instantPrint("| TalentThree1 - TalentThree2 - TalentThree 3 |");
	instantPrint("|                                             |");
	instantPrint("|         []           []            []       |");
	instantPrint("|                                             |");
	instantPrint("|---------------------------------------------]");
	printString("[1] Pick TalentThree1 [2] Pick TalentThree2 [3] Pick TalentThree3");
	inputSign();
	cin >> talentThree;

	switch (talentThree) {
	case 1:
		talentThree = 1;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("| TalentThree1 - TalentThree2 - TalentThree 3 |");
		instantPrint("|                                             |");
		instantPrint("|           [x]          []           []      |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	case 2:
		talentThree = 2;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("| TalentThree1 - TalentThree2 - TalentThree 3 |");
		instantPrint("|                                             |");
		instantPrint("|           []           [x]          []      |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	case 3:
		talentThree = 3;
		system("cls");
		instantPrint("_______________________________________________");
		instantPrint("[---------------------------------------------]");
		instantPrint("| TalentThree1 - TalentThree2 - TalentThree 3 |");
		instantPrint("|                                             |");
		instantPrint("|           []           []           [x]     |");
		instantPrint("|                                             |");
		instantPrint("[---------------------------------------------]");
		pause();
		system("cls");
		break;
	default:
		printString("That's not an option");
		pause();
		goto talentTop3;
		break;
	}
	system("cls");
	instantPrint("These are your talents:");
	cout << endl;
	if (talentOne == 1)
		printString("talentOne1");
	else if (talentOne == 2)
		printString("talentOne2");
	else if (talentOne == 3)
		printString("talentOne3");
	cout << endl;
	if (talentTwo == 1)
		printString("talentTwo1");
	else if (talentTwo == 2)
		printString("talentTwo2");
	else if (talentTwo == 3)
		printString("talentTwo3");
	cout << endl;
	if (talentThree == 1) {
		printString("talentThree1");
	}
	else if (talentThree == 2) {
		printString("talentThree2");
	}
	else if (talentThree == 3) {
		printString("talentThree3");
	}
	cout << endl;
	pause();
	system("cls");
}
