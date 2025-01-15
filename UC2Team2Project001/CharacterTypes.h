#pragma once

class Item;

struct FCharacterReward
{
	int DropGold = 0;

	shared_ptr<Item> DropItem = nullptr;

	FCharacterReward() {}

	FCharacterReward(int InDropGold, shared_ptr<Item> InDropItem) : DropGold(InDropGold), DropItem(InDropItem) {}

	// 골드 = 0 / 아이템 = nullptr => true
	bool IsEmpty() const;
};

