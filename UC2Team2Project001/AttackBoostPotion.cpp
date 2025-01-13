#include "pch.h"
#include "AttackBoostPotion.h"
#include "Character.h"
#include "StatComponent.h"

AttackBoostPotion::AttackBoostPotion() : Potion("공격력 물약", "공격력을 증가 시키는 물약입니다.", 5) {}

void AttackBoostPotion::use(Character& Target)
{
	Target.StatManager->ModifyStat(StatType::AttackPower, 5);
	cout << "공격력이 5상승 합니다." << endl;
}
