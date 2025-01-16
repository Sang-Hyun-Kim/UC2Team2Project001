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
	InventoryComponent = make_shared<Inventory>(this);
}

void Player::Initialize()
{
	Character::Initialize();
	SkillManager::GetInstance().CreateSkillFromType(typeid(BasicAttack), this);
}

void Player::UseItem(int index, Character* target)
{
	inventoryComponent->useItem(_index, _target);
}
