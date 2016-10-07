#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct items
{
	string name;
	int quantity;
	string rarity;
	int damage;
} invItems[10];

void printString(string String)
{
	for (int i = 0; i < String.length(); i++)
	{
		cout << String[i];
		Sleep(70);
	}
	cout << endl;
}

void main()
{
	invItems[0].name = "Bottle"; invItems[0].quantity = 1; invItems[0].rarity = "Legendary";

	printString("How dank isn't this?");

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		// an error occourred
		cerr << "Cannot determine console size." << endl;
	}
	else
	{
		cout << "The console is " << csbi.srWindow.Right - csbi.srWindow.Left + 1 << " wide." << endl;
	}

	system("pause");
}
