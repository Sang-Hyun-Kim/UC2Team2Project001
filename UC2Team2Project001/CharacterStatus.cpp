#include "pch.h"
#include "CharacterStatus.h"
#include "Character.h"
#include <iostream>
#include "CombatComponent.h"

#include "StatComponent.h"
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
