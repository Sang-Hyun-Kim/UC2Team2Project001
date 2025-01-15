#include "pch.h"
#include "Character.h"
#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"
#include "StatComponent.h"
#include "UStatusComponent.h"
#include <memory>
#include "StatsLoader.h"
#include "StrategyFactory.h"
#include "CombatComponent.h"
#include "USkillComponent.h"
#include "ICharacterEventTypes.h"

Character::Character()
{
	ManagerRegister();

	//StatsData LoadStatsData = StatsLoader::LoadFromJSON(CharacterName);
	//Initialize(LoadStatsData);
}

Character::Character(const string& _name) : characterName(_name)
{
	ManagerRegister();

	StatsData LoadStatsData = StatsLoader::LoadFromJSON(CharacterName);
	Initialize(LoadStatsData);
}

void Character::ManagerRegister()
{
	statManager = std::make_shared<UStatsComponent>(this);
	statManager.get()->BeginPlay();
	combatManager = make_shared<CombatComponent>();

	shared_ptr<Character> tmp(this);
	combatManager->SetOwner(tmp);
	skillManager = make_shared<USkillComponent>();
}

void Character::Initialize(const StatsData& _stats)
{
	// 스탯 설정
	statManager->SetStat(StatType::HP, _stats.HP);
	statManager->SetStat(StatType::MaxHP, _stats.MaxHP);
	statManager->SetStat(StatType::MP, _stats.MP);
	statManager->SetStat(StatType::MaxMP, _stats.MaxMP);
	statManager->SetStat(StatType::AttackPower, _stats.AttackPower);
	statManager->SetStat(StatType::Defense, _stats.Defense);
	statManager->SetStat(StatType::CriticalChance, _stats.CriticalChance);
	statManager->SetStat(StatType::EvasionRate, _stats.EvasionRate);
	statManager->SetStat(StatType::Level, _stats.Level);
	statManager->SetStat(StatType::Experience, _stats.Experience);
	statManager->SetStat(StatType::MaxExperience, _stats.MaxExperience);
	statManager->PrintStatus();


	// 전략 설정
	combatManager->SetAttackStrategy(StrategyFactory::CreateAttackStrategy(_stats.AttackStrategyData));
	combatManager->SetDefenseStrategy(StrategyFactory::CreateDefenseStrategy(_stats.DefenseStrategyData));
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


