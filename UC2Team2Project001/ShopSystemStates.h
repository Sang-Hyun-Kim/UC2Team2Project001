#pragma once
#include "pch.h"
#include "ShopSystem.h"


class ShopMainState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* system) override
	{
		auto shop = dynamic_cast<ShopSystem*>(system);

		if (shop)
		{
			shop->MainMenu();
		}
	}
};

class ShopDisplayInventoryState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* system) override
	{
		auto shop = dynamic_cast<ShopSystem*>(system);

		if (shop)
		{
			shop->DisplayInventory();
		}
	}
};

class ShopBuyItemState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* system) override
	{
		auto shop = dynamic_cast<ShopSystem*>(system);

		if (shop)
		{
			shop->BuyItemMenu();
		}
	}
};

class ShopBuySkillState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* system) override
	{
		auto shop = dynamic_cast<ShopSystem*>(system);

		if (shop)
		{
			shop->BuySkillMenu();
		}
	}
};

class ShopSellState : public ISystemState
{
public:
	// ISystemState을(를) 통해 상속됨
	void Excute(GameSystem* system) override
	{
		auto shop = dynamic_cast<ShopSystem*>(system);

		if (shop)
		{
			shop->SellMenu();
		}
	}
};