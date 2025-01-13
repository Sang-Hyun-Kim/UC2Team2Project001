#include "pch.h"
#include "PlayerCharacter.h"
#include "Inventory.h"

Player::Player()
{
	InventoryComponent = make_shared<Inventory>(this);
}

Player::Player(const std::string& InName) :Character(InName)
{
	InventoryComponent = make_shared<Inventory>(this);
}

void Player::UseItem(int index, Character* target)
{
	InventoryComponent->useItem(index, target);
}
