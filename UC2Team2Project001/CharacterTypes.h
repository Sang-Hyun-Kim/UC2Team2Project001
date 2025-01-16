#pragma once

class Item;

struct FCharacterReward
{
public:
	int DropGold = 0;

	int DropExperience = 0;

	shared_ptr<Item> DropItem = nullptr;

public:
	FCharacterReward() {}

	FCharacterReward(int InDropGold, shared_ptr<Item> InDropItem) : DropGold(InDropGold), DropItem(InDropItem) {}

	// 골드 = 0 / 아이템 = nullptr => true
	bool IsEmpty() const;
};

