#include "pch.h"
#include "StatComponent.h"
#include "Character.h"
#include "GlobalEventManager.h"
#include "IEventTypes.h"

UStatsComponent::UStatsComponent(Character* InOwnedCharacter)
{
	// 기본값 초기화
	Stats[StatType::HP] = 100;
	Stats[StatType::MaxHP] = 100;
	Stats[StatType::MP] = 50;
	Stats[StatType::MaxMP] = 50;
	Stats[StatType::AttackPower] = 10;
	Stats[StatType::Defense] = 5;
	Stats[StatType::CriticalChance] = 0.05f;        // 5%
	Stats[StatType::EvasionRate] = 0.0f;            // 회피율 0%

	OwnedCharacter = InOwnedCharacter;
}

UStatsComponent::~UStatsComponent()
{
	delete OwnedCharacter;
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

	// 예: HP가 0~MaxHP 범위를 벗어나지 않도록 clamping
	if (type == StatType::HP)
	{
		float maxHP = GetStat(StatType::MaxHP);

		if (Stats[type] < 0)
			Stats[type] = 0;
		else if (Stats[type] > maxHP)
			Stats[type] = maxHP;
	}
	// MP도 비슷한 방식으로 clamping 가능
	else if (type == StatType::MP)
	{
		float maxMP = GetStat(StatType::MaxMP);
		Stats[type] = std::clamp(Stats[type], 0.0f, maxMP);
	}

	if (Stats[type] == 0)
	{
		auto NewCharacterDeadEvent = make_shared<ICharacterDeadEvent>(OwnedCharacter->CharacterName);
		GlobalEventManager::Get().Notify(NewCharacterDeadEvent);
	}
}

bool UStatsComponent::IsDead()
{
	return Stats[StatType::HP] <= 0;
}

void UStatsComponent::PrintStatus()
{
	std::cout << "================ Character Status ================\n";
	std::cout << "Name: " << OwnedCharacter << "\n";
	std::cout << "HP: " << Stats.at(StatType::HP) << " / " << Stats.at(StatType::MaxHP) << "\n";
	std::cout << "MP: " << Stats.at(StatType::MP) << " / " << Stats.at(StatType::MaxMP) << "\n";
	std::cout << "Attack Power: " << Stats.at(StatType::AttackPower) << "\n";
	std::cout << "Defense: " << Stats.at(StatType::Defense) << "\n";
	std::cout << "Critical Chance: " << Stats.at(StatType::CriticalChance) * 100 << "%\n";
	std::cout << "Evasion Rate: " << Stats.at(StatType::EvasionRate) * 100 << "%\n";
	std::cout << "==================================================\n";
}

