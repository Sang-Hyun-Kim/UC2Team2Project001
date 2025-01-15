#include "pch.h"
#include "CharacterTypes.h"
#include "Item.h"

bool FCharacterReward::IsEmpty() const
{
	return DropGold <= 0 && DropItem == nullptr;
}
