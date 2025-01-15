#include "pch.h"
#include "CombatComponent.h"
#include "Character.h"
#include "StatComponent.h"
#include "IStrategy.h"
#include "IEventTypes.h"
#include "GlobalEventManager.h"

void CombatComponent::SetOwner(shared_ptr<Character> _owner)
{
	owner = _owner;
}

void CombatComponent::SetTarget(shared_ptr<Character> _target)
{
	target = _target;
}

void CombatComponent::Attack()
{
	if (CharacterUtility::IsDead(owner.get()))
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
	attackStrategy->Attack(owner.get(), target.get());
}

void CombatComponent::TakeDamage(int _incomingDamage)
{
	int finalDamage = _incomingDamage;

	// 방어 전략 적용
	if (defenseStrategy)
	{
		finalDamage = defenseStrategy->CalculateDamageReceived(owner.get(), _incomingDamage);
	}

	//콜백을 리워드 시스템에 연결
	auto Event = make_shared<ICharacterDamagedEvent>(owner->GetName(), finalDamage, CharacterUtility::GetStat(owner.get(), StatType::HP));
	GlobalEventManager::Get().Notify(Event);

	CharacterUtility::ModifyStat(owner.get(), StatType::HP, (float)-finalDamage);
}

void CombatComponent::SetAttackStrategy(shared_ptr<IAttackStrategy> _newAttackStrategy)
{
	attackStrategy = move(_newAttackStrategy);
}

void CombatComponent::SetDefenseStrategy(shared_ptr<IDefenseStrategy> _newDefenseStrategy)
{
	defenseStrategy = move(_newDefenseStrategy);
}
