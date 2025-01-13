#include "pch.h"
#include "HealthPotion.h"
#include "Character.h"
#include "StatComponent.h"
HealthPotion::HealthPotion(): Potion(1, "체력 물약", "체력을 회복하는 물약입니다.", 50) {}

void HealthPotion::use(Character* Target)
{
    Target->StatManager->ModifyStat(StatType::HP, 50);
    cout << "체력을 회복합니다." << endl;
}

shared_ptr<Item> HealthPotion::clone() const
{
    return make_shared<HealthPotion>(*this);
}
