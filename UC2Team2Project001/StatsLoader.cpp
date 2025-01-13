#include "pch.h"
#include "StatsLoader.h"

const std::string DefaultFileName = "CharacterStat.json";
//const std::string DefaultFileName = "ItemData.json";


StatsData StatsLoader::LoadFromJSON(const std::string& characterName) 
{
	std::ifstream file(DefaultFileName);
	if (!file.is_open()) {
		throw std::runtime_error("JSON 파일을 열 수 없습니다: " + DefaultFileName);
	}

	json jsonData;
	file >> jsonData;

	// 디버깅: JSON 데이터를 출력
	//std::cout << "JSON 데이터 로드 완료:\n" << jsonData.dump(4) << "\n";

	if (!jsonData.contains("Characters")) {
		throw std::runtime_error("JSON 파일에 'Characters' 키가 없습니다.");
	}

	const auto& characters = jsonData["Characters"];
	if (!characters.contains(characterName)) 
	{
		throw std::runtime_error("캐릭터 이름 '" + characterName + "'에 해당하는 데이터가 없습니다.");
	}

	const auto& statsData = characters[characterName]["Stats"];
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

	stats.AttackStrategyData = characters[characterName]["AttackStrategy"];
	stats.DefenseStrategyData = characters[characterName]["DefenseStrategy"];

	return stats;
}


void StatsLoader::SaveToJSON(const StatsData& stats, const std::string& characterName)
{
	std::ifstream file(DefaultFileName);
	json jsonData;

	if (file.is_open())
	{
		file >> jsonData;
		file.close();
	}

	auto& characterData = jsonData["Characters"][characterName];
	auto& statsData = characterData["Stats"];
	statsData["HP"] = stats.HP;
	statsData["MaxHP"] = stats.MaxHP;
	statsData["MP"] = stats.MP;
	statsData["MaxMP"] = stats.MaxMP;
	statsData["AttackPower"] = stats.AttackPower;
	statsData["Defense"] = stats.Defense;
	statsData["CriticalChance"] = stats.CriticalChance;
	statsData["EvasionRate"] = stats.EvasionRate;
	statsData["Level"] = stats.Level;
	statsData["Experience"] = stats.Experience;
	statsData["MaxExperience"] = stats.MaxExperience;

	// 공격 전략과 방어 전략 저장
	characterData["AttackStrategy"] = stats.AttackStrategyData;
	characterData["DefenseStrategy"] = stats.DefenseStrategyData;

	// JSON 저장
	std::ofstream outFile(DefaultFileName);
	if (!outFile.is_open())
	{
		throw std::runtime_error("JSON 파일을 저장할 수 없습니다: " + DefaultFileName);
	}
	outFile << jsonData.dump(4); // 4칸 들여쓰기
}
