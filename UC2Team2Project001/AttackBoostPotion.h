#pragma once

#include "Potion.h"
class AttackBoostPotion : public Potion
{
public:
	AttackBoostPotion();

	void use(Character* _target) override;
	shared_ptr<Item> clone() const;
};

