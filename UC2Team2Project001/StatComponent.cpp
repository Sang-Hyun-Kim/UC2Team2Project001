#include "pch.h"

#include "StatComponent.h"
#include "Character.h"
#include "GlobalEventManager.h"


#include <fstream>
#include "StatsLoader.h"
#include "ICharacterEventTypes.h"
#include "USkillComponent.h"

UStatsComponent::UStatsComponent(Character* _inOwnedCharacter)
{
	ownedCharacter = _inOwnedCharacter;
}

void UStatsComponent::BeginPlay()
{
	if (!ownedCharacter)
	{
		std::cerr << "Error: OwnedCharacter가 없습니다!" << std::endl;
		return;
	}
}

void UStatsComponent::Initialize(StatsData _loadStatsData)
{
	// 스탯 설정
	SetStat(StatType::HP, _loadStatsData.HP);
	SetStat(StatType::MaxHP, _loadStatsData.MaxHP);
	SetStat(StatType::MP, _loadStatsData.MP);
	SetStat(StatType::MaxMP, _loadStatsData.MaxMP);
	SetStat(StatType::AttackPower, _loadStatsData.AttackPower);
	SetStat(StatType::Defense, _loadStatsData.Defense);
	SetStat(StatType::CriticalChance, _loadStatsData.CriticalChance);
	SetStat(StatType::EvasionRate, _loadStatsData.EvasionRate);
	SetStat(StatType::Level, _loadStatsData.Level);
	SetStat(StatType::Experience, _loadStatsData.Experience);
	SetStat(StatType::MaxExperience, _loadStatsData.MaxExperience);
	PrintStatus();
}

UStatsComponent::~UStatsComponent()
{
}

void UStatsComponent::LoadFromJSON()
{
	// OwnerCharacter의 이름을 가져옴
	std::string characterName = ownedCharacter->GetName();

	try
	{
		// StatsLoader를 통해 JSON에서 스탯 로드
		StatsData statsData = StatsLoader::LoadFromJSON(characterName);

		// Stats 맵 초기화
		stats[StatType::HP] = statsData.HP;
		stats[StatType::MaxHP] = statsData.MaxHP;
		stats[StatType::MP] = statsData.MP;
		stats[StatType::MaxMP] = statsData.MaxMP;
		stats[StatType::AttackPower] = statsData.AttackPower;
		stats[StatType::Defense] = statsData.Defense;
		stats[StatType::CriticalChance] = statsData.CriticalChance;
		stats[StatType::EvasionRate] = statsData.EvasionRate;
		stats[StatType::Level] = statsData.Level;
		stats[StatType::Experience] = statsData.Experience;
		stats[StatType::MaxExperience] = statsData.MaxExperience;

		// 스탯 출력 (테스트용)
		PrintStatus();
	}
	catch (const std::exception& _exception)
	{
		std::cerr << "캐릭터에 대한 통계를 로드하는 중 오류가 발생했습니다.'" << characterName << "': " << _exception.what() << std::endl;
	}
}

float UStatsComponent::GetStat(StatType _type) const
{
	auto it = stats.find(_type);
	if (it != stats.end())
		return it->second;
	return 0.0f;
}

void UStatsComponent::SetStat(StatType _type, float _value)
{
	stats[_type] = _value;
}

void UStatsComponent::ModifyStat(StatType _type, float _delta)
{
	stats[_type] += _delta;

	if (stats[_type] < 0)
	{
		stats[_type] = 0;
	}

	if (_type == StatType::HP || _type == StatType::MP)
	{
		ClampStat(_type, 0.0f, GetStat(_type == StatType::HP ? StatType::MaxHP : StatType::MaxMP));

		if (_type == StatType::HP && stats[_type] == 0)
		{
			// 불굴의 의지가 있는지 확인
			if (!ownedCharacter->skillManager->GetSkill(SkillType::PASSIVE, "불굴의 의지"))
			{
				// 캐릭터 사망 이벤트
				auto newCharacterDeadEvent = std::make_shared<ICharacterDeadEvent>(ownedCharacter->GetName(), ownedCharacter->characterReward);
				GlobalEventManager::Get().Notify(newCharacterDeadEvent);
			}
			else
			{
				// 캐릭터 스탯 0 이벤트
				auto characterStatZeroEvent = std::make_shared<ICharacterStatZeroEvent>(ownedCharacter->GetName());
				GlobalEventManager::Get().Notify(characterStatZeroEvent);
			}
		}
	}
	else if (_type == StatType::Experience)
	{
		float currentExp = stats[StatType::Experience];
		float maxExp = stats[StatType::MaxExperience];

		// 여러 레벨이 한 번에 오를 수 있으면 while 사용
		while (currentExp >= maxExp)
		{
			// 남는 경험치 계산 (예: 120 / 100 -> 남는 20)
			float leftover = currentExp - maxExp;
			stats[StatType::Experience] = leftover;

			// 레벨 업 실행
			LevelUp();

			// 레벨업 후, maxExp 값이 바뀔 수 있으므로 다시 읽어옴
			currentExp = stats[StatType::Experience];
			maxExp = stats[StatType::MaxExperience];
		}
	}
}

bool UStatsComponent::IsDead()
{
	return (stats[StatType::HP] <= 0);
}

void UStatsComponent::PrintStatus()
{
	std::cout << "================ Character Status ================\n";
	std::cout << "Name: " << (ownedCharacter ? ownedCharacter->GetName(): "None") << "\n";
	std::cout << "Level: " << stats[StatType::Level] << "\n";
	std::cout << "Experience: " << stats[StatType::Experience]
		<< " / " << stats[StatType::MaxExperience] << "\n";
	std::cout << "HP: " << stats[StatType::HP]
		<< " / " << stats[StatType::MaxHP] << "\n";
	std::cout << "MP: " << stats[StatType::MP]
		<< " / " << stats[StatType::MaxMP] << "\n";
	std::cout << "Attack Power: " << stats[StatType::AttackPower] << "\n";
	std::cout << "Defense: " << stats[StatType::Defense] << "\n";
	std::cout << "Critical Chance: " << (stats[StatType::CriticalChance] * 100) << "%\n";
	std::cout << "Evasion Rate: " << (stats[StatType::EvasionRate] * 100) << "%\n";
	std::cout << "==================================================\n";
	cout << endl;
}

void UStatsComponent::LevelUp()
{
	// 레벨 증가
	stats[StatType::Level] += 1;

	// 체력/최대체력 증가
	stats[StatType::MaxHP] += 10;
	// 체력은 새로 오른 최대체력으로 보충
	stats[StatType::HP] = stats[StatType::MaxHP];

	// MP/최대MP 증가
	stats[StatType::MaxMP] += 5;
	stats[StatType::MP] = stats[StatType::MaxMP];

	// 공격력 증가
	stats[StatType::AttackPower] += 2;

	// 방어력 증가
	stats[StatType::Defense] += 1;

	// 다음 레벨에 필요한 경험치 증가(예: +50)
	stats[StatType::MaxExperience] += 50;

	// 레벨업 시점에 메시지 출력 (UI 이벤트를 보낼 수도 있음)
	auto NewLevelUpEvent = make_shared<ICharacterLevelUpEvent>(ownedCharacter->GetName(), (int)stats[StatType::Level]);
	GlobalEventManager::Get().Notify(NewLevelUpEvent);
}

void UStatsComponent::ClampStat(StatType _type, float _minValue, float _maxValue)
{
	stats[_type] = std::clamp(stats[_type], _minValue, _maxValue);
}
