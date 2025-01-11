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
};

class StatsLoader
{
public:
	// 특정 캐릭터 데이터를 로드
	static StatsData LoadFromJSON(const std::string& characterName);

	// 특정 캐릭터 데이터를 저장
	static void SaveToJSON(const StatsData& stats, const std::string& characterName);
};
