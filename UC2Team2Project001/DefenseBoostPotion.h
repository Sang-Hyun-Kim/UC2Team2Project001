#pragma once

#include "Potion.h"
class DefenseBoostPotion : public Potion
{
public:
	DefenseBoostPotion(int _id);

	bool use(Character* _target) override;
	shared_ptr<Item> clone() const;
};

