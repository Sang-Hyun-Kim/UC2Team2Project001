#include "pch.h"
#include "CharacterStatus.h"

#include "Character.h"
#include "CombatComponent.h"
#include "UStatusComponent.h"
#include "StatComponent.h"

#include <iostream>


void ICharacterState::TickDuration()
{
	if (duration > 0)
	{
		--duration;
	}
}

bool ICharacterState::IsExpired() const
{
	return duration <= 0;
}

const std::string& ICharacterState::GetStateName() const
{
	return stateName;
}

int ICharacterState::GetDuration() const
{
	return duration;
}

void ICharacterState::SetDuration(int NewDuration)
{
	duration = NewDuration;
}

void ICharacterState::ApplyStack(int NewStack)
{
	currentStack += NewStack;
	currentStack = clamp(currentStack, 0, currentStack);
}

void BurnState::ApplyEffect(Character* Target)
{
	// 만료되지 않았다면 데미지 적용
	if (Target && !IsExpired())
	{
		std::cout << Target->GetName() << "은(는) 불타고 있어 " << damagePerTurn << "의 데미지를 받았습니다. " << "[남은 턴: " << GetDuration() << "]\n";

		Target->combatManager->TakeDamage(damagePerTurn);
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
	currentStack += NewStack;
	currentStack = clamp(currentStack, 0, currentStack);
}

void PoisonState::ApplyEffect(Character* Target)
{
	if (Target && !IsExpired())
	{
		int CalculatedDamage = damagePerTurn * currentStack;
		std::cout << Target->GetName() << "은(는) 중독되어 " << CalculatedDamage << "의 데미지를 받았습니다. " << "[스택: " << currentStack << ", 남은 턴: " << GetDuration() << "]\n";
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
		target->statusManager->RemoveState(typeid(UnbreakableState));
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

void ModifyStatState::ApplyEffect(Character* _target)
{
	if (!isApplied)
	{
		target = _target;
		CharacterUtility::ModifyStat(target, statType, value); // 스탯 증가/감소
		isApplied = true;
	}
}

void ModifyStatState::EffectBeforeRemove()
{
	if (isApplied && target)
	{
		CharacterUtility::ModifyStat(target, statType, -value); // 원래 값 복구
		isApplied = false;
	}
}

void CursedSealState::ApplyEffect(Character* target)
{
	// 주기적 데미지 적용
	if (turnCounter % interval == 0 && target)
	{
		if (target->statManager)
		{
			target->statManager->ModifyStat(StatType::HP, -(float)damage);
			std::cout << target->GetName() << "은(는) 저주의 인장 효과로 " << damage << "의 데미지를 받았습니다. [남은 HP: " << target->statManager->GetStat(StatType::HP) << "]\n";
		}
	}
}

void CursedSealState::TickDuration()
{
	// 턴 카운터 증가 및 지속 시간 감소
	++turnCounter;
	ICharacterState::TickDuration(); // 부모 클래스의 지속 시간 감소 로직 호출
}

SanctificationState::SanctificationState(int _duration, float _increasValue)
	: ICharacterState("신성화 상태", _duration), increasValue(_increasValue), target(nullptr), isApplied(false)
{
}

void SanctificationState::ApplyEffect(Character* _target)
{
	if (!isApplied)
	{
		target = _target;
		CharacterUtility::ModifyStat(target, StatType::AttackPower, increasValue);
		CharacterUtility::ModifyStat(target, StatType::Defense, increasValue);
		CharacterUtility::ModifyStat(target, StatType::EvasionRate, increasValue / 100);
		isApplied = true;
	}
}

void SanctificationState::EffectBeforeRemove()
{
	if (isApplied && target)
	{
		CharacterUtility::ModifyStat(target, StatType::AttackPower, -increasValue);
		CharacterUtility::ModifyStat(target, StatType::Defense, -increasValue);
		CharacterUtility::ModifyStat(target, StatType::EvasionRate, -(increasValue / 100));
		isApplied = false;
	}
}
