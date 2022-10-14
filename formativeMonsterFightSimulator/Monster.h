#pragma once
#include <iostream>

enum class Race {
	Orc = 1,
	Troll,
	Goblin,
};


class Monster
{
private:
	float _healthPoint, _attackDamage, _defensePoint, _speed;
	Race _Race;

public:

	std::string RaceToString();	
	Monster(int, float, float, float, float);
	void Attack(Monster&);
	void ShowStat();	//print all stats
	float getDefensePoint();
	float getSpeed();
	Race getRace();
	bool isDead();
	void takeDamage(float);

	bool isEnemyDefTooStrong(Monster);	//true if monster can t attack because of the enemy defense point
	void avoidDefense();	//set defense to 0		//use if combat impossible because both monster had def > enemy attack
	void printHP(); //print | for all hp point	//use to create an Health Bar

};

