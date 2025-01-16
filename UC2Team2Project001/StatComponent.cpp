#include "pch.h"

#include "StatComponent.h"
#include "Character.h"
#include "GlobalEventManager.h"


#include <fstream>
#include "StatsLoader.h"
#include "ICharacterEventTypes.h"
#include "USkillComponent.h"

UStatsComponent::UStatsComponent(Character* InOwnedCharacter)
{
	OwnedCharacter = InOwnedCharacter;
}

void UStatsComponent::BeginPlay()
{
	if (!OwnedCharacter)
	{
		std::cerr << "Error: OwnedCharacter가 없습니다!" << std::endl;
		return;
	}
}

void UStatsComponent::Initialize(StatsData LoadStatsData)
{
	// 스탯 설정
	SetStat(StatType::HP, LoadStatsData.HP);
	SetStat(StatType::MaxHP, LoadStatsData.MaxHP);
	SetStat(StatType::MP, LoadStatsData.MP);
	SetStat(StatType::MaxMP, LoadStatsData.MaxMP);
	SetStat(StatType::AttackPower, LoadStatsData.AttackPower);
	SetStat(StatType::Defense, LoadStatsData.Defense);
	SetStat(StatType::CriticalChance, LoadStatsData.CriticalChance);
	SetStat(StatType::EvasionRate, LoadStatsData.EvasionRate);
	SetStat(StatType::Level, LoadStatsData.Level);
	SetStat(StatType::Experience, LoadStatsData.Experience);
	SetStat(StatType::MaxExperience, LoadStatsData.MaxExperience);
	PrintStatus();
}

UStatsComponent::~UStatsComponent()
{
}

void UStatsComponent::LoadFromJSON()
{
	// OwnerCharacter의 이름을 가져옴
	std::string characterName = OwnedCharacter->GetName();

	try
	{
		// StatsLoader를 통해 JSON에서 스탯 로드
		StatsData statsData = StatsLoader::LoadFromJSON(characterName);

		// Stats 맵 초기화
		Stats[StatType::HP] = statsData.HP;
		Stats[StatType::MaxHP] = statsData.MaxHP;
		Stats[StatType::MP] = statsData.MP;
		Stats[StatType::MaxMP] = statsData.MaxMP;
		Stats[StatType::AttackPower] = statsData.AttackPower;
		Stats[StatType::Defense] = statsData.Defense;
		Stats[StatType::CriticalChance] = statsData.CriticalChance;
		Stats[StatType::EvasionRate] = statsData.EvasionRate;
		Stats[StatType::Level] = statsData.Level;
		Stats[StatType::Experience] = statsData.Experience;
		Stats[StatType::MaxExperience] = statsData.MaxExperience;

		// 스탯 출력 (테스트용)
		PrintStatus();
	}
	catch (const std::exception& e)
	{
		std::cerr << "캐릭터에 대한 통계를 로드하는 중 오류가 발생했습니다.'" << characterName << "': " << e.what() << std::endl;
	}
}

float UStatsComponent::GetStat(StatType type) const
{
	auto it = Stats.find(type);
	if (it != Stats.end())
		return it->second;
	return 0.0f;
}

void UStatsComponent::SetStat(StatType type, float value)
{
	Stats[type] = value;
}

void UStatsComponent::ModifyStat(StatType type, float delta)
{
	Stats[type] += delta;

	if (type == StatType::HP || type == StatType::MP)
	{
		ClampStat(type, 0.0f, GetStat(type == StatType::HP ? StatType::MaxHP : StatType::MaxMP));

		if (type == StatType::HP && Stats[type] == 0)
		{
			// 불굴의 의지가 있는지 확인
			if (!OwnedCharacter->skillManager->GetSkill(SkillType::PASSIVE, "불굴의 의지"))
			{
				// 캐릭터 사망 이벤트
				auto NewCharacterDeadEvent = std::make_shared<ICharacterDeadEvent>(OwnedCharacter->GetName(), OwnedCharacter->characterReward);
				GlobalEventManager::Get().Notify(NewCharacterDeadEvent);
			}
			else
			{
				// 캐릭터 스탯 0 이벤트
				auto characterStatZeroEvent = std::make_shared<ICharacterStatZeroEvent>(OwnedCharacter->GetName());
				GlobalEventManager::Get().Notify(characterStatZeroEvent);
			}
		}
	}
	else if (type == StatType::Experience)
	{
		float currentExp = Stats[StatType::Experience];
		float maxExp = Stats[StatType::MaxExperience];

		// 여러 레벨이 한 번에 오를 수 있으면 while 사용
		while (currentExp >= maxExp)
		{
			// 남는 경험치 계산 (예: 120 / 100 -> 남는 20)
			float leftover = currentExp - maxExp;
			Stats[StatType::Experience] = leftover;

			// 레벨 업 실행
			LevelUp();

			// 레벨업 후, maxExp 값이 바뀔 수 있으므로 다시 읽어옴
			currentExp = Stats[StatType::Experience];
			maxExp = Stats[StatType::MaxExperience];
		}
	}
}

bool UStatsComponent::IsDead()
{
	return (Stats[StatType::HP] <= 0);
}

void UStatsComponent::PrintStatus()
{
	std::cout << "================ Character Status ================\n";
	std::cout << "Name: " << (OwnedCharacter ? OwnedCharacter->GetName(): "None") << "\n";
	std::cout << "Level: " << Stats[StatType::Level] << "\n";
	std::cout << "Experience: " << Stats[StatType::Experience]
		<< " / " << Stats[StatType::MaxExperience] << "\n";
	std::cout << "HP: " << Stats[StatType::HP]
		<< " / " << Stats[StatType::MaxHP] << "\n";
	std::cout << "MP: " << Stats[StatType::MP]
		<< " / " << Stats[StatType::MaxMP] << "\n";
	std::cout << "Attack Power: " << Stats[StatType::AttackPower] << "\n";
	std::cout << "Defense: " << Stats[StatType::Defense] << "\n";
	std::cout << "Critical Chance: " << (Stats[StatType::CriticalChance] * 100) << "%\n";
	std::cout << "Evasion Rate: " << (Stats[StatType::EvasionRate] * 100) << "%\n";
	std::cout << "==================================================\n";
	cout << endl;
}

void UStatsComponent::LevelUp()
{
	// 레벨 증가
	Stats[StatType::Level] += 1;

	// 체력/최대체력 증가
	Stats[StatType::MaxHP] += 10;
	// 체력은 새로 오른 최대체력으로 보충
	Stats[StatType::HP] = Stats[StatType::MaxHP];

	// MP/최대MP 증가
	Stats[StatType::MaxMP] += 5;
	Stats[StatType::MP] = Stats[StatType::MaxMP];

	// 공격력 증가
	Stats[StatType::AttackPower] += 2;

	// 방어력 증가
	Stats[StatType::Defense] += 1;

	// 다음 레벨에 필요한 경험치 증가(예: +50)
	Stats[StatType::MaxExperience] += 50;

	// 레벨업 시점에 메시지 출력 (UI 이벤트를 보낼 수도 있음)
	auto NewLevelUpEvent = make_shared<ICharacterLevelUpEvent>(OwnedCharacter->GetName(), (int)Stats[StatType::Level]);
	GlobalEventManager::Get().Notify(NewLevelUpEvent);
}

void UStatsComponent::ClampStat(StatType type, float minValue, float maxValue)
{
	Stats[type] = std::clamp(Stats[type], minValue, maxValue);
}
