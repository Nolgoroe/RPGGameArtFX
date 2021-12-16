#pragma once

#include "Character.h"

class Hero : public Character
{
public:
	Hero();
	~Hero();

	void healAction(int _healAmount);
	void atkBooseAction(int _atkBooseAmount);
	void defBooseAction(int _defBooseAmount);
};

