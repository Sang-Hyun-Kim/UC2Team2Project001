#include "pch.h"
#include "Character.h"
#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"
#include "StatComponent.h"
#include <memory>

#include "StatsLoader.h"
#include "StrategyFactory.h"


Character::Character() : AttackStrategy(nullptr), DefenseStrategy(nullptr)
{
	StatManager = std::make_shared<UStatsComponent>(this);
	StatManager.get()->BeginPlay();

	//StatsData LoadStatsData = StatsLoader::LoadFromJSON(CharacterName);
	//Initialize(LoadStatsData);
}

Character::Character(const string& InName) : CharacterName(InName), AttackStrategy(nullptr), DefenseStrategy(nullptr)                                                                                                                                                                                                                                                          
{
	StatManager = std::make_shared<UStatsComponent>(this);
	StatManager.get()->BeginPlay();

	StatsData LoadStatsData = StatsLoader::LoadFromJSON(CharacterName);
	Initialize(LoadStatsData);
}

void Character::Initialize(const StatsData& stats)
{
	// 스탯 설정
	if (StatManager->bIsLoadJson)
	{
		StatManager->SetStat(StatType::HP, stats.HP);
		StatManager->SetStat(StatType::MaxHP, stats.MaxHP);
		StatManager->SetStat(StatType::MP, stats.MP);
		StatManager->SetStat(StatType::MaxMP, stats.MaxMP);
		StatManager->SetStat(StatType::AttackPower, stats.AttackPower);
		StatManager->SetStat(StatType::Defense, stats.Defense);
		StatManager->SetStat(StatType::CriticalChance, stats.CriticalChance);
		StatManager->SetStat(StatType::EvasionRate, stats.EvasionRate);
		StatManager->SetStat(StatType::Level, stats.Level);
		StatManager->SetStat(StatType::Experience, stats.Experience);
		StatManager->SetStat(StatType::MaxExperience, stats.MaxExperience);
		//StatManager->PrintStatus();
	}


	// 전략 설정
	AttackStrategy = StrategyFactory::CreateAttackStrategy(stats.AttackStrategyData);
	DefenseStrategy = StrategyFactory::CreateDefenseStrategy(stats.DefenseStrategyData);
}

void Character::Attack(Character* Target)
{
	if (StatManager->IsDead())
	{
		return;
	}

	if (!Target)
	{
		std::cout << "타겟이 없습니다." << std::endl;
		return;
	}

	if (!AttackStrategy)
	{
		std::cout << "공격 전략이 설정되지 않았습니다." << std::endl;
		return;
	}

	// 공격 전략 실행
	AttackStrategy->Attack(this, Target);
}

void Character::TakeDamage(int IncomingDamage)
{
	int finalDamage = IncomingDamage;

	// 방어 전략 적용
	if (DefenseStrategy)
	{
		finalDamage = DefenseStrategy->CalculateDamageReceived(this, IncomingDamage);
	}

	//콜백을 리워드 시스템에 연결
	auto Event = make_shared<ICharacterDamagedEvent>(CharacterName, finalDamage, StatManager->GetStat(StatType::HP));
	GlobalEventManager::Get().Notify(Event);

	StatManager->ModifyStat(StatType::HP, (float) - finalDamage);
}

void Character::SetAttackStrategy(shared_ptr<IAttackStrategy> NewAttackStrategy)
{
	AttackStrategy = move(NewAttackStrategy);
}

void Character::SetDefenseStrategy(shared_ptr<IDefenseStrategy> NewDefenseStrategy)
{
	DefenseStrategy = move(NewDefenseStrategy);
}


void Character::UseItem(const string& ItemName)
{
}

bool Character::IsDead()
{
	return StatManager && StatManager->IsDead();
}
