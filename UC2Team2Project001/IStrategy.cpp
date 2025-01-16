#include "pch.h"
#include "IStrategy.h"
#include "Character.h"
#include "StatComponent.h"
#include <memory>

#include "GlobalEventManager.h"
#include "CombatComponent.h"
#include "ICharacterEventTypes.h"
#include "ConsoleColorManager.h"

using namespace std;

void BasicAttackStrategy::Attack(Character* _self, Character* _target, float _damge)
{
	auto Event = make_shared<ICharacterAttackEvent>(_self->GetName(), _damge);
	GlobalEventManager::Get().Notify(Event);

	ConsoleColorManager::GetInstance().SetColor(ConsoleColor::Yellow, ConsoleColor::Black);
	std::cout << "공격을 수행하여" << _damge << "의 피해를 주었습니다!" << std::endl;
	_target->combatManager->TakeDamage(_damge);

}

int BlockDefenseStrategy::CalculateDamageReceived(Character* _self, int _incomingDamage) 
{
	int defenseValue = (int)CharacterUtility::GetStat(_self, StatType::Defense);
	int finalDamage = _incomingDamage - defenseValue;

	if (finalDamage < 0) finalDamage = 0;

	auto Event = make_shared<ICharacterDefenseEvent>(_self->GetName(), _incomingDamage, defenseValue);
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
