#pragma once
#include "ThrowableItem.h"
class FireBottle :public ThrowableItem
{
public:
	FireBottle(int _id);

	bool use(Character* _owner) override;
	shared_ptr<Item> clone() const;
};