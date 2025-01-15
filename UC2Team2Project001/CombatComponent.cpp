#include "pch.h"
#include "CombatComponent.h"
#include "Character.h"
#include "StatComponent.h"
#include "IStrategy.h"
#include "ICharacterEventTypes.h"
#include "GlobalEventManager.h"

void CombatComponent::SetOwner(Character* _owner)
{
	owner = _owner;
}

void CombatComponent::SetTarget(Character* _target)
{
	target = _target;
}

void CombatComponent::Attack()
{
	if (CharacterUtility::IsDead(owner))
	{
		return;
	}

	if (!target)
	{
		cout << "타겟이 없습니다." << endl;
		return;
	}

	if (!attackStrategy)
	{
		cout << "공격 전략이 설정되지 않았습니다." << endl;
		return;
	}

	// 공격 전략 실행
	attackStrategy->Attack(owner, target);
}

void CombatComponent::TakeDamage(int _incomingDamage)
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
}

void CombatComponent::SetAttackStrategy(shared_ptr<IAttackStrategy> _newAttackStrategy)
{
	attackStrategy = move(_newAttackStrategy);
}

void CombatComponent::SetDefenseStrategy(shared_ptr<IDefenseStrategy> _newDefenseStrategy)
{
	defenseStrategy = move(_newDefenseStrategy);
}
