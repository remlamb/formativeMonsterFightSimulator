#include "FightSimulator.h"
#include <stdlib.h>

Monster FightSimulator::CreateMonster() {
	
	int race;
	float hp, ad, dp, speed;

	std::cout << "Monster Creation : Monster need a race, HealtPoint, Attack, Defense and Speed" << std::endl;
	std::cout << "Input a number to choose a race : 1 for Orc, 2 for Troll, 3 for Goblin" << std::endl;
	std::cin >> race;
	while (race > 3 || race <= 0) { 
		std::cout << "Please retry : 1 for Orc, 2 for Troll, 3 for Goblin" << std::endl;
		std::cin >> race;
	}

	std::cout << "Enter Health Point (max 80):				/use 0 to roll ten dice" << std::endl;
	std::cin >> hp;
	while (!checkedStat(hp, 80)) {
		std::cout << "Please retry, Health Point :			max80 or use 0 to roll dices" << std::endl;
		std::cin >> hp;
	}
	randomValue(hp, 10, 60); //simulates 10 roll dice

	std::cout << "Enter Attack Point (max40):				/use 0 to roll two dice" << std::endl;
	std::cin >> ad;
	while (!checkedStat(ad, 40)) {
		std::cout << "Please retry, Attack Point :			max40 or use 0 to roll dices" << std::endl;
		std::cin >> ad;
	}
	randomValue(ad, 2, 12); //simulates 2 roll dice


	std::cout << "Enter Defense Point (max20):				/use 0 to roll one dice" << std::endl;
	std::cin >> dp;
	while (!checkedStat(dp, 20)) {
		std::cout << "Please retry, Defense Point :			max20 or use 0 to roll dice" << std::endl;
		std::cin >> dp;
	}
	randomValue(dp, 1, 6); //simulates 1 roll dice

	std::cout << "Enter Speed (max10):						/use 0 to roll one dice" << std::endl;
	std::cin >> speed;
	while (!checkedStat(speed, 10)) {
		std::cout << "Please retry, Speed Point :			max10 or use 0 to roll dice" << std::endl;
		std::cin >> speed;
	}
	randomValue(speed, 1, 6); //simulates 1 roll dice
	

	Monster createMonster(race, hp, ad, dp, speed);
	clearConsole();
	createMonster.ShowStat();
	return createMonster;

}

void FightSimulator::MonsterFight(Monster firstMonster, Monster secondMonster) {
	
	int round = 0;
	clearConsole();
	//show Fighters stat
	std::cout << std::endl << "FIGHTERS " <<std::endl;
	firstMonster.ShowStat();
	secondMonster.ShowStat();

	//avoid fight if fighters got same race
	if (checkedSameRaceFight(firstMonster, secondMonster)) {
		returnToMenu();
		return;
	}

	//Special mode to avoid an infinite combat because of enemy def > current attack
	if (firstMonster.isEnemyDefTooStrong(secondMonster) && secondMonster.isEnemyDefTooStrong(firstMonster)) {
		std::cout << "Sudden Death:				no defense point " << std::endl;
		firstMonster.avoidDefense();
		secondMonster.avoidDefense();
	}

	//Turn based fighting systeme
	bool firstMonsterIsAttacking;
	if (firstMonsterIsFaster(firstMonster, secondMonster)) {
		firstMonsterIsAttacking = true;
	}
	else {
		firstMonsterIsAttacking = false;
	}
	
	while (!firstMonster.isDead() && !secondMonster.isDead()) {
		round++;
		std::cout << "Round " << round << std::endl;
		if (firstMonsterIsAttacking) {

			firstMonster.Attack(secondMonster);
			firstMonsterIsAttacking = false;
			std::cout << firstMonster.RaceToString() << " is attacking, ";
			std::cout << "Hp " << secondMonster.RaceToString() << " : ";
			secondMonster.printHP();
			std::cout << std::endl;
		}
		else{
			secondMonster.Attack(firstMonster);
			firstMonsterIsAttacking = true;
			std::cout << secondMonster.RaceToString() << " is attacking, ";
			std::cout << "Hp " << firstMonster.RaceToString() << " : ";
			firstMonster.printHP();
			std::cout << std::endl;
		}
	}

	//print winner and round
	std::cout << std::endl;
	std::cout << "The fight lasted " << round << " rounds and" << std::endl;
	std::cout << "Winner is : " << std::endl;
	printWinner(firstMonster, secondMonster);

	returnToMenu();
}

void FightSimulator::Menu() {
	std::cout <<"--- MONSTER FIGHT SIMULATOR ---" << std::endl;
	std::cout << "Create two monster and watch them fighting" << std::endl << std::endl;
	int currentChoice;
	std::cout << "- Press 1 to start" << std::endl << "- Anything else to exit" << std::endl;
	std::cin >> currentChoice;
	if (currentChoice == 1) {
		clearConsole();
		MonsterFight(CreateMonster(), CreateMonster());
	}
	else {
		clearConsole();
	}
}

void FightSimulator::clearConsole() {
	std::cout << "\x1B[2J\x1B[H";
}

bool FightSimulator::checkedSameRaceFight(Monster firstMonster, Monster secondMonster) {
	if (firstMonster.getRace() == secondMonster.getRace()) {
		std::cout << "Fight impossible, Same race" << std::endl;
		return true;
	}
	else {
		return false;
	}
}

bool FightSimulator::firstMonsterIsFaster(Monster firstMonster, Monster secondMonster) {
	return firstMonster.getSpeed() > secondMonster.getSpeed();
}

void FightSimulator::printWinner(Monster firstMonster, Monster secondMonster) {
	if (firstMonster.isDead()) {
		secondMonster.ShowStat();
	}
	else {
		firstMonster.ShowStat();
	}
}

void FightSimulator::randomValue(float& value, int min,  int max) {
	if (value == 0) {
		value = rand() % max + min;
	 }
}

bool FightSimulator::checkedStat(float value, float maxStat) {
	return value <= maxStat && value >= 0;
}

void FightSimulator::returnToMenu(){
	int currentChoice;
	std::cout << "press 1 to return in main menu, anything else to quit" << std::endl;
	std::cin >> currentChoice;
	if (currentChoice == 1) {
		clearConsole();
		Menu();
	}
	else {
		clearConsole();
	}
}

