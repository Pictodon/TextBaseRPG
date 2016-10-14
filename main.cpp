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
void printStringColor(int color, string stringInput, int color2, string stringInput2, int color3, string stringInput3, int color4, string stringInput4, bool instant);
void loadingAnimation(int durationSeconds);
void asignDefaultRarityColor();

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
} invItems[11];

//Main
void main()
{
	//Assign name and info for every item in the game
	invItems[4].name = "Bottle"; invItems[4].quantity = 1; invItems[4].quality = "Legendary"; invItems[4].levelRequirement = 3;
	invItems[6].name = "dada"; invItems[6].quantity = 1; invItems[6].quality = "Rare";
	invItems[5].name = "asdsdadsad"; invItems[5].quantity = 1; invItems[5].quality = "Common";
	invItems[7].name = "as31221dsdadsad"; invItems[7].quantity = 0; invItems[7].quality = "Legendary";
	invItems[3].name = "Katana"; invItems[3].quantity = 1; invItems[3].quality = "Rare"; invItems[3].weapon = true; invItems[3].inventoryColor = 16; invItems[3].levelRequirement = 2;

	asignDefaultRarityColor();

	choseFontSize();

	//Set console to be fulscreen
	system("mode 1000");

	screenResolution();

	//Tell the compiler what number to base rand(); of
	srand(time(NULL));

	nameGreeting();

	classMenu();

	//Random shiz
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
		printString("You have a really powerfull arrow that you can fire at your enemy. ");
		printString("If you are easily scared by monsters then this is the class for you. ");
		break;
	case 2:
		//not sure vad jag har skrivit xD
		printString("If you have less than 10 braincells then this is the class for you. ");
		printString("I mean who would choose a class that just runs in to battle with their,");
		printString("head first. The smartest class would be hunter, but nevermind. ");
		printString("With the warrior class you can slash your baws ass sword at your enemies.");
		printString("Just look at He-Man, he's the boss.");
		break;
	case 3:
		printString("Are you gonna pick a shaman? Really?");
		printString("The shaman class gets nerfed every expansion, just so you know.");
		printString("Very well, the shaman is a class that combiens the hunters range and the warriors strength.");
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

//Draws the loading animation when called
/// <summary>Used to to draw the loading animation
/// <para>Usage: loadingAnimation(2);</para>
/// </summary>
void loadingAnimation(int durationSeconds)
{
	for (int i = 0; i < durationSeconds; i++)
	{
		system("cls");
		for (int i = 0; i < winHeight - 6; i++)
		{
			cout << endl;
		}
		cout << string(winWide + 1 - 15, ' ') << ">))'>";
		Sleep(125);
		system("cls");
		for (int i = 0; i < winHeight - 6; i++)
		{
			cout << endl;
		}
		cout << string(winWide + 1 - 15, ' ') << " >))'>";
		Sleep(125);
		system("cls");
		for (int i = 0; i < winHeight - 6; i++)
		{
			cout << endl;
		}
		cout << string(winWide + 1 - 15, ' ') << "  >))'>";
		Sleep(125);
		system("cls");
		for (int i = 0; i < winHeight - 6; i++)
		{
			cout << endl;
		}
		cout << string(winWide + 1 - 15, ' ') << "   >))'>";
		Sleep(125);
		system("cls");
		for (int i = 0; i < winHeight - 6; i++)
		{
			cout << endl;
		}
		cout << string(winWide + 1 - 15, ' ') << "    >))'>";
		Sleep(125);
		system("cls");
		for (int i = 0; i < winHeight - 6; i++)
		{
			cout << endl;
		}
		cout << string(winWide + 1 - 15, ' ') << "   <'((<";
		Sleep(125);
		system("cls");
		for (int i = 0; i < winHeight - 6; i++)
		{
			cout << endl;
		}
		cout << string(winWide + 1 - 15, ' ') << "  <'((<";
		Sleep(125);
		system("cls");
		for (int i = 0; i < winHeight - 6; i++)
		{
			cout << endl;
		}
		cout << string(winWide + 1 - 15, ' ') << " <'((<";
		Sleep(125);
	}
	system("cls");
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
					printString(invItems[invSortPos[secondInput]].name + " has been equiped!");
					pause();
					goto top;
				}
				else
				{
					printString("You need to level up a few levels before you could use this.");
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
				printString(invItems[invSortPos[secondInput]].name + " has been removed sucessfully!");

				//Set the quantity to 0
				invItems[invSortPos[secondInput]].quantity = 0;

				//Call the function to update the array
				removeFromInvSortArray(secondInput);
			}
			else
			{
				printString("You can't delete your currently equiped weapon or quest items!");
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
			printString("Item type is not a consumable!");
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
	//Set item quantity to current quantity plus 1
	invItems[itemID].quantity = invItems[itemID].quantity + quantity;

	//Update array for inventory sortation
	invSortPos[invSort] = itemID;

	//Tell the program how many sorted values there is in total
	invSort++;
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
