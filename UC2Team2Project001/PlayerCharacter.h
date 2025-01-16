
#pragma once
#include "Character.h"

class Inventory;

class Player : public Character
{
public:
	Player();

	Player(const std::string& InName);

	virtual ~Player() = default;

	virtual void ManagerRegister() override;

	virtual void Initialize() override;

	// 아이템 사용

	void UseItem(int index, Character* target);

public:
	shared_ptr<Inventory> InventoryComponent;

};
