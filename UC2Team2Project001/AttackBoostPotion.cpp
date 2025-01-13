#include "pch.h"
#include "AttackBoostPotion.h"
#include "Character.h"
#include "StatComponent.h"

AttackBoostPotion::AttackBoostPotion() : Potion(2,"공격력 부스트 물약", "공격력을 5 증가하는  물약입니다.", 50) {}

void AttackBoostPotion::use(Character* Target)
{
	Target->StatManager->ModifyStat(StatType::AttackPower, 5);
	cout << "공격력이 5상승 합니다." << endl;
}

shared_ptr<Item> AttackBoostPotion::clone() const
{
	return make_shared<AttackBoostPotion>(*this);
}
