#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

using namespace std;

void quest1Complete();
void quest2Complete();
void drawInventory();
void menu();
void battle(int enemyType);

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

string name, activeQuest;
int userLevel = 1, userHealth = 10, userMaxHealth = 10, userXp = 0, equipedWeapon;

void greeting()
{
	cout << " _       __     __                               " << "__       " << endl;
	cout << "\| \|     / /__  / /________  ____ ___  ___      " << " / /_____  " << endl;
	cout << "\| \| /\| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\" << "     / __/ __ \\ " << endl;
	cout << "\| \|/ \|/ /  __/ / /__/ /_/ / / / / / /  __/    " << "/ /_/ /_/ / " << endl;
	cout << "\|__/\|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/  " << "   \\__/\\____/  " << endl;

	cout << "       ________        " << "    __                                   ______" << endl;
	cout << "      /_  __/ /_  ___  " << "   / /   ____  ____  ___ _      ______  / / __/" << endl;
	cout << "       / / / __ \\/ _ \\ " << "  / /   / __ \\/ __ \\/ _ \\ \| /\| / / __ \\/ / /_" << endl;
	cout << "      / / / / / /  __/ " << " / /___/ /_/ / / / /  __/ \|/ \|/ / /_/ / / __/" << endl;
	cout << "     /_/ /_/ /_/\\___/  " << "/_____/\\____/_/ /_/\\___/\|__/\|__/\\____/_/_/" << endl;
	cout << "    ____               _           __    " << endl;
	cout << "   / __ \\_________    (_)__  _____/ /_  " << endl;
	cout << "  / /_/ / ___/ __ \\  / / _ \\/ ___/ __/ " << endl;
	cout << " / ____/ /  / /_/ / / /  __/ /__/ /_     " << endl;
	cout << "/_/   /_/   \\____/_/ /\\___/\\___/\\__/ " << endl;
	cout << "                /___/                    " << endl << endl;
}

void questAscii()
{
	cout << endl << endl;
	cout << "*\|" << "   ____                  __ " << "\|*" << endl;
	cout << "*\|" << "  / __ \\__  _____  _____/ /_" << "\|*" << endl;
	cout << "*\|" << " / / / / / / / _ \\/ ___/ __/" << "\|*" << endl;
	cout << "*\|" << "/ /_/ / /_/ /  __(__  ) /_  " << "\|*" << endl;
	cout << "*\|" << "\\___\\_\\__,_/\\___/____/\\__/  " << "\|*" << endl;
	cout << "********************************" << endl;
}


void death()
{
	userHealth = userMaxHealth / 2;
	system("cls");
	cout << "You have died :(\nPress any key to respawn." << endl;
	system("pause");
	menu();
}

void levelUpCheck()
{
	while (userXp >= 500)
	{
		userXp = userXp - 500;
		userLevel++;
		cout << "Congratulations, you have reached level " << userLevel << "!" << endl;
		cout << "Maxium HP has been increased from " << userMaxHealth;
		userMaxHealth = userMaxHealth + 2;
		cout << " to " << userMaxHealth << endl;
	}
}

void mainMenu(string gameName, string version)
{
	int menuChoice;

	start:

	system("cls");


	greeting();

	cout << gameName << " \| Version v" << version << endl << endl;

	cout << "1. Start game\n\n\n0. Quit game" << endl;

	cin >> menuChoice;

	switch (menuChoice)
	{
		case 1:
			system("cls");
			break;
		case 0:
			exit(0);
		default:
			system("cls");
			cout << "Invalid choice!" << endl;
			goto start;
	}
}

void village()
{
	string input;

start:

	system("cls");

	if (activeQuest == "quest2")
	{
		if (invItems[6].quantity == 0)
			cout << "Our village was attacked by a pack of Skeletals,\nplease help us kill them and collect pieces of our tome." << endl;
		else
			cout << "You have " << invItems[6].quantity << " out of 4 pieces to complete the quest." << endl;

		midQuest:

		cout << "Use 'fight' to start a fight with a Skeletal." << endl;
		
		if (invItems[6].quantity >= 3)
			cout << "Use 'fightboss' to start a fight the Skeletal boss!" << endl;

		cout << "You could also return to the menu using 'menu'!" << endl;

		cin >> input;

		if (input == "fight" || input == "Fight" || input == "FIGHT")
		{
			battle(0);

			system("cls");

			if (invItems[6].quantity <= 2)
			{
				invItems[6].quantity++;
			}

			if (invItems[6].quantity < 4)
			{
				if (invItems[6].quantity == 3)
					cout << "To get the last piece you'll have to kill a boss!\nMake sure to come prepared." << endl;
				else
					cout << "Great work, you need " << 4 - invItems[6].quantity << " more pieces!" << endl;
			}

			goto midQuest;
		}
		else if (input == "menu" || input == "Menu" || input == "MENU")
		{
			menu();
		}
		else if (input == "fightboss" || input == "Fightboss" || input == "FIGHTBOSS")
		{
			if (invItems[6].quantity >= 3)
			{
				battle(1);

				if (invItems[6].quantity == 3)
				{
					invItems[6].quantity++;
					quest2Complete();
				}

				goto start;
			}
			else
			{
				system("cls");
				cout << "Collect the other pieces first!" << endl;
				system("pause");
				goto start;
			}
		}
		else
		{
			cout << "Wrong usage, usage 'fight'!" << endl << endl;
			system("pause");
			goto start;
		}

		goto start;
	}
	else
	{

	}
}

void fastTravel()
{
	string input;

	start:

	system("cls");

	cout << "Fast travel to a location.\nUsage (location).\n e.g 'village'." << endl << endl;
	cout << "[Travel locations]" << endl;
	cout << "Village" << endl;
	cout << "Dragons lair" << endl;
	cout << "Akash was ther" << endl;

	cin >> input;

	if (input == "village" || input == "Village" || input == "VILLAGE")
	{
		village();
	}
	else if (input == "menu" || input == "Menu" || input == "MENU")
	{
		menu();
	}
	else
	{
		cout << "Wrong usage, usage 'location name'!" << endl << endl;
		system("pause");
		goto start;
	}
}

void menu()
{
	string input;

start:

	system("cls");

	cout << "This is the menu! Use this to travel to and from places.\nAs well as access the inventory.\n'travel'\n'inventory'" << endl;

	cin >> input;

	if (input == "inventory" || input == "Inventory" || input == "INVENTORY" || input == "i" || input == "I")
	{
		drawInventory();
	}
	else if (input == "travel" || input == "Travel" || input == "TRAVEL")
	{
		fastTravel();
	}
	else if (input == "info" || input == "Info" || input == "INFO")
	{

	}
	else
	{
		cout << "Wrong usage!" << endl << endl;
		system("pause");
	}
	goto start;
}

void drawInventory()
{
	string inventoryTitle = name + "'s inventory", input;
	int additionForOddNames = 0;

	if (inventoryTitle.length() % 2 == 1)
	{
		additionForOddNames = additionForOddNames + - 1;
	}

	int numDigits = 1, numDigitsXp = 1, quantityOrDamage, secondInput, numberOfItems = 11;

	string damageString;
	if (userXp > 99)
		numDigitsXp = 3;
	else if (userXp > 9)
		numDigitsXp = 2;
	else
		numDigitsXp = 1;

	top:

	system("cls");
	cout << endl << endl << endl << endl << endl << endl;
	cout << "|I|----------------------------------------------------------------------------------------------------|I|" << endl;
	cout << "|I|****************************************************************************************************|I|" << endl;
	cout << " -|" << string(20, ' ') << "Level: " << userLevel << " " << userXp << "/500" << string(16 - numDigitsXp - inventoryTitle.length() / 2, ' ') << "[" << inventoryTitle << "]" << string(4, ' ') << "HP: " << string(userHealth, '#') << string(userMaxHealth - userHealth, 'O') <<  string(42 - userMaxHealth + additionForOddNames - 1 - inventoryTitle.length() / 2, ' ') << "|-" <<  endl;
	cout << " I|____________________________________________________________________________________________________|I" << endl;
	cout << " I|                                                                                                    |I" << endl;
	cout << " I|  Quality:        Name:              Quantity/Damage:     Type:         Description:                |I" << endl;
	cout << " I|____________________________________________________________________________________________________|I" << endl;

	for (int i = 0; i < numberOfItems; i++)
	{
		if (invItems[i].quantity > 9 || invItems[i].damage > 9)
			numDigits = 2;
		else
			numDigits = 1;

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

		if (invItems[i].quantity > 0)
			cout << " I|" << string(2, ' ') << invItems[i].quality << string(16 - invItems[i].quality.length(), ' ') << invItems[i].name << string(19 - invItems[i].name.length(), ' ') << quantityOrDamage << damageString << string(21 - numDigits, ' ') << invItems[i].type << string(14 - invItems[i].type.length(), ' ') << invItems[i].desc << string(28 - invItems[i].desc.length(), ' ') << "|I" << endl;
	}
	cout << "|I|****************************************************************************************************|I|" << endl;
	cout << "|I|----------------------------------------------------------------------------------------------------|I|" << endl;

	cout << "'Equip', 'Use', 'Delete' or 'Back'" << endl;

	cin >> input;

	if (input == "equip" || input == "Equip" || input == "EQUIP")
	{
		for (int i = 0; i < numberOfItems; i++)
		{
			if (invItems[i].quantity > 0)
				cout << i << ". " << invItems[i].name << endl;
		}
		failcheck:
		cin >> secondInput;
		if (!cin)
		{
			cin.clear();
			string ignore;
			getline(cin, ignore);
			goto failcheck;
		}

		if (secondInput < numberOfItems && secondInput > 0)
		{
			if (invItems[secondInput].weapon == true)
			{
				equipedWeapon = secondInput;
				cout << invItems[secondInput].name << " has been equiped!" << endl;
				system("pause");
				goto top;
			}
			else
			{
				cout << "You can only equip weapons!" << endl;
				system("pause");
				goto top;
			}
		}

	}
	else if (input == "delete" || input == "Delete" || input == "DELETE")
	{
		for (int i = 0; i < numberOfItems; i++)
		{
			if (invItems[i].quantity > 0)
				cout << i << ". " << invItems[i].name << endl;
		}
	failchecksecond:
		cin >> secondInput;
		if (!cin)
		{
			cin.clear();
			string ignore;
			getline(cin, ignore);
			goto failchecksecond;
		}

		if (secondInput < numberOfItems && secondInput > 0 && invItems[secondInput].quantity > 0)
		{
			if (secondInput != equipedWeapon && invItems[secondInput].questItem == false)
			{
				cout << invItems[secondInput].name << " has been removed sucessfully!" << endl;
				invItems[secondInput].quantity = 0;
			}
			else
			{
				cout << "You can't delete your currently equiped weapon or quest items!" << endl;
			}
		}
		system("pause");
		goto top;
	}
	else if (input == "use" || input == "Use" || input == "USE")
	{
		for (int i = 0; i < numberOfItems; i++)
		{
			if (invItems[i].quantity > 0)
				cout << i << ". " << invItems[i].name << endl;
		}
	failcheckthird:
		cin >> secondInput;
		if (!cin)
		{
			cin.clear();
			string ignore;
			getline(cin, ignore);
			goto failcheckthird;
		}

		if (invItems[secondInput].consumable == true && userHealth < userMaxHealth)
		{
			invItems[secondInput].quantity--;
			userHealth = userHealth + invItems[secondInput].healthRegen;

			if (userHealth > userMaxHealth)
				userHealth = userMaxHealth;

			cout << "You have been healed for " << invItems[secondInput].healthRegen << " health points!" << endl;
			cout << "Current HP " << userHealth << "/" << userMaxHealth << endl;
		}
		else if (invItems[secondInput].consumable == true && userHealth == userMaxHealth)
		{
			cout << "Your HP is full!" << endl;
		}
		else
		{
			cout << "Item type is not a consumable!" << endl;
		}

		system("pause");
		goto top;
	}
	else if (input == "back" || input == "Back" || input == "BACK" )
	{

	}
	else
	{
		cout << "Wrong input!" << endl;
		system("pause");
		goto top;
	}
}

void quest1()
{
	activeQuest = "quest1";
	string input;

	questAscii();

	cout << "Your first quest is to open the inventory.\nThis is done by typing 'inventory' or 'i' and pressing enter." << endl;

start:
	cin >> input;

	if (input == "inventory" || input == "Inventory" || input == "INVENTORY" || input == "i" || input == "I")
	{
		
	}
	else
	{
		system("cls");
		cout << "Wrong usage!" << endl << endl;
		cout << "Correct usage: 'inventory' or 'i' and pressing enter." << endl;
		goto start;
	}


	//

	string inventoryTitle = name + "'s inventory";
	int additionForOddNames = 0;

	if (inventoryTitle.length() % 2 == 1)
	{
		additionForOddNames = additionForOddNames + -1;
	}

	int numDigits = 1;

	string damageString;

	system("cls");
	cout << endl << endl << endl << endl << endl << endl;
	cout << "|I|----------------------------------------------------------------------------------------------------|I|" << endl;
	cout << "|I|****************************************************************************************************|I|" << endl;
	cout << " -|" << string(20, ' ') << "Level: " << userLevel << " " << userXp << "/500" << string(16 - numDigits - inventoryTitle.length() / 2, ' ') << "[" << inventoryTitle << "]" << string(4, ' ') << "HP: " << string(userHealth, '#') << string(10 - userHealth, 'O') << string(32 + additionForOddNames - 1 - inventoryTitle.length() / 2, ' ') << "|-" << endl;
	cout << " I|____________________________________________________________________________________________________|I" << endl;
	cout << " I|                                                                                                    |I" << endl;
	cout << " I|  Quality:        Name:              Quantity/Damage:     Type:         Description:                |I" << endl;
	cout << " I|____________________________________________________________________________________________________|I" << endl;
	cout << " I|                                                                                                    |I" << endl;
	cout << "|I|****************************************************************************************************|I|" << endl;
	cout << "|I|----------------------------------------------------------------------------------------------------|I|" << endl;
	quest1Complete();
}

void quest2()
{
	activeQuest = "quest2";
	string input;

	system("cls");

start:

	questAscii();

	cout << name << ", the time has come to go out and kill some monsters!" << endl;
	cout << "Head over to the menu and then teleport to village." << endl << endl;
	cout << "To do this type 'menu' and press enter." << endl;

	cin >> input;

	if (input == "menu" || input == "Menu" || input == "MENU")
	{
		menu();
	}
	else
	{
		system("cls");
		cout << "Wrong usage!" << endl << endl;
		cout << "Correct usage: 'menu' and pressing enter." << endl;
		goto start;
	}
}

void quest1Complete()
{
	cout << "Congratulations, you have completed the first quest!\nHere you could view all of your items!\nYou get 200 xp as well as 2 apples!" << endl;
	invItems[10].quantity = invItems[10].quantity + 2;
	userXp = userXp + 200;

	levelUpCheck();

	system("pause");
}

void quest2Complete()
{
	system("cls");

	cout << "Thank you so much for saving us, without our tome our people would had gone crazy!" << endl;
	cout << "Here is your reward!" << endl;
	//invItems[10].quantity = invItems[10].quantity + 2;
	userXp = userXp + 200;

	levelUpCheck();

	system("pause");
}

void battle(int enemyType)
{
	string attack;
	int attackPower, enemyAttackPower;
	bool ran = false;
	enemy[enemyType].health = enemy[enemyType].maxHealth;
	while (enemy[enemyType].health > 0 && userHealth > 0)
	{
	system("cls");
	cout << endl << endl;
	cout << "#--------------------------------#" << endl;
	cout << "# -" << name << "-" << string(29 - name.length(), ' ') << "#" << endl; //32
	cout << "# " << string(userHealth, '#') << string(userMaxHealth - userHealth, 'O') << string(31 - userMaxHealth, ' ') << "#" << endl;
	cout << "#                                #" << endl;
	cout << "# -" << enemy[enemyType].name << "-" << string(29 - enemy[enemyType].name.length(), ' ') << "#" << endl; //32
	cout << "# " << string(enemy[enemyType].health, '#') << string(enemy[enemyType].maxHealth - enemy[enemyType].health, 'O') << string(21 - enemy[enemyType].maxHealth + 10, ' ') << "#" << endl;
	cout << "#--------------------------------#" << endl;

		cout << "Your turn!" << endl << "Use 'attack', 'run', 'block' to decide your next move." << endl;
		cin >> attack;
		
		if (attack == "attack" || attack == "Attack" || attack == "ATTACK")
		{
			Sleep(500);
			attackPower = rand()%10+1;
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
			int flee = rand()%10+1;
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

		enemyAttackPower = rand()%10+1;

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
			userHealth = userHealth - enemyAttackPower;

			cout << enemy[enemyType].name << " hit you with " << enemyAttackPower << " of healthpoints!" << endl;
		}
		else
		{
			if (ran == false)
			{
				userXp = userXp + enemy[enemyType].xpGain;
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

				levelUpCheck();
			}
			else
			{
				cout << "You have sucessfully ran away" << endl;
				system("pause");
				menu();
			}
		}

		if (userHealth <= 0)
			death();

		system("pause");
	}
}

void main()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	srand(time(NULL));

	string gameName, version;

	invItems[6].name = "Paper Pieces"; invItems[6].quantity = 0; invItems[6].questItem = true;
	invItems[1].name = "Shortsword"; invItems[1].quantity = 1; invItems[1].weapon = true; invItems[1].damage = 2; invItems[1].type = "Weapon"; invItems[1].desc = "Short melee weapon";
	invItems[2].name = "Skeleton arm"; invItems[2].quantity = 0; invItems[2].weapon = true; invItems[2].damage = 3; invItems[2].type = "Weapon"; invItems[2].desc = "Literally an arm";
	invItems[3].name = "Fire staff"; invItems[3].quantity = 0; invItems[3].weapon = true; invItems[3].damage = 4; invItems[3].type = "Weapon"; invItems[3].desc = "Fire staff"; invItems[3].questItem = true;
	invItems[4].quality = "Legendary"; invItems[4].name = "Dragon Katana"; invItems[4].quantity = 0; invItems[4].weapon = true; invItems[4].damage = 5; invItems[4].type = "Weapon"; invItems[4].desc = "Katana forged by dragons";
	invItems[9].name = "Health potion"; invItems[9].quantity = 0; invItems[9].type = "Consumable"; invItems[9].healthRegen = 10; invItems[9].consumable = true; invItems[9].desc = "Heals for 10HP when used";
	invItems[10].name = "Apples"; invItems[10].quantity = 1; invItems[10].type = "Consumable"; invItems[10].healthRegen = 5; invItems[10].consumable = true; invItems[10].desc = "Heals for 5HP when used";



	enemy[0].health = 10; enemy[0].name = "Skeletal"; enemy[0].damage = 1; enemy[0].xpGain = 100, enemy[0].maxHealth = 10; enemy[0].drop = 10; enemy[0].hasDrop = true; enemy[0].dropAmount = 2; enemy[0].potentialLoot = 2;
	enemy[1].health = 16; enemy[1].name = "Skeletal King"; enemy[1].damage = 2; enemy[1].xpGain = 100, enemy[1].maxHealth = 16; enemy[1].drop = 9; enemy[1].hasDrop = true; enemy[1].dropAmount = 1; enemy[1].potentialLoot = 4;

	equipedWeapon = 1;

	//Config
	gameName	= "Lonewolf";
	version		= "1.4";

	mainMenu(gameName, version);

	greeting();

	cout << endl << "Please enter your name:" << endl;

	cin >> name;

	system("cls");

	greeting();

	cout << "Welcome, " << name << "!\nWhen you are ready, " << endl;

	system("pause&cls");

	quest1();

	drawInventory();

	quest2();
	
	system("pause");
}
