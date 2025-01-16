#pragma once

#include "Character.h"

class Monster : public Character, public enable_shared_from_this<Monster>
{
private:
	vector<string> monsterNames{ "Dragon", "Goblin", "Orc", "Troll" };

	bool isBoss;

	void SetMonsterStat(int _playerLevel);

	int blanceLevel = 8;

	void SetBlance(Character* _player);
public:
	Monster();

	virtual  void Initialize() override;

	//Character();

	//Character(const string& _name);


	bool IsBoss() const;

	// 처치 보상 생성
	virtual void CreateCharacterReward() override;
};