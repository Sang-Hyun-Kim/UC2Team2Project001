#pragma once

#include "StatType.h"

class Character;

class CharacterUtility
{
public:
	static bool IsDead(Character* _character);

	static float GetStat(Character* _character, StatType _type);

	static void ModifyStat(Character* _character, StatType _type, float _delta);

	static void PrintStatus(Character* _character);
};

