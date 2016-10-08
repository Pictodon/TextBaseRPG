//Includes
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

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
	printString("Hello my friend, how are you?");

	pause();
	system("cls");

	cout << endl;
	printString("Oh, that's right. I dont care.");

	pause();
	system("cls");

	cout << endl;
	printString("What's your name?");
	inputSign();
	cin >> cName;
	system("cls");

	cout << endl;
	printString("Was poppin, " + cName + "?");

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

	//Set text color to 2
	setTextColor(2);

	printString("[1] Hunter");

	//Set text color to 8
	setTextColor(8);

	printString("[2] Warrior");

	//Set text color to 9
	setTextColor(9);

	printString("[3] Shaman");

	//Change back to default color
	setTextColor(7);

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
		printString("VIKTOR SKRIVER");
		printString("VIKTOR SKRIVER");
		printString("VIKTOR SKRIVER");
		break;


	default:
		printString("That is not an option.");
		pause();
		goto failSaver;
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
	int fontInput = 18;

top:

	//Set font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.dwFontSize.Y = fontInput;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	cout << "Font size: " + to_string(cfi.dwFontSize.Y) << endl;

	cout << "Enter a number to change font size,\nand type the current font size to proceed" << endl;

	cin >> fontInput;

	//If input is not a number, go to top and clear cin
	if (!cin)
	{
		system("cls");
		cin.clear();
		string failSaver;
		getline(cin, failSaver);
		goto top;
	}

	//Just continue if input is same as current font otherwise update font
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
void printString(string stringInput)
{
	int spacing = winWide / 2 - stringInput.length() / 2;
	cout << string(spacing, ' ');
	//For every letter in string do this
	for (int i = 0; i < stringInput.length(); i++)
	{
		//Print character and sleep for 70ms
		cout << stringInput[i];
		Sleep(30);
	}

	cout << endl;
}

void inputSign()
{
	//Define variable types and calculate string length and assign position
	string pauseText = "Press any key to proceed";
	int pauseTextLength = pauseText.length();
	int pauseTextPos = winWide / 2 - pauseTextLength / 2;
	cout << string(pauseTextPos, ' ') << "> ";
}

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
		winHeight = 60;
		winWide = 100;
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
