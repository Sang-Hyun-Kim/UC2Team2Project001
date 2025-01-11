#pragma once

#include "Character.h"

class Monster : public Character
{
private:
	bool bIsBoss;

	// 처치후 보상으로 얻을 골드와 아이템
	int Gold;
	//shared_ptr<Item> Item;
public:
	Monster(int PlayerLevel);

	void SetMonsterStat(int PlayerLevel);

	bool IsBoss() const;

	// 처치 보상 골드
	int GetGold() const;
	
	// 처치 아이템 골드
	//shared_ptr<Item> GetItem() const;
};