#include "pch.h"
#include "IStrategy.h"
#include "Character.h"
#include "StatComponent.h"
#include <memory>
#include "IEventTypes.h"
#include "GlobalEventManager.h"

using namespace std;

void BasicAttackStrategy::Attack(Character* Self, Character* Target) 
{
	// 치명타 확률 계산
	int CriticalChance = (int)(Self->StatManager->GetStat(StatType::CriticalChance) * 100);
	bool IsCritical = (rand() % 100) <= CriticalChance;

	int BaseDamage = (int) Self->StatManager->GetStat(StatType::AttackPower);
	int FianlDamage = IsCritical ? (BaseDamage * 2) : BaseDamage;

	auto Event = make_shared<ICharacterAttackEvent>(Self->GetName(), FianlDamage);
	GlobalEventManager::Get().Notify(Event);

	Target->TakeDamage(FianlDamage);
}

int BlockDefenseStrategy::CalculateDamageReceived(Character* Self, int IncomingDamage) 
{
	int finalDamage = IncomingDamage - (int)Self->StatManager->GetStat(StatType::Defense);

	if (finalDamage < 0) finalDamage = 0;

	auto Event = make_shared<ICharacterDefenseEvent>(Self->GetName(), IncomingDamage, finalDamage);
	GlobalEventManager::Get().Notify(Event);

	return finalDamage;
}

//int EvadeDefenseStrategy::CalculateDamageReceived(Character* Self, int IncomingDamage) 
//{
//	bool isEvaded = (rand() % 4 == 0);
//
//	if (isEvaded)
//	{
//		cout << Self->CharacterName << "이(가) 공격을 완전히 회피했습니다! (0 데미지)\n";
//		return 0;
//	}
//	else 
//	{
//		cout << Self->CharacterName << "이(가) 회피에 실패했습니다. 데미지: " << IncomingDamage << endl;
//		return IncomingDamage;
//	}
//}
