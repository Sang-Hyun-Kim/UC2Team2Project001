#pragma once

#include "Potion.h"
class AttackBoostPotion : public Potion
{
	AttackBoostPotion();

	void use(Character& Target) override;
};

