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
	int baseDamage = (int)CharacterUtility::GetStat(_self, StatType::AttackPower);

	auto Event = make_shared<ICharacterAttackEvent>(_self->GetName(), baseDamage);
	GlobalEventManager::Get().Notify(Event);

	_target->combatManager->TakeDamage(baseDamage);
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
