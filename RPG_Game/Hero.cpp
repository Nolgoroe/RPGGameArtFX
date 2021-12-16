#include "Hero.h"



Hero::Hero()
{
}


Hero::~Hero()
{
}

void Hero::healAction(int _healAmount)
{
	hp += _healAmount;

	if (hp > hpMax)
	{
		hp = hpMax;
	}
}

void Hero::atkBooseAction(int _atkBooseAmount)
{
	str += _atkBooseAmount;
}

void Hero::defBooseAction(int _defBooseAmount)
{
	def += _defBooseAmount;
}
