//Includes
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

//Define namespace
using namespace std;

//Define functions
void printString(string stringInput, bool boolAddSpacing);
void pause();
void screenResolution();
void setTextColor(int col);
void nameGreeting();
void choseFontSize();
void classMenu();

//Create an array with a structure for every item
struct items
{
	string name;
	int quantity;
	string rarity;
	int damage;
} invItems[10];

//Global var
string cName;
int winHeight = 0;
int winWide = 0;
int playerClass;

//Main
void main()
{
	//Assign name and info for every item in the game
	invItems[0].name = "Bottle"; invItems[0].quantity = 1; invItems[0].rarity = "Legendary";

	choseFontSize();

	//Set console to be fulscreen
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	screenResolution();

	//Tell the compiler what number to base rand of
	srand(time(NULL));

	nameGreeting();
	classMenu();
}

void nameGreeting()
{
	//Call the function to print text
	cout << endl;
	printString("Hello my friend, how are you?", true);

	pause();
	system("cls");

	cout << endl;
	printString("Oh, that's right. I dont care.", true);

	pause();
	system("cls");

	cout << endl;
	printString("What's your name?", false);
	cout << "> ";
	cin >> cName;
	system("cls");

	cout << endl;
	printString("Was poppin, " + cName + "?", true);

	pause();
}

void classMenu()
{
	int classConfirm;
failSaver:

	system("cls");

	cout << endl;

	printString("It's time to pick a class", true);

	printString("What would you like to play?", true);

	printString("[1] Hunter", true);

	printString("[2] Warrior", true);

	printString("[3] Shaman", false);

	cout << "> ";

	cin >> playerClass;
	cout << endl;

	switch (playerClass)
	{
	case 1:
		printString("Oh so you're a hunter type. ", true);
		printString("This class it especially good when you want to attack at a long range.", true);
		printString("You have a really powerfull arrow that you can fire at your enemy. ", true);
		printString("If you are easily scared by monsters then you should play this class. ", false);

		break;
	case 2:
		printString("", true);
		printString("", true);
		printString("", true);
	case 3:
		printString("", true);
		printString("", true);
		printString("", true);


	default:
		printString("That is not an option.", false);
		pause();
		goto failSaver;
	}
	cout << endl;
	printString("Are you sure you want to play this class? ", true);
	printString("[1] Yes I am sure.", true);
	printString("[2] No I want to browse the other classes.", false);


	cout << "> ";
	cin >> classConfirm;
	switch (classConfirm)
	{
	case 1:
		printString("Then let's gooooo!", false);
		pause();
		break;
	case 2:
		printString("Okay", false);
		pause();
		goto failSaver;
	default:
		printString("That is not an option.", false);
		pause();
		goto failSaver;

	}
	pause();

}

void choseFontSize()
{
	int fontInput = 18;

top:

	//Set font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = fontInput;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	cout << "Font size: " + to_string(cfi.dwFontSize.Y) << endl;

	cout << "Enter a number to change font size,\nand type the current font size to proceed" << endl;

	cin >> fontInput;

	if (!cin)
	{
		system("cls");
		cin.clear();
		string failSaver;
		getline(cin, failSaver);
		goto top;
	}

	if (fontInput == cfi.dwFontSize.Y)
	{
		system("cls");
	}
	else
	{
		cfi.dwFontSize.Y = fontInput;
		system("cls");
		goto top;
	}
}

void setTextColor(int col)
{
	//Set text color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (col & 0x0F));
}

//Function to print text
void printString(string stringInput, bool boolAddSpacing)
{
	int spacing = winWide / 2 - stringInput.length() / 2;
	cout << string(spacing, ' ');
	//For every letter in string do this
	for (int i = 0; i < stringInput.length(); i++)
	{
		//Print character and sleep for 70ms
		cout << stringInput[i];
		Sleep(70);
	}
	//If boolAddSpacing is true, just make a new line
	if (boolAddSpacing)
	{
		cout << endl;
	}
	else
	{
		//Create a new line in the end with spacing
		cout << endl << string(spacing, ' ');
	}
}

void pause()
{
	//Define variable types and calculate string length and assign position
	string pauseText = "Press any key to proceed";
	int pauseTextLength = pauseText.length();
	int pauseTextPos = winWide / 2 - pauseTextLength / 2;

	//Print Press any key to proceed and pause
	printString(pauseText, false);
	cout << "> ";
	system("pause >nul");
}

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

	//For every row in console
	for (int i = 1; i < winHeight; i++)
	{
		//If it's the first row print full row with #
		if (i == 1)
		{
			cout << string(winWide, '#');
		}
		//If it's the last row print full row with #
		else if (i == winHeight - 1)
		{
			cout << string(winWide, '#');
			//Stop the loop
			break;
		}
		//For every other row print in beginning and end
		cout << "#" << string(winWide - 2, ' ') << "#";
	}

	//Define a variable to store the input
	int screenResInput;

	//Define a goto point
failSaver:

	cout << "Is the screen resolution above correct?\n[1] Yes\n[2] No" << endl;

	cin >> screenResInput;

	//Take action by input
	switch (screenResInput)
	{
		//Just continue here
	case 1:
		system("cls");
		break;
		//Set Screen res to a default one 
	case 2:
		system("cls");
		winHeight = 20;
		winWide = 20;
		break;
		//If the others didn't match go back to top and clear sceen
	default:
		cout << "Wrong input!" << endl;
		//Pause and clear screen on the same line
		pause();
		system("cls");
		goto failSaver;
	}
}
