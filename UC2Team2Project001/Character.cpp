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
}

void Character::ManagerRegister()
{
	statManager = std::make_shared<UStatsComponent>(this);
	statManager.get()->BeginPlay();
	combatManager = make_shared<CombatComponent>();
	combatManager->SetOwner(this);
	skillManager = make_shared<USkillComponent>();
	StatusComponent = make_shared<UStatusComponent>(this);
}

void Character::Initialize()
{
	StatsData LoadStatsData = StatsLoader::LoadFromJSON(characterName);
	// 스탯 설정
	statManager->SetStat(StatType::HP, LoadStatsData.HP);
	statManager->SetStat(StatType::MaxHP, LoadStatsData.MaxHP);
	statManager->SetStat(StatType::MP, LoadStatsData.MP);
	statManager->SetStat(StatType::MaxMP, LoadStatsData.MaxMP);
	statManager->SetStat(StatType::AttackPower, LoadStatsData.AttackPower);
	statManager->SetStat(StatType::Defense, LoadStatsData.Defense);
	statManager->SetStat(StatType::CriticalChance, LoadStatsData.CriticalChance);
	statManager->SetStat(StatType::EvasionRate, LoadStatsData.EvasionRate);
	statManager->SetStat(StatType::Level, LoadStatsData.Level);
	statManager->SetStat(StatType::Experience, LoadStatsData.Experience);
	statManager->SetStat(StatType::MaxExperience, LoadStatsData.MaxExperience);
	statManager->PrintStatus();


	// 전략 설정
	combatManager->SetAttackStrategy(StrategyFactory::CreateAttackStrategy(LoadStatsData.AttackStrategyData));
	combatManager->SetDefenseStrategy(StrategyFactory::CreateDefenseStrategy(LoadStatsData.DefenseStrategyData));
}

void Character::UseItem(const string& ItemName)
{
}


