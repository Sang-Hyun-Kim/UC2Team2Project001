#include "pch.h"
#include "CharacterStatus.h"
#include "Character.h"
#include <iostream>
#include "CombatComponent.h"
#include "UStatusComponent.h"
#include "StatComponent.h"

void BurnState::ApplyEffect(Character* Target)
{
	// 만료되지 않았다면 데미지 적용
	if (Target && !IsExpired())
	{
		std::cout << Target->GetName() << "은(는) 불타고 있어 " << DamagePerTurn << "의 데미지를 받았습니다. " << "[남은 턴: " << GetDuration() << "]\n";

		Target->combatManager->TakeDamage(DamagePerTurn);
	}
}

ModifyDefenseState::~ModifyDefenseState()
{
}

void ModifyDefenseState::ApplyEffect(Character* _target)
{
	if (!isApplied)
	{
		target = _target;
		float beforeDefense = CharacterUtility::GetStat(target, StatType::Defense);
		CharacterUtility::ModifyStat(_target, StatType::Defense, modifyValue);
		isApplied = true;

		cout << "방어력 : " << beforeDefense << " ->" << CharacterUtility::GetStat(target, StatType::Defense) << endl;
	}
}

void ModifyDefenseState::EffectBeforeRemove()
{
	float beforeDefense = CharacterUtility::GetStat(target, StatType::Defense);
	CharacterUtility::ModifyStat(target, StatType::Defense, -modifyValue);
	cout << "방어력 : " << beforeDefense << " ->" << CharacterUtility::GetStat(target, StatType::Defense) << endl;
}

void PoisonState::ApplyStack(int NewStack)
{
	poisonStack += NewStack;
	poisonStack = clamp(poisonStack, 0, poisonStack);
}

void PoisonState::ApplyEffect(Character* Target)
{
	if (Target && !IsExpired())
	{
		int CalculatedDamage = damagePerTurn * poisonStack;
		std::cout << Target->GetName() << "은(는) 중독되어 " << CalculatedDamage << "의 데미지를 받았습니다. " << "[스택: " << poisonStack << ", 남은 턴: " << GetDuration() << "]\n";
		Target->statManager->ModifyStat(StatType::HP, -(float)CalculatedDamage);
	}
}

UnbreakableState::UnbreakableState(int _duration) : ICharacterState("불굴의 의지", _duration)
{
}

UnbreakableState::~UnbreakableState()
{
}

void UnbreakableState::ApplyEffect(Character* _target)
{
	target = _target;

	CharacterUtility::ModifyStat(_target, StatType::HP, 1);

	if (CharacterUtility::IsDead(target->combatManager->GetTarget()))
	{
		target->StatusComponent->RemoveState(typeid(UnbreakableState));
		CharacterUtility::ModifyStat(target, StatType::HP, 20);
		cout << target->GetName() << "의 불굴의 의지 상태가 해제되었습니다." << endl;
		cout << target->GetName() << "의 체력이 20 회복 되었습니다." << endl;
		return;
	}

	cout << target->GetName() << "의 현제 체력 : " << CharacterUtility::GetStat(target, StatType::HP) << endl;
}

void UnbreakableState::EffectBeforeRemove()
{
	CharacterUtility::ModifyStat(target, StatType::HP, -9999);
}
