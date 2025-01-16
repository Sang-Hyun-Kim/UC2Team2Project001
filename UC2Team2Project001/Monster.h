#pragma once

#include "Character.h"

class Monster : public Character, public enable_shared_from_this<Monster>
{
public:
	Monster();

	virtual  void Initialize() override;

	//Character();

	//Character(const string& _name);


	bool IsBoss() const;

	// 처치 보상 생성
	virtual void CreateCharacterReward() override;

public:
	void SetMonsterStat(int PlayerLevel);

	void SetBlance(Character* Player);

private:
	// 몬스터 이름 결정
	std::string DetermineMonsterName(int _playerLevel);

	// 스탯 계산
	void AdjustStatsForLevel(const StatsData& baseStats, int playerLevel);


private:
	bool bIsBoss = false;

	int balanceLevel = 4;
};