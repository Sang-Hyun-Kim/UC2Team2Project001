#pragma once

#include "Character.h"

class Monster : Character
{
private:
	bool IsBoss;

public:
	Monster(const string& InName, int InHP, int InMaxHP, int InAttack, int InDefense);
	Monster(const string& InName, int InHP, int InMaxHP, int InAttack, int InDefense, int level);

	
};