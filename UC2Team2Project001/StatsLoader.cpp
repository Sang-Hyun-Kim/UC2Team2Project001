#include "pch.h"
#include "StatsLoader.h"

const std::string DefaultFileName = "CharacterStat.json";


StatsData StatsLoader::LoadFromJSON(const std::string& characterName)
{
	std::ifstream file(DefaultFileName);
	if (!file.is_open())
	{
		throw std::runtime_error("JSON 파일을 열 수 없습니다: " + DefaultFileName);
	}

	json jsonData;
	file >> jsonData;

	if (!jsonData.contains("Characters"))
	{
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

	return stats;
}

void StatsLoader::SaveToJSON(const StatsData& stats, const std::string& characterName)
{
	std::ifstream file(DefaultFileName);
	json jsonData;

	// 기존 JSON 데이터를 읽어옴
	if (file.is_open())
	{
		file >> jsonData;
	}
	file.close();

	// "Characters" 키가 없으면 생성
	if (!jsonData.contains("Characters"))
	{
		jsonData["Characters"] = json::object();
	}

	// 캐릭터 데이터 저장
	jsonData["Characters"][characterName]["Stats"]["HP"] = stats.HP;
	jsonData["Characters"][characterName]["Stats"]["MaxHP"] = stats.MaxHP;
	jsonData["Characters"][characterName]["Stats"]["MP"] = stats.MP;
	jsonData["Characters"][characterName]["Stats"]["MaxMP"] = stats.MaxMP;
	jsonData["Characters"][characterName]["Stats"]["AttackPower"] = stats.AttackPower;
	jsonData["Characters"][characterName]["Stats"]["Defense"] = stats.Defense;
	jsonData["Characters"][characterName]["Stats"]["CriticalChance"] = stats.CriticalChance;
	jsonData["Characters"][characterName]["Stats"]["EvasionRate"] = stats.EvasionRate;
	jsonData["Characters"][characterName]["Stats"]["Level"] = stats.Level;
	jsonData["Characters"][characterName]["Stats"]["Experience"] = stats.Experience;
	jsonData["Characters"][characterName]["Stats"]["MaxExperience"] = stats.MaxExperience;

	// JSON 데이터를 파일에 저장
	std::ofstream outFile(DefaultFileName);
	if (!outFile.is_open())
	{
		throw std::runtime_error("쓰기를 위해 파일을 열 수 없습니다: " + DefaultFileName);
	}

	outFile << jsonData.dump(4); // 4칸 들여쓰기
	outFile.close();
}

