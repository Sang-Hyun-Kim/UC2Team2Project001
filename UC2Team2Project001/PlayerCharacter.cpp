#include "pch.h"
#include "PlayerCharacter.h"
#include "Inventory.h"
#include "SkillManager.h"
#include "BasicAttack.h"

Player::Player()
{
}

Player::Player(const std::string& _inName) :Character(_inName)
{
}

void Player::ManagerRegister()
{
	Character::ManagerRegister();
	inventoryComponent = make_shared<Inventory>(this);
}

void Player::Initialize()
{
	Character::Initialize();
}

void Player::UseItem(int _index, Character* _target)
{
	inventoryComponent->useItem(_index, _target);
}
