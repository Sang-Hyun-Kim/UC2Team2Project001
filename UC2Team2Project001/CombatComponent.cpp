#include "pch.h"
#include "CombatComponent.h"
#include "Character.h"
#include "StatComponent.h"
#include "IStrategy.h"
#include "ICharacterEventTypes.h"
#include "GlobalEventManager.h"
#include "StatsLoader.h"
#include "StrategyFactory.h"
#include "ConsoleColorManager.h"

UCombatComponent::UCombatComponent()
{

}

UCombatComponent::UCombatComponent(Character* _owner)
{
	owner = _owner;
}

void UCombatComponent::Initialize(StatsData _loadStatsData)
{
	// 전략 설정
	SetAttackStrategy(StrategyFactory::CreateAttackStrategy(_loadStatsData.AttackStrategyData));
	SetDefenseStrategy(StrategyFactory::CreateDefenseStrategy(_loadStatsData.DefenseStrategyData));
}

void UCombatComponent::SetOwner(Character* _owner)
{
	owner = _owner;
}

void UCombatComponent::SetTarget(Character* _target)
{
	target = _target;
}

void UCombatComponent::TakeDamage(int _incomingDamage)
{
	int finalDamage = _incomingDamage;

	// 방어 전략 적용
	if (defenseStrategy)
	{
		finalDamage = defenseStrategy->CalculateDamageReceived(owner, _incomingDamage);
	}

	//콜백을 리워드 시스템에 연결
	auto Event = make_shared<ICharacterDamagedEvent>(owner->GetName(), finalDamage, CharacterUtility::GetStat(owner, StatType::HP));
	GlobalEventManager::Get().Notify(Event);

	CharacterUtility::ModifyStat(owner, StatType::HP, (float)-finalDamage);
	ConsoleColorManager::GetInstance().SetDefaultColor();
}

void UCombatComponent::SetAttackStrategy(shared_ptr<IAttackStrategy> _newAttackStrategy)
{
	attackStrategy = move(_newAttackStrategy);
}

void UCombatComponent::SetDefenseStrategy(shared_ptr<IDefenseStrategy> _newDefenseStrategy)
{
	defenseStrategy = move(_newDefenseStrategy);
}

shared_ptr<IAttackStrategy> UCombatComponent::GetAttackStrategy()
{
	return attackStrategy;
}
