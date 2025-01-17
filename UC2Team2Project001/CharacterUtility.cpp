#include "pch.h"
#include "CharacterUtility.h"
#include "StatComponent.h"
#include "Character.h"

bool CharacterUtility::IsDead(Character* _character)
{
	return _character->statManager->IsDead();
}

float CharacterUtility::GetStat(Character* _character, StatType _type)
{
	return _character->statManager->GetStat(_type);
}

void CharacterUtility::ModifyStat(Character* _character, StatType _type, float _delta)
{
	_character->statManager->ModifyStat(_type, _delta);
}

void CharacterUtility::PrintStatus(Character* _character)
{
	_character->statManager->PrintStatus();
}

std::string CharacterUtility::GetStatName(StatType statType)
{
    switch (statType)
    {
    case StatType::HP: return "HP";
    case StatType::MaxHP: return "최대 HP";
    case StatType::MP: return "MP";
    case StatType::MaxMP: return "최대 MP";
    case StatType::AttackPower: return "공격력";
    case StatType::Defense: return "방어력";
    case StatType::CriticalChance: return "치명타 확률";
    case StatType::EvasionRate: return "회피율";
    case StatType::Level: return "레벨";
    case StatType::Experience: return "경험치";
    case StatType::MaxExperience: return "최대 경험치";
    default: throw std::invalid_argument("Unknown StatType");
    }
}