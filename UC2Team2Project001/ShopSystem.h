#pragma once
#include "GameSystem.h"

class Item;

class ShopSystem : public GameSystem
{
	enum ShopState
	{
		MAIN = 0,
		INVENTORY = 1,
		BUY = 2,
		EXIT = 3
	};
public:
	ShopSystem() {}
	virtual ~ShopSystem() {};
	virtual void EnterSystem() override;
	virtual void Update() override; 
private:
	void MainMenu();
	void DisplayInventory();
	void BuyMenu();
	void SellMenu();
	void GetRandomItems();

	vector<shared_ptr<Item>> itemList;
	int state = MAIN;
};

extern shared_ptr<ShopSystem> GShopSystem;
