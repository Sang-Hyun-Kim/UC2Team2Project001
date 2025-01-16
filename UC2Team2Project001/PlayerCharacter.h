
#pragma once
#include "Character.h"

class Inventory;

class Player : public Character
{
public:
	Player();

	Player(const std::string& _inName);

	virtual ~Player() = default;

	virtual void ManagerRegister() override;

	virtual void Initialize() override;

	// 아이템 사용

	void UseItem(int _index, Character* _target);

public:
	shared_ptr<Inventory> InventoryComponent;
};
