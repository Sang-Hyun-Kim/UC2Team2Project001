#include "pch.h"
#include "ManaPotion.h"
#include "ConsoleLayout.h"

ManaPotion::ManaPotion(int _id) : Potion(_id, "마나 물약", "마나를 회복하는 물약입니다.", 60)
{
}

bool ManaPotion::use(Character* _target)
{
    if (CharacterUtility::GetStat(_target, StatType::MP) < CharacterUtility::GetStat(_target, StatType::MaxMP))
    {
        CharacterUtility::ModifyStat(_target, StatType::MP, 40);
        ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "마나를 40 회복합니다.", true, ConsoleColor::LightBlue);
        return true;
    }

    ConsoleLayout::GetInstance().AppendLine(ConsoleRegionType::LeftBottom, "마나가 이미 최대치 입니다.", true, ConsoleColor::Magenta);

    return false;
}

shared_ptr<Item> ManaPotion::clone() const
{
	return make_shared<ManaPotion>(*this);
}