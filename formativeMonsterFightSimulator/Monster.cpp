#include "Monster.h"

std::string Monster::RaceToString() {
	switch (_Race) {
	case Race::Orc:
		return "Orc";

	case Race::Troll:
		return "Troll";

	case Race::Goblin:
		return "Goblin";

	default:
		break;
	}
};

Monster::Monster(int raceId, float hp, float ad, float dp, float speed) {
	_Race = Race(raceId);
	_healthPoint = hp;
	_attackDamage = ad;
	_defensePoint = dp;
	_speed = speed;
};

void Monster::Attack(Monster& defendingMonster) {
	float damage = _attackDamage - defendingMonster.getDefensePoint();
	if (damage < 0) {
		return;
	}
	defendingMonster.takeDamage(damage);
};

void Monster::ShowStat() {
	std::cout << " Race : " << RaceToString() << std::endl;
	std::cout << " HP : " << _healthPoint << std::endl;
	std::cout << " AD : " << _attackDamage << std::endl;
	std::cout << " DP : " << _defensePoint << std::endl;
	std::cout << " Speed : " << _speed << std::endl;
	std::cout << std::endl;
}


float Monster::getDefensePoint() {
	return _defensePoint;
}

float Monster::getSpeed() {
	return _speed;
}

Race Monster::getRace() {
	return _Race;
};

bool Monster::isDead() {
	return _healthPoint <= 0;
}

void Monster::takeDamage(float damage) {
	_healthPoint -= damage;
}

void Monster::printHP() {
	for (int i = 1; i <= _healthPoint; i++) {
		std::cout << "|";
	}
}

bool Monster::isEnemyDefTooStrong(Monster defMonster) {
	return _attackDamage < defMonster.getDefensePoint();
}

void Monster::avoidDefense() {
	_defensePoint = 0;
}


