#include "pch.h"
#include "Character.h"
#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"
#include "StatComponent.h"
#include <memory>
#include "StatsLoader.h"
#include "StrategyFactory.h"
#include "CombatComponent.h"
#include "USkillComponent.h"

Character::Character()
{
	ManagerRegister();
}

Character::Character(const string& _name) : characterName(_name)
{
	ManagerRegister();

	StatsData loadStatsData = StatsLoader::LoadFromJSON(characterName);
	Initialize(loadStatsData);
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

void Character::UseItem(const string& ItemName)
{
}


