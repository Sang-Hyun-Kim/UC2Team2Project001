#include "pch.h"
#include "../../Item/Potion/HealthPotion.h"

HealthPotion::HealthPotion(): Potion("체력 물약", "체력을 회복하는 물약입니다.", 50) {}

void HealthPotion::use()
{
    cout << "체력을 회복합니다." << endl;
}