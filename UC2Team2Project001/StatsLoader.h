#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct StatsData
{
	float HP;
	float MaxHP;
	float MP;
	float MaxMP;
	float AttackPower;
	float Defense;
	float CriticalChance;
	float EvasionRate;
	float Level;
	float Experience;
	float MaxExperience;

	json AttackStrategyData;
	json DefenseStrategyData;
};

class StatsLoader
{
public:
	// 특정 캐릭터 데이터를 로드
	static StatsData LoadFromJSON(const std::string& _characterName);

	// 특정 캐릭터 데이터를 저장
	static void SaveToJSON(const StatsData& _stats, const std::string& _characterName);
};
