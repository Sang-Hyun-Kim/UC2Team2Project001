#include "pch.h"
#include "PlayerCharacter.h"
#include "Inventory.h"

Player::Player()
{
	inventoryComponent = make_shared<Inventory>(this);
}

Player::Player(const std::string& _inName) :Character(_inName)
{
	inventoryComponent = make_shared<Inventory>(this);
}

void Player::UseItem(int _index, Character* _target)
{
	inventoryComponent->useItem(_index, _target);
}
