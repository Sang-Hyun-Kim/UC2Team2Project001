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
