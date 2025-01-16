#include "pch.h"
#include "StatsLoader.h"
#include <iostream>

const std::string defaultFileName = "CharacterStat.json";
//const std::string DefaultFileName = "ItemData.json";


StatsData StatsLoader::LoadFromJSON(const std::string& _characterName)
{
	std::ifstream file(defaultFileName);
	if (!file.is_open()) {
		throw std::runtime_error("JSON 파일을 열 수 없습니다: " + defaultFileName);
	}

	json jsonData;
	file >> jsonData;

	// 디버깅: JSON 데이터를 출력
	//std::cout << "JSON 데이터 로드 완료:\n" << jsonData.dump(4) << "\n";

	if (!jsonData.contains("Characters")) {
		throw std::runtime_error("JSON 파일에 'Characters' 키가 없습니다.");
	}

	const auto& characters = jsonData["Characters"];
	if (!characters.contains(_characterName))
	{
		std::cerr << "캐릭터 이름 '" + _characterName + "'에 해당하는 데이터가 없습니다.";
	}

	const auto& statsData = characters[_characterName]["Stats"];
	StatsData stats;
	stats.HP = statsData.value("HP", 0.0f);
	stats.MaxHP = statsData.value("MaxHP", 0.0f);
	stats.MP = statsData.value("MP", 0.0f);
	stats.MaxMP = statsData.value("MaxMP", 0.0f);
	stats.AttackPower = statsData.value("AttackPower", 0.0f);
	stats.Defense = statsData.value("Defense", 0.0f);
	stats.CriticalChance = statsData.value("CriticalChance", 0.0f);
	stats.EvasionRate = statsData.value("EvasionRate", 0.0f);
	stats.Level = statsData.value("Level", 0.0f);
	stats.Experience = statsData.value("Experience", 0.0f);
	stats.MaxExperience = statsData.value("MaxExperience", 0.0f);

	stats.AttackStrategyData = characters[_characterName]["AttackStrategy"];
	stats.DefenseStrategyData = characters[_characterName]["DefenseStrategy"];

	return stats;
}


void StatsLoader::SaveToJSON(const StatsData& _stats, const std::string& _characterName)
{
	std::ifstream file(defaultFileName);
	json jsonData;

	if (file.is_open())
	{
		file >> jsonData;
		file.close();
	}

	auto& characterData = jsonData["Characters"][_characterName];
	auto& statsData = characterData["Stats"];
	statsData["HP"] = _stats.HP;
	statsData["MaxHP"] = _stats.MaxHP;
	statsData["MP"] = _stats.MP;
	statsData["MaxMP"] = _stats.MaxMP;
	statsData["AttackPower"] = _stats.AttackPower;
	statsData["Defense"] = _stats.Defense;
	statsData["CriticalChance"] = _stats.CriticalChance;
	statsData["EvasionRate"] = _stats.EvasionRate;
	statsData["Level"] = _stats.Level;
	statsData["Experience"] = _stats.Experience;
	statsData["MaxExperience"] = _stats.MaxExperience;

	// 공격 전략과 방어 전략 저장
	characterData["AttackStrategy"] = _stats.AttackStrategyData;
	characterData["DefenseStrategy"] = _stats.DefenseStrategyData;

	// JSON 저장
	std::ofstream outFile(defaultFileName);
	if (!outFile.is_open())
	{
		throw std::runtime_error("JSON 파일을 저장할 수 없습니다: " + defaultFileName);
	}
	outFile << jsonData.dump(4); // 4칸 들여쓰기
}
