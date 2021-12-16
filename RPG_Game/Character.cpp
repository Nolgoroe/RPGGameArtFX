#include "Character.h"



Character::Character()
{
}


Character::~Character()
{
}

void Character::setupStats(int _hp, int _str, int _def, int _agi)
{
	hp = _hp;
	hpMax = _hp;
	str = _str;
	def = _def;
	agi = _agi;
}

void Character::displayStats(){
	cout << "NAME " << getName() << endl;
	cout << "HP " << hp << "/" << hpMax << endl;
	cout << "STR: " << str << endl;
	cout << "DEF: " << def << endl;
	cout << "AGI: " << agi << endl;
}

int Character::getHP()
{
	return hp;
}

int Character::getHPMax()
{
	return hpMax;
}

int Character::getAGI()
{
	return agi;
}

int Character::getSTR()
{
	return str;
}

void Character::takeDamage(int dmg)
{
	int dmgAfterDefence = dmg - def;

	if (dmgAfterDefence < 1) 
	{
		dmgAfterDefence = 0;
	}

	hp -= dmgAfterDefence;
}

void Character::setName(string _name)
{
	characterName = _name;
}

string Character::getName()
{
	return characterName;
}
