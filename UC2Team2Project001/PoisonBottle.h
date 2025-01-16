#pragma once
#include "ThrowableItem.h"

class PoisonBottle : public ThrowableItem
{
public:
	PoisonBottle(int _id);

	bool use(Character* _owner) override;
	shared_ptr<Item> clone() const;
};

