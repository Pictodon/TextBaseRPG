#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

struct items
{
	string name;
	int quantity;
	string rarity;
	int damage;
} invItems[10];

void main()
{
	invItems[0].name = "Bottle"; invItems[0].quantity = 1; invItems[0].rarity = "Legendary";

}
