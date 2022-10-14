#pragma once
#include "Monster.h"

class FightSimulator
{
public:

	Monster CreateMonster();
	void MonsterFight(Monster, Monster);

	void Menu();
	void clearConsole();

	bool checkedSameRaceFight(Monster, Monster);
	bool firstMonsterIsFaster(Monster, Monster);
	void printWinner(Monster, Monster);

	void randomValue(float&, int, int);	//use to simulate a special dice roll if input = 0, ints are the range of the rand fonction		//we use 0 as input so it s impossible to use it as a stat
	bool checkedStat(float, float);	//get input and check if it s between 0 and an other float as max stat 

	void returnToMenu();
};

