#include "pch.h"
#include "CharacterStatus.h"

#include "Character.h"
#include "CombatComponent.h"
#include "UStatusComponent.h"
#include "StatComponent.h"

#include <iostream>
#include "ConsoleColorManager.h"
#include "PlayerCharacter.h"


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

void ICharacterState::SetDuration(int _newDuration)
{
	duration = _newDuration;
}

void ICharacterState::ApplyStack(int _newStack)
{
	currentStack += _newStack;
	currentStack = clamp(currentStack, 0, currentStack);
}

void BurnState::ApplyEffect(Character* _target)
{
	// 만료되지 않았다면 데미지 적용
	if (_target && !IsExpired())
	{
		std::cout << _target->GetName() << "은(는) 불타고 있어 " << damagePerTurn << "의 데미지를 받았습니다. " << "[남은 턴: " << GetDuration() << "]\n";

		_target->combatManager->TakeDamage(damagePerTurn);
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

void PoisonState::ApplyStack(int _newStack)
{
	currentStack += _newStack;
	currentStack = clamp(currentStack, 0, currentStack);
}

void PoisonState::ApplyEffect(Character* _target)
{
	if (_target && !IsExpired())
	{
		int CalculatedDamage = damagePerTurn * currentStack;
		std::cout << _target->GetName() << "은(는) 중독되어 " << CalculatedDamage << "의 데미지를 받았습니다. " << "[스택: " << currentStack << ", 남은 턴: " << GetDuration() << "]\n";
		_target->statManager->ModifyStat(StatType::HP, -(float)CalculatedDamage);
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

void CursedSealState::ApplyEffect(Character* _target)
{
	// 주기적 데미지 적용
	if (turnCounter % interval == 0 && _target)
	{
		if (_target->statManager)
		{
			_target->statManager->ModifyStat(StatType::HP, -(float)damage);
			std::cout << _target->GetName() << "은(는) 저주의 인장 효과로 " << damage << "의 데미지를 받았습니다. [남은 HP: " << _target->statManager->GetStat(StatType::HP) << "]\n";
		}
	}
}

void CursedSealState::TickDuration()
{
	// 턴 카운터 증가 및 지속 시간 감소
	++turnCounter;
	ICharacterState::TickDuration(); // 부모 클래스의 지속 시간 감소 로직 호출
}

SanctificationState::SanctificationState(int _duration, float _increasValue): ICharacterState("신성화", _duration), increasValue(_increasValue), target(nullptr), isApplied(false)
{
}

void SanctificationState::ApplyEffect(Character* _target)
{
	if (!isApplied)
	{
		target = _target;

		if (dynamic_cast<Player*>(target))
		{
			cout << target->GetName() << "이(가) 신성화를 사용 했습니다." << endl;
		}

		float beforeAttackPower = CharacterUtility::GetStat(target, StatType::AttackPower);
		float beforeDefense = CharacterUtility::GetStat(target, StatType::Defense);
		float beforeEvasionRate = CharacterUtility::GetStat(target, StatType::EvasionRate);

		CharacterUtility::ModifyStat(target, StatType::AttackPower, increasValue);
		CharacterUtility::ModifyStat(target, StatType::Defense, increasValue);
		CharacterUtility::ModifyStat(target, StatType::EvasionRate, increasValue / 100);

		cout << endl;

		cout << target->GetName() << "의 공격력 : " << beforeAttackPower << " ->" << CharacterUtility::GetStat(target, StatType::AttackPower) << endl;
		cout << target->GetName() << "의 방어력 : " << beforeDefense << " ->" << CharacterUtility::GetStat(target, StatType::Defense) << endl;
		cout << target->GetName() << "의 회피력 : " << beforeEvasionRate << " ->" << CharacterUtility::GetStat(target, StatType::EvasionRate) << endl;

		isApplied = true;
	}
}

void SanctificationState::EffectBeforeRemove()
{
	if (isApplied && target)
	{
		float beforeAttackPower = CharacterUtility::GetStat(target, StatType::AttackPower);
		float beforeDefense = CharacterUtility::GetStat(target, StatType::Defense);
		float beforeEvasionRate = CharacterUtility::GetStat(target, StatType::EvasionRate);

		CharacterUtility::ModifyStat(target, StatType::AttackPower, -increasValue);
		CharacterUtility::ModifyStat(target, StatType::Defense, -increasValue);
		CharacterUtility::ModifyStat(target, StatType::EvasionRate, -(increasValue / 100));

		cout << target->GetName() << "의 공격력 : " << beforeAttackPower << " ->" << CharacterUtility::GetStat(target, StatType::AttackPower) << endl;
		cout << target->GetName() << "의 방어력 : " << beforeDefense << " ->" << CharacterUtility::GetStat(target, StatType::Defense) << endl;
		cout << target->GetName() << "의 회피력 : " << beforeEvasionRate << " ->" << CharacterUtility::GetStat(target, StatType::EvasionRate) << endl;

		isApplied = false;
	}
}
