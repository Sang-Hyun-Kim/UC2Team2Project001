#pragma once
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
	Level,
	Experience,
	MaxExperience
	// ... 필요한 스탯들 추가
};



class UStatsComponent
{
public:
	UStatsComponent(Character* InOwnedCharacter);

	virtual void BeginPlay();

	~UStatsComponent();

	void LoadFromJSON();

	// 스탯 접근/설정 함수
	float GetStat(StatType type) const;

	void SetStat(StatType type, float value);

	// 스탯 증감 (경험치 증가 시 레벨업 체크)
	void ModifyStat(StatType type, float delta);

	// 사망 판정
	bool IsDead();

	// 현재 스탯 콘솔 출력
	void PrintStatus();

	// 레벨 업 기능
	void LevelUp();


protected:
	void ClampStat(StatType type, float minValue, float maxValue);
	
public:
	bool bIsLoadJson = true;

private:
	Character* OwnedCharacter;

	std::map<StatType, float> Stats;
	
};
