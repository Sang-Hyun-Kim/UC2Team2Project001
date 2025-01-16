#pragma once
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include "StatType.h"

using json = nlohmann::json;

class Character;
struct StatsData;

class UStatsComponent
{
public:
	UStatsComponent()
	{
	}

	UStatsComponent(Character* _inOwnedCharacter);

	virtual void BeginPlay();

	virtual void Initialize(StatsData _loadStatsData);


	~UStatsComponent();

	void LoadFromJSON();

	// 스탯 접근/설정 함수
	float GetStat(StatType _type) const;

	void SetStat(StatType _type, float _value);

	// 스탯 증감 (경험치 증가 시 레벨업 체크)
	void ModifyStat(StatType _type, float _delta);

	// 사망 판정
	bool IsDead();

	// 현재 스탯 콘솔 출력
	void PrintStatus();

	// 레벨 업 기능
	void LevelUp();


protected:
	void ClampStat(StatType _type, float _minValue, float _maxValue);

private:
	Character* ownedCharacter;

	std::map<StatType, float> stats;
};
