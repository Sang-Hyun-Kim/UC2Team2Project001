#pragma once

class Item;

struct FCharacterReward
{
	int dropGold = 0;

	int dropExperience = 0;

	shared_ptr<Item> dropItem = nullptr;

	FCharacterReward()
	{
	}

	FCharacterReward(int _inDropGold, shared_ptr<Item> _inDropItem) : dropGold(_inDropGold), dropItem(_inDropItem) {}

	// 골드 = 0 / 아이템 = nullptr => true
	bool IsEmpty() const;
};

