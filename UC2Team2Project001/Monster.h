#pragma once

#include "Character.h"

class Monster : public Character
{
private:
	vector<string> MonsterNames{ "Dragon", "Goblin", "Orc", "Troll" };

	bool bIsBoss;

	void SetMonsterStat(int PlayerLevel);

public:
	Monster(int PlayerLevel);

	bool IsBoss() const;

	// 처치 보상 생성
	virtual void CreateCharacterReward() override;
};