#include "pch.h"
#include "IStrategy.h"
#include "Character.h"
#include "StatComponent.h"
#include <memory>

#include "GlobalEventManager.h"
#include "CombatComponent.h"
#include "ICharacterEventTypes.h"

using namespace std;

void BasicAttackStrategy::Attack(Character* _self, Character* _target)
{
	// 치명타 확률 계산
	int CriticalChance = (int)(CharacterUtility::GetStat(_self, StatType::CriticalChance) * 100);
	bool IsCritical = (rand() % 100) <= CriticalChance;

	int BaseDamage = (int)CharacterUtility::GetStat(_self, StatType::AttackPower);
	int FianlDamage = IsCritical ? (BaseDamage * 2) : BaseDamage;

	auto Event = make_shared<ICharacterAttackEvent>(_self->GetName(), FianlDamage);
	GlobalEventManager::Get().Notify(Event);

	_target->combatManager->TakeDamage(FianlDamage);
}

int BlockDefenseStrategy::CalculateDamageReceived(Character* _self, int _incomingDamage) 
{
	int DefenseValue = (int)CharacterUtility::GetStat(_self, StatType::Defense);
	int finalDamage = _incomingDamage - DefenseValue;

	if (finalDamage < 0) finalDamage = 0;

	auto Event = make_shared<ICharacterDefenseEvent>(_self->GetName(), _incomingDamage, DefenseValue);
	GlobalEventManager::Get().Notify(Event);

	return finalDamage;
}

//int EvadeDefenseStrategy::CalculateDamageReceived(Character* _self, int _incomingDamage) 
//{
//	bool isEvaded = (rand() % 4 == 0);
//
//	if (isEvaded)
//	{
//		cout << _self->GetName() << "이(가) 공격을 완전히 회피했습니다! (0 데미지)\n";
//		return 0;
//	}
//	else 
//	{
//		cout << _self->GetName() << "이(가) 회피에 실패했습니다. 데미지: " << _incomingDamage << endl;
//		return _incomingDamage;
//	}
//}
