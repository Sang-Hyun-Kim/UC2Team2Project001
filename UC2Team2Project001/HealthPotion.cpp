#include "pch.h"
#include "HealthPotion.h"
#include "Character.h"
#include "StatComponent.h"
#include "ConsoleLayout.h"

HealthPotion::HealthPotion(int _id): Potion(_id, "체력 물약", "체력을 회복하는 물약입니다.", 50)
{

}

bool HealthPotion::use(Character* _target)
{
    if (CharacterUtility::GetStat(_target, StatType::HP) < CharacterUtility::GetStat(_target, StatType::MaxHP))
    {
        CharacterUtility::ModifyStat(_target, StatType::HP, 50);
        ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "체력을 50 회복합니다.", true, ConsoleColor::Magenta);
        return true;
    }

    ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "체력이 이미 최대치 입니다.", true, ConsoleColor::Magenta);

    return false;
}

shared_ptr<Item> HealthPotion::clone() const
{
    return make_shared<HealthPotion>(*this);
}
