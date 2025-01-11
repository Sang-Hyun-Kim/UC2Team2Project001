#pragma once

#include "Potion.h"
class AttackBoost : public Potion
{
	AttackBoost();

	void use(Character& Target) override;
};

