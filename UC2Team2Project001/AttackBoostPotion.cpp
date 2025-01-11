#include "pch.h"
#include "AttackBoostPotion.h"
#include "Character.h"
#include "StatComponent.h"

AttackBoostPotion::AttackBoostPotion()
{

}

void AttackBoostPotion::use(Character& Target)
{
	Target.StatManager->ModifyStat(StatType::AttackPower, 5);
	cout << "공격력이 5상승 합니다." << endl;
}
