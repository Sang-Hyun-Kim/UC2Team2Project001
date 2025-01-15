#pragma once

#include "Character.h"

class Monster : public Character, public enable_shared_from_this<Monster>
{
private:
	vector<string> MonsterNames{ "Dragon", "Goblin", "Orc", "Troll" };

	bool bIsBoss;

	void SetMonsterStat(int PlayerLevel);

	

	int blanceLevel = 4;

	void SetBlance(Character* Player);
public:
	Monster();

	virtual  void Initialize() override;

	//Character();

	//Character(const string& _name);


	bool IsBoss() const;

	// 처치 보상 생성
	virtual void CreateCharacterReward() override;
};