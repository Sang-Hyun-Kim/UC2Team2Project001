#include "pch.h"
#include "CharacterTypes.h"
#include "Item.h"

bool FCharacterReward::IsEmpty() const
{
	return dropGold <= 0 && dropItem == nullptr;
}
