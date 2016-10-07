#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
string cName;
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

		cout << "Hello my friend, how are you? " << endl;

	Sleep(1001);
	system("cls");

	cout << "Oh thats right, i dont care. " << endl;
	Sleep(1001);
	system("cls");

	cout << "what´s your name?" << endl;
	cin >> cName;
	system("cls");

	cout << "Was poppin " << cName << endl;
	
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
