#pragma once
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <iostream>

class Character;

// enum 혹은 문자열 키로 구분
enum class StatType
{
	HP,
	MaxHP,
	MP,
	MaxMP,
	AttackPower,
	Defense,
	CriticalChance,
	EvasionRate,
	// ... 필요한 스탯들 추가
};

class UStatsComponent
{
public:
	UStatsComponent(Character* InOwnedCharacter);	

	~UStatsComponent();

	// 스탯 접근/설정 함수
	float GetStat(StatType type) const;

	void SetStat(StatType type, float value);

	void ModifyStat(StatType type, float delta);

	bool IsDead();

	void PrintStatus();

private:
	Character* OwnedCharacter;

	std::map<StatType, float> Stats;
};
