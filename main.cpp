//Includes
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

//Define namespace
using namespace std;

//Define functions
void printString(string String);

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

//Main
void main()
{
	//Assign name and info for every item in the game
	invItems[0].name = "Bottle"; invItems[0].quantity = 1; invItems[0].rarity = "Legendary";

	//Set console to be fulscreen
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	//Tell the compiler what number to base rand of
	srand(time(NULL));

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
		}
		//For every other row print in beginning and end
			cout << "#" << string(winWide - 2, ' ') << "#";
	}

	//Define a variable to store the input
	int screenResInput;

	//Define a goto point
	failSaver:

	cout << "Is the screen resolution above correct?\n[1] Yes\n[1] No" << endl;

	cin >> screenResInput;

	//Take action by input
	switch (screenResInput)
	{
		//Just continue here
		case 1:
			break;
		//Set Screen res to a default one 
		case 2:
			winHeight = 20;
			winWide = 20;
		//If the others didn't match go back to top and clear sceen
		default:
			cout << "Wrong input!" << endl;
			//Pause and clear screen on the same line
			system("pause&cls");
			goto failSaver;
	}

	//Call the function to print text
	printString("Hello my friend, how are you?");

	system("pause&cls");

	printString("Oh thats right, I dont care.");
	system("pause&cls");

	printString("What's your name?");
	cin >> cName;
	system("cls");

	printString("Was poppin " + cName + "?");

	system("pause");
}

//Function to print text
void printString(string String)
{
	//For every letter in string do this
	for (int i = 0; i < String.length(); i++)
	{
		//Print character and sleep for 70ms
		cout << String[i];
		Sleep(70);
	}
	//Create a new line in the end
	cout << endl;
}
