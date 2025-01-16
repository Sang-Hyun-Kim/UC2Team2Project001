#pragma once

#include "Potion.h"
class AttackBoostPotion : public Potion
{
public:
	AttackBoostPotion(int _id);

	bool use(Character* _target) override;
	shared_ptr<Item> clone() const;
};