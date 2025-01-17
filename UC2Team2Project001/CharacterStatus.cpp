#include "pch.h"
#include "CharacterStatus.h"

#include "Character.h"
#include "CombatComponent.h"
#include "UStatusComponent.h"
#include "StatComponent.h"

#include <iostream>
#include "ConsoleColorManager.h"
#include "PlayerCharacter.h"
#include "ConsoleLayout.h"


void ICharacterState::TickDuration()
{
	if (duration > 0)
	{
		--duration;
	}
}

bool ICharacterState::IsExpired() const
{
	return duration < 0;
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
		CharacterUtility::ModifyStat(_target, StatType::HP, damagePerTurn);
		std::cout << _target->GetName() << "은(는) 불타고 있어 " << damagePerTurn << "의 데미지를 받았습니다. " << "[남은 턴: " << GetDuration() << "]\n";
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


		std::string defenseLog = "🛡️ 방어력: " + std::to_string(beforeDefense) + " -> " + std::to_string(CharacterUtility::GetStat(target, StatType::Defense));

		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, defenseLog, true, ConsoleColor::LightGreen);

	}
}

void ModifyDefenseState::EffectBeforeRemove()
{
	float beforeDefense = CharacterUtility::GetStat(target, StatType::Defense);
	CharacterUtility::ModifyStat(target, StatType::Defense, -modifyValue);

	std::string defenseLog = "🛡️ 방어력: " + std::to_string(beforeDefense) + " -> " + std::to_string(CharacterUtility::GetStat(target, StatType::Defense));
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, defenseLog, true, ConsoleColor::LightGreen);
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

		std::string statePrint = "🤬" + _target->GetName() + " 중독! " +
			std::to_string(CalculatedDamage) + " 데미지 " +
			"[" + std::to_string(currentStack) + "스택, " +
			std::to_string(GetDuration()) + "턴]";

		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, statePrint, true, ConsoleColor::Magenta);

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

		std::string stateRemovedMsg = "💪 " + target->GetName() + "의 불굴 상태 해제!";
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, stateRemovedMsg, true, ConsoleColor::LightBlue);

		std::string hpRecoveryMsg = "❤️ 체력 +20";
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, hpRecoveryMsg, true, ConsoleColor::LightBlue);
		return;
	}

	std::string currentHpMsg = "❤️ " + target->GetName() + " 체력: " + std::to_string(CharacterUtility::GetStat(target, StatType::HP));
	ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, currentHpMsg, true, ConsoleColor::LightBlue);

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

		// 스탯 타입과 상승값을 로그에 표시
		std::string statName = CharacterUtility::GetStatName(statType); // StatType을 문자열로 변환하는 유틸리티 함수 필요
		std::string logMessage = "🌟 " + statName + "이(가) " + std::to_string(duration) + "턴 동안 " + std::to_string(value) + "만큼 상승";
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, logMessage, true, ConsoleColor::LightBlue);

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

			std::string curseEffectString = "😱" + _target->GetName() + " [HP: " + std::to_string(_target->statManager->GetStat(StatType::HP)) + "] 저주 피해 " + std::to_string(damage);
			ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, curseEffectString, true, ConsoleColor::Magenta);

		}
	}
}

void CursedSealState::TickDuration()
{
	// 턴 카운터 증가 및 지속 시간 감소
	++turnCounter;
	ICharacterState::TickDuration(); // 부모 클래스의 지속 시간 감소 로직 호출
}

SanctificationState::SanctificationState(int _duration, float _increasValue) : ICharacterState("신성화", _duration), increasValue(_increasValue), target(nullptr), isApplied(false)
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

		std::string attackString = "🌟 " + target->GetName() + "의 공격력 : " + std::to_string(beforeAttackPower) + " -> " + std::to_string(CharacterUtility::GetStat(target, StatType::AttackPower));
		std::string defenseString = "🌟 " + target->GetName() + "의 방어력 : " + std::to_string(beforeDefense) + " -> " + std::to_string(CharacterUtility::GetStat(target, StatType::Defense));
		std::string evasionString = "🌟 " + target->GetName() + "의 회피력: " + std::to_string(beforeEvasionRate) + " -> " + std::to_string(CharacterUtility::GetStat(target, StatType::EvasionRate));

		// ConsoleLayout을 사용해 출력
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, attackString, true, ConsoleColor::Brown);
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, defenseString, true, ConsoleColor::Brown);
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, evasionString, true, ConsoleColor::Brown);

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


		std::string attackString = "🌟 공격력: " + std::to_string(beforeAttackPower) + " -> " + std::to_string(CharacterUtility::GetStat(target, StatType::AttackPower));
		std::string defenseString = "🌟 방어력: " + std::to_string(beforeDefense) + " -> " + std::to_string(CharacterUtility::GetStat(target, StatType::Defense));
		std::string evasionString = "🌟 회피력: " + std::to_string(beforeEvasionRate) + " -> " + std::to_string(CharacterUtility::GetStat(target, StatType::EvasionRate));
		std::string statsString = target->GetName() + "🌟  [" + attackString + ", " + defenseString + ", " + evasionString + "]";

		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, attackString, true, ConsoleColor::Brown);
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, defenseString, true, ConsoleColor::Brown);
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, evasionString, true, ConsoleColor::Brown);
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, statsString, true, ConsoleColor::Brown);


		isApplied = false;
	}
}

void RageState::ApplyEffect(Character* _target)
{
	if (!isApplied && _target)
	{
		target = _target;
		isApplied = true;

		// 공격력 증가
		float currentAttackPower = CharacterUtility::GetStat(target, StatType::AttackPower);
		CharacterUtility::ModifyStat(target, StatType::AttackPower, currentAttackPower * (damageMultiplier - 1));


		std::string effectString = "🌟" + target->GetName() + " 분노 중! 다음 공격 " + std::to_string(damageMultiplier * 100) + "% 피해";
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, effectString, true, ConsoleColor::Brown);
	}

}

void RageState::EffectBeforeRemove()
{
	if (isApplied && target)
	{
		// 공격력 복구
		float currentAttackPower = CharacterUtility::GetStat(target, StatType::AttackPower);
		CharacterUtility::ModifyStat(target, StatType::AttackPower, -(currentAttackPower / damageMultiplier * (damageMultiplier - 1)));

		std::string effectString = "😳" + target->GetName() + "의 분노 상태 종료 .";
		ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, effectString, true, ConsoleColor::Brown);

		isApplied = false;
	}
}
