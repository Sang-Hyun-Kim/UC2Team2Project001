#pragma once

#include "Potion.h"
class AttackBoostPotion : public Potion
{
public:
	AttackBoostPotion();

	void use(Character& Target) override;
};

