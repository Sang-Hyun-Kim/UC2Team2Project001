#include "pch.h"
#include "CharacterStatus.h"
#include "Character.h"
#include <iostream>
#include "CombatComponent.h"
#include "UStatusComponent.h"

void BurnState::ApplyEffect(Character* Target)
{
	// 만료되지 않았다면 데미지 적용
	if (Target && !IsExpired())
	{
		std::cout << Target->GetName() << "은(는) 불타고 있어 " << DamagePerTurn << "의 데미지를 받았습니다. " << "[남은 턴: " << GetDuration() << "]\n";

		Target->combatManager->TakeDamage(DamagePerTurn);
	}
}

void ModifyDefenseState::ApplyEffect(Character* _target)
{
	if (!isApplied)
	{
		target = _target;
		CharacterUtility::ModifyStat(_target, StatType::Defense, modifyValue);
		isApplied = true;

		cout << "방어력 증감 효과 발동" << endl;
	}
}

void ModifyDefenseState::EffectBeforeRemove()
{
	CharacterUtility::ModifyStat(target, StatType::Defense, -modifyValue);
}
